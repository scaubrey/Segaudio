/*
  ==============================================================================

    AudioAnalysisController.cpp
    Created: 9 Mar 2014 10:45:52pm
    Author:  Cameron Summers

  ==============================================================================
*/

#include "AudioAnalysisController.h"


AudioAnalysisController::AudioAnalysisController(){
    
    windowSize = 2048*4;
    
    formatManager = new AudioFormatManager();
    formatManager->registerBasicFormats();
    
};

AudioAnalysisController::~AudioAnalysisController(){
    
    delete formatManager;
    
};

void AudioAnalysisController::calculateDistances(Array<float>* distanceArray, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, Array<AudioRegion>* refRegions, SignalFeaturesToUse* featuresToUse){
    
    Time testTime = Time();
    
    int startTime  = testTime.getApproximateMillisecondCounter();
    
    distanceArray->clear(); // don't keep adding to it!
    

    refFeatureMat = calculateFeatureMatrix(refRegionBuffer, featuresToUse, (*refRegions)[0]);
    
    DBG("Finished reg features: " + String(testTime.getApproximateMillisecondCounter() - startTime));
    
    targetFeatureMat = calculateFeatureMatrix(targetBuffer, featuresToUse, AudioRegion(0, 1));
    
    DBG("Finished target features: " + String(testTime.getApproximateMillisecondCounter() - startTime));
    
    Eigen::MatrixXf avgRegionFeatures = refFeatureMat.colwise().mean();
    
    float maxDistanceVal = 0; // keep track of max for drawing
    for(int i=0; i<targetFeatureMat.rows(); i++){
        
        float distanceVal;
        
        if(featuresToUse->getNumSelected() < 2){
            distanceVal = (targetFeatureMat.row(i) - avgRegionFeatures).squaredNorm();
        }
        else{
            // cosine distance
            float tmp1 = (targetFeatureMat.row(i).array() * avgRegionFeatures.array()).sum();
            float tmp2 = sqrt(targetFeatureMat.row(i).array().pow(2).sum());
            float tmp3 = sqrt(avgRegionFeatures.array().pow(2).sum());
            
            distanceVal = 1 - tmp1 / (tmp2 * tmp3);
        }
        
        if(i == targetFeatureMat.rows()-1){
            DBG(distanceVal);
        }
        
        if(distanceVal > maxDistanceVal){
            maxDistanceVal = distanceVal;
        }
        
        distanceArray->add(distanceVal);
    }
    maxDistance = maxDistanceVal;

}

