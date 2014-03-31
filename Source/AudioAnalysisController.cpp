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

void AudioAnalysisController::calculateDistances(Array<float>* distanceArray, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, AudioRegion refRegion, SignalFeaturesToUse* featuresToUse){
    
    distanceArray->clear(); // don't keep adding to it!

    refFeatureMat = calculateFeatureMatrix(refRegionBuffer, featuresToUse, refRegion);
    targetFeatureMat = calculateFeatureMatrix(targetBuffer, featuresToUse);
    
    
    Eigen::MatrixXf avgRegionFeatures = refFeatureMat.colwise().mean();
    
    float maxDistanceVal = 0; // keep track of max for drawing
    for(int i=0; i<targetFeatureMat.rows(); i++){
        
        float distanceVal = (targetFeatureMat.row(i) - avgRegionFeatures).squaredNorm();
        
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
    
    startBlock = 0;
    endBlock = numTotalBlocks;
    
    if(region.isInitialized()){ // take subsection if provided
        startBlock = floor(region.getStart(numTotalBlocks));
        endBlock = floor(region.getEnd(numTotalBlocks));
    }

    // initialize vars for feature matrix
    int numBlocksToProcess = endBlock - startBlock;
    int numFeaturesSelected = featuresToUse->getNumSelected();
    Eigen::MatrixXf featureMatrix = Eigen::MatrixXf::Zero(numBlocksToProcess, numFeaturesSelected);
    
    //=== Process blocks
    float rmsMean=0, rmsStd=0, rmsVar=0, zcrMean=0, zcrStd=0, zcrVar=0, tmpDelta=0; // for running feature standardization
    int rmsIdx=0, zcrIdx=0;
    int blockSampleIdx = 0, numProcessedBlocks = 0;
    int blockIdx = 0;
    for(int i=startBlock; i<endBlock-1; i++){ // TODO get last block!
        
        numProcessedBlocks += 1;
        int featureIdx = 0; // for indexing w/variable num features
        
        //---Break samples into block
        blockSampleIdx = i * windowSize; // sample idx of block
        AudioSampleBuffer asbBlock = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        for(int j=0; j<buffer->getNumChannels(); j++){
            asbBlock.copyFrom(j, 0, *buffer, j, blockSampleIdx, windowSize);
        }
        
        // TODO average data from all channels
        
        Eigen::Map<Eigen::RowVectorXf> mBlock(asbBlock.getSampleData(0), windowSize);
        Eigen::FFT<float> fft;
        Eigen::RowVectorXcf blockFft;
        
        //---Calculate fft only if we use features that need it
        if(featuresToUse->needFft()){
            fft.SetFlag(fft.HalfSpectrum);
            fft.fwd(blockFft, mBlock);
        }
        
        if(featuresToUse->rms){
            rmsIdx = featureIdx;
            float blockRMS = calculateBlockRMS(asbBlock);
            tmpDelta = blockRMS - rmsMean;
            rmsMean = rmsMean + tmpDelta / numProcessedBlocks;
            rmsVar = rmsVar + tmpDelta*(blockRMS - rmsMean);
            featureMatrix(blockIdx, featureIdx) = blockRMS;
            featureIdx += 1;
        }
        
        if(featuresToUse->zcr){
            zcrIdx = featureIdx;
            float blockZCR = calculateZeroCrossRate(asbBlock);
            tmpDelta = blockZCR - zcrMean;
            zcrMean = zcrMean + tmpDelta / numProcessedBlocks;
            zcrVar = zcrVar + tmpDelta*(blockZCR - zcrMean);
            featureMatrix(blockIdx, featureIdx) = blockZCR;
            featureIdx += 1;
        }
        
        if(featuresToUse->sf){
            float blockSf = calculateSprectralFlux(blockFft);
            featureMatrix(blockIdx, featureIdx) = blockSf;
            featureIdx += 1;
        }
        
        if(featuresToUse->mfcc){
            Eigen::RowVectorXf blockMFCC = calculateMFCC(blockFft, 44100);
            featureMatrix.block(blockIdx, featureIdx, 1, 12) = blockMFCC;
            featureIdx += 12; // note 12 spots taken!
        }
        
        blockIdx += 1;
    }
        
    //=== Standardize features
    if(featuresToUse->rms){
        rmsStd = sqrtf(rmsVar/numProcessedBlocks);
//        featureMatrix.col(rmsIdx) = (featureMatrix.col(rmsIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, rmsMean)) / rmsStd;
    }
    
    if(featuresToUse->zcr){
        zcrStd = sqrtf(zcrVar/numProcessedBlocks);
//        featureMatrix.col(zcrIdx) = (featureMatrix.col(zcrIdx) - Eigen::MatrixXf::Constant(numBlocksToProcess, 1, zcrMean)) / zcrStd;
    }
    
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

float AudioAnalysisController::calculateZeroCrossRate(juce::AudioSampleBuffer &block){
    
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

Eigen::RowVectorXf AudioAnalysisController::calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate){
        
    // for reference: http://practicalcryptography.com/miscellaneous/machine-learning/guide-mel-frequency-cepstral-coefficients-mfccs/
    
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

        for(int j=0; j<numFftBins; j++){
            if(j < float(numFftBins)/2){
                triangleBankValues[j] = float(j) / (numFftBins / 2); // scale 0 to 1
            }
            else{
                triangleBankValues[j] = (numFftBins - float(j)) / (numFftBins / 2); // scale 1 back to 0
            }
            //DBG(triangleBankValues[j]);
        }
        
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

Array<AudioRegion> AudioAnalysisController::getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray){
    
    Array<AudioRegion> regionCandidates;
    
    Array<int> acceptedBlocks;
    
    int numBlocks = distanceArray->size();
    
    for(int blockIdx=0; blockIdx<numBlocks; blockIdx++){
        if((*distanceArray)[blockIdx] < clusterParams->threshold * maxDistance * 1){
            acceptedBlocks.add(blockIdx);
        }
    }
    
    
    int numAcceptedBlocks = acceptedBlocks.size();
    int regionStart = acceptedBlocks[0];
    int regionEnd = acceptedBlocks[1];
    for(int blockIdx=1; blockIdx<numAcceptedBlocks; blockIdx++){
        if(acceptedBlocks[blockIdx] - acceptedBlocks[blockIdx-1] > clusterParams->regionConnectionWidth*float(numBlocks)/5 + 1){
            float regionFracWidth = (float(regionEnd) - float(regionStart)) / numBlocks;
            if(regionFracWidth > clusterParams->minRegionTimeWidth / 10 and regionFracWidth < clusterParams->maxRegionTimeWidth){
                regionCandidates.add(AudioRegion(regionStart, regionEnd, numBlocks));
            }
            regionStart = acceptedBlocks[blockIdx];
            regionEnd = acceptedBlocks[blockIdx];
        }
        else{
            regionEnd = acceptedBlocks[blockIdx];
            if(blockIdx == numAcceptedBlocks - 1){
                regionCandidates.add(AudioRegion(regionStart, regionEnd, numBlocks));
            }
        }
    }
    
    if(clusterParams->shouldInvertRegions){
        regionCandidates = invertClusterRegions(regionCandidates);
    }
    
    return regionCandidates;
}



void AudioAnalysisController::actionListenerCallback(const String &message){
    
//    std::cout << message;
}

int AudioAnalysisController::signum(float value){
    if(value > 0) return 1;
    if(value < 0) return -1;
    return 0;
}

Array<AudioRegion> AudioAnalysisController::invertClusterRegions(Array<AudioRegion> &regions){
    
    Array<AudioRegion> invertedRegions;
    
    int numRegions = regions.size();
    
    for(int i=0; i<numRegions-1; i++){
        invertedRegions.add(AudioRegion(regions[i].getEnd(), regions[i+1].getStart()));
    }
    
    if(regions[0].getStart() != 0.0f){
        invertedRegions.add(AudioRegion(0.0f, regions[0].getStart()));
    }
    
    if(regions[numRegions-1].getEnd() != 1.0f){
        invertedRegions.add(AudioRegion(regions[numRegions-1].getEnd(), 1.0f));
    }
    
    return invertedRegions;
    
}

void AudioAnalysisController::findRegionsGridSearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams){
    
    ClusterParameters candidateParams;
    int numTestIncrements = 100;
    float minCost = FLT_MAX, cost;
    
    if(searchParams->useWidthFilter){
        candidateParams.minRegionTimeWidth = searchParams->minWidth;
        candidateParams.maxRegionTimeWidth = searchParams->maxWidth;
    }
    
    for(int i=0; i<numTestIncrements*10; i++){
        
        candidateParams.threshold = float(i) / (numTestIncrements*10);
        
        for(int j=0; j<numTestIncrements; j++){
            candidateParams.regionConnectionWidth = float(j) / numTestIncrements;
            Array<AudioRegion> regions = getClusterRegions(&candidateParams, distanceArray);
            
            if(regions.size() == searchParams->numRegions){
                DBG("match: " + String(candidateParams.threshold) + " " + String(candidateParams.regionConnectionWidth) + " " + String(cost));
            }
            
            if(regions.size() < searchParams->numRegions){
                continue; // skip if the smoothing parameter past the target num
            }
            
            cost = getRegionCost(regions, searchParams);
            if(cost < minCost){
                bestParams->threshold = candidateParams.threshold;
                bestParams->regionConnectionWidth = candidateParams.regionConnectionWidth;
                minCost = cost;
            }
        }
    }
}

void AudioAnalysisController::findRegionsBinarySearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams){
    
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
    Array<AudioRegion> regions = Array<AudioRegion>();
    
    while(regions.size() != searchParams->numRegions){
        
        candidateParams.threshold = (rightBoundary - leftBoundary)/2;
        
        regions = getClusterRegions(&candidateParams, distanceArray);
        
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
        
        numRegions = regions.size();
        
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



float AudioAnalysisController::getRegionCost(Array<AudioRegion> &regions, SearchParameters* searchParams){
 
    float weightNumRegion = 1.0f; float weightPercentage = 2.0f;
    float cost;
    int numRegions = regions.size();
    
    float regionFilePercentage = 0.0f;
    for(int i=0; i<numRegions; i++){
        regionFilePercentage += (regions[i].getEnd() - regions[i].getStart());
    }
    
//    DBG("file percentage" + String(regionFilePercentage));
    
    cost = weightNumRegion*pow(abs(searchParams->numRegions - numRegions), 2) + weightPercentage*pow(fabs(searchParams->filePercentage - regionFilePercentage), 2);
    
    return cost;
    
}

bool AudioAnalysisController::saveRegionsToFile(Array<AudioRegion> &regions, AudioSampleBuffer* sourceBuffer, File &destinationFile, bool useSeparateFiles){
    
    return false;
}