Eigen::MatrixXf AudioAnalysisController::calculateFeatureMatrix(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion region){
    
    if(featuresToUse->isNoneSelected()){ // skip all this if no features selected
        Eigen::MatrixXf featureMatrix = Eigen::MatrixXf::Zero(0, 0);
        return featureMatrix;
    }
    
    // Separate into blocks
    int totalNumSamples = buffer->getNumSamples();
    int approxNumBlocks = floor(totalNumSamples / windowSize);
    int numTotalBlocks, startBlock, endBlock;
    if(approxNumBlocks * windowSize == totalNumSamples){
        numTotalBlocks = approxNumBlocks;
    }
    else{
        numTotalBlocks = approxNumBlocks + 1;
    }

    startBlock = floor(region.getStart(numTotalBlocks));
    endBlock = floor(region.getEnd(numTotalBlocks));

    // initialize vars for feature matrix
    int numBlocksToProcess = endBlock - startBlock;
    int numFeaturesSelected = featuresToUse->getNumSelected();
    Eigen::MatrixXf featureMatrix = Eigen::MatrixXf::Zero(numBlocksToProcess, numFeaturesSelected);
    
    //=== Process blocks
    float rmsMean=0, rmsStd=0, zcrMean=0, zcrStd=0, scMean=0, scStd=0, mfccMean=0, mfccStd=0; // for running feature standardization
    int rmsIdx=0, zcrIdx=0, scIdx=0, mfccIdx=0;
    int blockSampleIdx = 0, numProcessedBlocks = 0;
    int blockIdx = 0, blockSize = windowSize;
    
    Time testTime = Time();
    
    int totalFftTimeMs = 0;
    int totalMfccTimeMs = 0;
    
    for(int i=startBlock; i<endBlock-1; i++){
        
        numProcessedBlocks += 1;
        int featureIdx = 0; // for indexing feature matrix w/variable num features
        
        //---Break samples into block
        blockSampleIdx = i * windowSize; // sample idx of block
        if(totalNumSamples - blockSampleIdx < windowSize){
            blockSize = totalNumSamples - blockSampleIdx;
        }
        
        AudioSampleBuffer asbBlock = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        if(blockSize < windowSize){
            asbBlock.clear(); // for last block, set all values to 0
        }
        
        for(int j=0; j<buffer->getNumChannels(); j++){
            asbBlock.copyFrom(j, 0, *buffer, j, blockSampleIdx, blockSize);
        }
        
        // TODO average data from all channels
        
        Eigen::Map<Eigen::RowVectorXf> mBlock(asbBlock.getSampleData(0), windowSize);
        Eigen::FFT<float> fft;
        Eigen::RowVectorXcf blockFft;
        
        //---Calculate fft only if we use features that need it
        if(featuresToUse->needFft()){
            
            int startTime = testTime.getApproximateMillisecondCounter();
            
            fft.SetFlag(fft.HalfSpectrum);
            fft.fwd(blockFft, mBlock);
            
            totalFftTimeMs += testTime.getApproximateMillisecondCounter() - startTime;

        }
        
        //---Calculate selected features
        if(featuresToUse->rms){
            rmsIdx = featureIdx;
            float blockRMS = calculateBlockRMS(asbBlock);
            featureMatrix(blockIdx, featureIdx) = blockRMS;
            featureIdx += 1;
        }
        
        if(featuresToUse->zcr){
            zcrIdx = featureIdx;
            float blockZCR = calculateZeroCrossRate(asbBlock);
            featureMatrix(blockIdx, featureIdx) = blockZCR;
            featureIdx += 1;
        }
        
        if(featuresToUse->sf){
            float blockSf = calculateSprectralFlux(blockFft);
            featureMatrix(blockIdx, featureIdx) = blockSf;
            featureIdx += 1;
        }
        
        if(featuresToUse->sc){
            scIdx = featureIdx;
            float blockSc = calculateSpectralCentroid(blockFft);
            if(blockSc != blockSc){
                DBG(blockSc);
            }
            featureMatrix(blockIdx, featureIdx) = blockSc;
            featureIdx += 1;
        }        
        
        if(featuresToUse->mfcc){
            mfccIdx = featureIdx;
            
            int startTime = testTime.getApproximateMillisecondCounter();

            Eigen::RowVectorXf blockMFCC = calculateMFCC(blockFft, 44100);
            featureMatrix.block(blockIdx, featureIdx, 1, 12) = blockMFCC;
            featureIdx += 12; // note 12 spots taken!
            
            totalMfccTimeMs += testTime.getApproximateMillisecondCounter() - startTime;

        }
        
        blockIdx += 1; // keep track of where to put features in matrix
    }
    
    DBG("Total fft: " + String(totalFftTimeMs));
    DBG("Total mfcc: " + String(totalMfccTimeMs));

    Eigen::VectorXf meanArray;
    
    //=== Standardize features
//    if(featuresToUse->rms){
//        rmsMean = featureMatrix.col(rmsIdx).array().mean();
//        meanArray = Eigen::VectorXf::Constant(numBlocksToProcess, 1, rmsMean);
//        Eigen::VectorXf tmpArray = featureMatrix.col(rmsIdx) - meanArray;
//        
//        float tmp1 = tmpArray.array().pow(2).sum() / float(numBlocksToProcess);
//        rmsStd = sqrt(tmp1);
//        
//        featureMatrix.col(rmsIdx) = (featureMatrix.col(rmsIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, rmsMean)) / rmsStd;
//    }
//    
//    if(featuresToUse->zcr){
//        zcrMean = featureMatrix.col(zcrIdx).array().mean();
//        meanArray = Eigen::VectorXf::Constant(numBlocksToProcess, 1, zcrMean);
//        Eigen::VectorXf tmpArray = featureMatrix.col(zcrIdx) - meanArray;
//        
//        float tmp1 = tmpArray.array().pow(2).sum() / float(numBlocksToProcess);
//        zcrStd = sqrt(tmp1);
//
//        featureMatrix.col(zcrIdx) = (featureMatrix.col(zcrIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, zcrMean)) / zcrStd;
//    }
//    
//    if(featuresToUse->sc){
//        scMean = featureMatrix.col(scIdx).array().mean();
//        meanArray = Eigen::VectorXf::Constant(numBlocksToProcess, 1, scMean);
//        Eigen::VectorXf tmpArray = featureMatrix.col(scIdx) - meanArray;
//        
//        float tmp1 = tmpArray.array().pow(2).sum() / float(numBlocksToProcess);
//        scStd = sqrt(tmp1);
//        
//        featureMatrix.col(scIdx) = (featureMatrix.col(scIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, scMean)) / scStd;
//    }
    
//    if(featuresToUse->mfcc){
//        mfccMean = featureMatrix.col(scIdx).array().mean();
//        meanArray = Eigen::VectorXf::Constant(numBlocksToProcess, 1, scMean);
//        Eigen::VectorXf tmpArray = featureMatrix.col(scIdx) - meanArray;
//        
//        float tmp1 = tmpArray.array().pow(2).sum() / float(numBlocksToProcess);
//        scStd = sqrt(tmp1);
//        
//        featureMatrix.col(scIdx) = (featureMatrix.col(scIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, scMean)) / scStd;
//    }
    
    return featureMatrix;
}


float AudioAnalysisController::calculateBlockRMS(AudioSampleBuffer &block){
    
    float runningTotal = 0;
    float** channelArray = block.getArrayOfChannels();
    
    for(int j=0; j<block.getNumChannels(); j++){
        for(int i=0; i<block.getNumSamples(); i++){
            runningTotal += powf(channelArray[j][i], 2);
        }
    }
    
    float rms = sqrtf(runningTotal);
    
    return rms;
}

float AudioAnalysisController::calculateZeroCrossRate(AudioSampleBuffer &block){
    
    int blockLength = block.getNumSamples();
    int numZeroCrosses = 0;
    float zcr;
    
    float** channelArray = block.getArrayOfChannels();
    
    for(int j=0; j<block.getNumChannels(); j++){
        for(int i=1; i<blockLength; i++){
            numZeroCrosses += abs(signum(channelArray[j][i]) - signum(channelArray[j][i-1]));
        }
    }
    
    zcr = 1/(2*float(blockLength)) * float(numZeroCrosses);
    return zcr;
}

float AudioAnalysisController::calculateSprectralFlux(Eigen::RowVectorXcf &blockFft){
    return 0;
}

float AudioAnalysisController::calculateSpectralCentroid(Eigen::RowVectorXcf &blockFft){
    
    int fftLength = blockFft.size();
    
    Eigen::RowVectorXf weights = Eigen::RowVectorXf::LinSpaced(Eigen::Sequential, fftLength, 0, fftLength-1);
    
    float sc = (blockFft.array().abs().pow(2) * weights.array()).sum() / blockFft.array().abs().pow(2).sum();
    
    if(sc != sc) sc = 0; // check for nan
    
    return sc;
}

Eigen::RowVectorXf AudioAnalysisController::calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate){
        
    // coded by cameron from reference:
    // http://practicalcryptography.com/miscellaneous/machine-learning/guide-mel-frequency-cepstral-coefficients-mfccs/
    
    //---Initial params
    int numFilterBanks = 12; // num triangular filter banks applied to dft
    int numBankPts = numFilterBanks+2; 
    
    // Set min and max frequencies for our filter bank
    float minFreq = 200.0f; // Hz, start filter banks here
    float maxFreq = 8000.0f; // Hz, end here
    // TODO maxFreq has to be less that sample rate

    //---Convert to mel scale so we can get linearly spaced banks
    float minMel = 1125.0f * log(1 + minFreq/700);
    float maxMel = 1125.0f * log(1 + maxFreq/700);
    
    //---Calculate linearly spaced bank locations on mel scale
    Array<float> melBankLocations;
    for(int i=0; i<numBankPts; i++){
        melBankLocations.add(minMel + i*((maxMel - minMel)/numFilterBanks));
    }
    
    //---Convert bank pts back to hertz
    Array<float> freqBankLocations;
    for(int i=0; i<numBankPts; i++){
        freqBankLocations.add((exp(melBankLocations[i] / 1125.0f) - 1) * 700);
    }
    
    //---Round pts to nearest actual fft bin
    Array<float> freqBankBinIdxs;
    for(int i=0; i<numBankPts; i++){
        freqBankBinIdxs.add(floor((windowSize/2+1)*freqBankLocations[i] / sampleRate));
    }
    
    //---Get power spectrum estimate of dft
    Eigen::RowVectorXf periodogram = (blockFft.array().abs().pow(2) / windowSize).matrix();
    
    //---Apply triangular banks to periodogram
    Eigen::RowVectorXf logEnergies = Eigen::RowVectorXf::Zero(1, numFilterBanks);
    for(int i=0; i<numFilterBanks; i++){
                
        int bankBinStart = freqBankBinIdxs[i]; // triangle starts one before filter center
        int bankBinEnd = freqBankBinIdxs[i+2]; // ends one pt after
        int numFftBins = bankBinEnd - bankBinStart;
        
        Eigen::RowVectorXf triangleBankValues = Eigen::RowVectorXf::Zero(1, numFftBins);

        // create triangle filter banks
        for(int j=0; j<numFftBins; j++){
            if(j < float(numFftBins)/2){
                triangleBankValues[j] = float(j) / (numFftBins / 2); // scale triangle filter from 0 to 1
            }
            else{
                triangleBankValues[j] = (numFftBins - float(j)) / (numFftBins / 2); // scale 1 back to 0
            }
            //DBG(triangleBankValues[j]);
        }
        
        // multiply filter banks with spectral power
        float energy = (triangleBankValues.array() * periodogram.block(0, bankBinStart, 1, numFftBins).array()).sum();
        
        logEnergies[i] = log(energy);
    }
    
    // Take discrete cosine transform of log energies
    // Ref: http://www.haberdar.org/Discrete-Cosine-Transform-Tutorial.htm
    Eigen::RowVectorXf mfccs = Eigen::RowVectorXf::Zero(1, 12); float w;
    for(int i=0; i<numFilterBanks; i++){
        w = 0;
        
        for(int j=0; j<numFilterBanks-1; j++){
            w += logEnergies[j] * cos(M_PI * (float(j)+1/2) * i / numFilterBanks);
        }
        mfccs[i] = w;
    }
    
    return mfccs.transpose(); // return as column
}


float AudioAnalysisController::getLastMaxDistance(){
    return maxDistance;
}

void AudioAnalysisController::getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray, Array<AudioRegion>* regions){
    
    regions->clear();
    Array<int> acceptedBlocks; // holds all blocks under threshold
    
    int numBlocks = distanceArray->size();
    
    // take all blocks under threshold
    for(int blockIdx=0; blockIdx<numBlocks; blockIdx++){
        if((*distanceArray)[blockIdx] < clusterParams->threshold * maxDistance * 1){
            acceptedBlocks.add(blockIdx);
        }
    }

    int numAcceptedBlocks = acceptedBlocks.size();
    int regionStart = acceptedBlocks[0];
    int regionEnd = acceptedBlocks[1];
    
    float connWidth = clusterParams->regionConnectionWidth*50.0f + 1; // connections up to 51 blocks
    
    // for blocks under threshold, create regions satisfying other cluster params (width of region and smoothing)
    for(int blockIdx=1; blockIdx<numAcceptedBlocks; blockIdx++){
        float regionFracWidth = (float(regionEnd) - float(regionStart)) / numBlocks;

        if(acceptedBlocks[blockIdx] - acceptedBlocks[blockIdx-1] > connWidth){ // passes smoothing
            if(isRegionWithinWidth(regionFracWidth, clusterParams)){ // passes width filter
                regions->add(AudioRegion(regionStart, regionEnd, numBlocks));
            }
            regionStart = acceptedBlocks[blockIdx]; // start next region
            regionEnd = acceptedBlocks[blockIdx];
        }
        else{ // doesn't pass smoothing
            regionEnd = acceptedBlocks[blockIdx]; // so end region
            
            // catch ending region
            if(blockIdx == numAcceptedBlocks - 1 and isRegionWithinWidth(regionFracWidth, clusterParams)){
                regions->add(AudioRegion(regionStart, regionEnd, numBlocks));
            }
        }
    }
    
    // invert the regions if asked
    if(clusterParams->shouldInvertRegions){
        invertClusterRegions(regions);
    }
    
}

bool AudioAnalysisController::isRegionWithinWidth(float regionFracWidth, ClusterParameters *clusterParams){
    
    if(regionFracWidth > clusterParams->minRegionTimeWidth / 10 and regionFracWidth < clusterParams->maxRegionTimeWidth){
        return true;
    }
    
    return false;
}



void AudioAnalysisController::actionListenerCallback(const String &message){
    
//    std::cout << message;
}

int AudioAnalysisController::signum(float value){
    if(value > 0) return 1;
    if(value < 0) return -1;
    return 0;
}

void AudioAnalysisController::invertClusterRegions(Array<AudioRegion>* regions){
    
    Array<AudioRegion> invertedRegions;
    
    int numRegions = regions->size();
    
    for(int i=0; i<numRegions-1; i++){
        invertedRegions.add(AudioRegion((*regions)[i].getEnd(), (*regions)[i+1].getStart()));
    }
    
    if((*regions)[0].getStart() != 0.0f){
        invertedRegions.add(AudioRegion(0.0f, (*regions)[0].getStart()));
    }
    
    if((*regions)[numRegions-1].getEnd() != 1.0f){
        invertedRegions.add(AudioRegion((*regions)[numRegions-1].getEnd(), 1.0f));
    }

    regions->clear();
    for(int i=0; i<invertedRegions.size(); i++){
        regions->add(invertedRegions[i]);
    }
}

void AudioAnalysisController::findRegionsGridSearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams, Array<AudioRegion>* regions){
    
    ClusterParameters candidateParams;
    int numTestIncrements = 100;
    float minCost = FLT_MAX, cost;
    
    if(searchParams->useWidthFilter){
        candidateParams.minRegionTimeWidth = searchParams->minWidth;
        candidateParams.maxRegionTimeWidth = searchParams->maxWidth;
    }
    
    for(int i=0; i<numTestIncrements; i++){
        
        candidateParams.threshold = float(i) / (numTestIncrements);
        
//        for(int j=0; j<numTestIncrements; j++){
            candidateParams.regionConnectionWidth = 0;// float(j) / numTestIncrements;
        
        
            getClusterRegions(&candidateParams, distanceArray, regions);

            if(regions->size() == searchParams->numRegions){
                DBG("match: " + String(candidateParams.threshold) + " " + String(candidateParams.regionConnectionWidth) + " " + String(cost));
            }

//            if(regions->size() < searchParams->numRegions){
//                continue; // skip if the smoothing parameter past the target num
//            }

            cost = getRegionCost(regions, searchParams);
            if(cost < minCost){
                bestParams->threshold = candidateParams.threshold;
                bestParams->regionConnectionWidth = candidateParams.regionConnectionWidth;
                minCost = cost;
            }
//        }
    }
}

void AudioAnalysisController::findRegionsBinarySearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams, Array<AudioRegion>* regions){

    ClusterParameters candidateParams;
//    int numTestIncrements = 100;
    float minCost = FLT_MAX, cost;
    
    if(searchParams->useWidthFilter){
        candidateParams.minRegionTimeWidth = searchParams->minWidth;
        candidateParams.maxRegionTimeWidth = searchParams->maxWidth;
    }
    
    candidateParams.regionConnectionWidth = 0;
    int numChanges = 0; int numRegions = 0; int prevNumRegions = 0;
    float leftBoundary = 0; float rightBoundary = 1;

    while(regions->size() != searchParams->numRegions){
        
        candidateParams.threshold = (rightBoundary - leftBoundary)/2;

        cost = getRegionCost(regions, searchParams);
        if(cost < minCost){
            bestParams->threshold = candidateParams.threshold;
            bestParams->regionConnectionWidth = candidateParams.regionConnectionWidth;
            minCost = cost;
            
            numChanges = 0;
        }
        else{
            numChanges += 1;
        }
        
        numRegions = regions->size();
        
        prevNumRegions = numRegions;
        
        if(numChanges > 100){
            break;
        }
        
        if(numRegions == searchParams->numRegions){
            DBG("match: " + String(candidateParams.threshold) + " " + String(candidateParams.regionConnectionWidth) + " " + String(cost));
        }
        
        if(numRegions > searchParams->numRegions){
            rightBoundary = (rightBoundary - leftBoundary)/2;
        }
        else{
            leftBoundary = (rightBoundary - leftBoundary)/2;
        }
    }
}

void findRegionsGradientDescent(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams){
    
    int numIterations = 1;
    float convergePrecision = 0.00001;
    float stepSize = 0.001f;
    
    float thresh_old = 0;
    float thresh_new = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
    float smooth_old = 0;
    float smooth_new = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
    
    for(int i=0; i<numIterations; i++){
        
//        while(abs(thresh_new - thresh_old) > convergePrecision){
//            
//            thresh_old = thresh_new;
//            thresh_new = thresh_old - stepSize * 
//            
//        }
        
    }
}



float AudioAnalysisController::getRegionCost(Array<AudioRegion>* regions, SearchParameters* searchParams){
 
    float weightNumRegion = 1.0f; float weightPercentage = 2.0f;
    float cost;
    int numRegions = regions->size();
    
    float regionFilePercentage = 0.0f;
    for(int i=0; i<numRegions; i++){
        regionFilePercentage += ((*regions)[i].getEnd() - (*regions)[i].getStart());
    }
    
//    DBG("file percentage" + String(regionFilePercentage));
    
    cost = weightNumRegion*pow(abs(searchParams->numRegions - numRegions), 2) + weightPercentage*pow(fabs(searchParams->filePercentage - regionFilePercentage) + 1, 2);
    
    return cost;
}

bool AudioAnalysisController::saveRegionsToAudioFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile, bool useSingleFile){
    
    AudioFormat* wavFormat = formatManager->findFormatForFileExtension("wav");
    int numRegions = regions->size();
    
    if(useSingleFile){
        FileOutputStream* destOutputStream = destinationFile.createOutputStream();
        AudioFormatWriter* wavWriter = wavFormat->createWriterFor(destOutputStream, sourceFile->getSampleRate(), sourceFile->getNumChannels(), 16, nullptr, 0);
        
        // concatenate regions into one file
        for(int i=0; i<numRegions; i++){
            int regionStartSample = floor((*regions)[i].getStart() * sourceFile->getNumSamples());
            int regionEndSample = floor((*regions)[i].getEnd() * sourceFile->getNumSamples());
            
            int numSamplesToWrite = regionEndSample - regionStartSample;

            wavWriter->writeFromAudioSampleBuffer(*sourceFile->getFileBuffer(), regionStartSample, numSamplesToWrite);
            destOutputStream->flush();
        }
        
        delete wavWriter;
        
        return true;
    }
    else{ // save to multiple files
        
        for(int i=0; i<numRegions; i++){
            
            int regionStartSample = floor((*regions)[i].getStart() * sourceFile->getNumSamples());
            int regionEndSample = floor((*regions)[i].getEnd() * sourceFile->getNumSamples());
            
            int sampleRate = sourceFile->getSampleRate();
        
            File newDestinationFile = File(destinationFile.getFullPathName() + "_" + String(regionStartSample / sampleRate) + "-" + String(regionEndSample / sampleRate));
            newDestinationFile = newDestinationFile.withFileExtension(".wav");

            FileOutputStream* destOutputStream = newDestinationFile.createOutputStream();
            AudioFormatWriter* wavWriter = wavFormat->createWriterFor(destOutputStream, sourceFile->getSampleRate(), sourceFile->getNumChannels(), 16, nullptr, 0);
            
            int numSamplesToWrite = regionEndSample - regionStartSample;
            
            wavWriter->writeFromAudioSampleBuffer(*sourceFile->getFileBuffer(), regionStartSample, numSamplesToWrite);
            destOutputStream->flush();
            delete wavWriter;

        }
        
        
        return true;
    }

    return false;
}

bool AudioAnalysisController::saveRegionsToTxtFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile){
    
    int totalNumSamples = sourceFile->getNumSamples();
    int sampleRate = sourceFile->getSampleRate();
    float totalLengthInSec = float(totalNumSamples) / sampleRate;
    
    int numRegions = regions->size();
    String dataString = "";
    
    for(int i=0; i<numRegions; i++){
        dataString += (String((*regions)[i].getStart() * totalLengthInSec)) + ", " + (String((*regions)[i].getEnd() * totalLengthInSec)) + "\n";
    }
    
    destinationFile.replaceWithText(dataString);
    
    return true;
}