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
        
        blockSampleIdx = i * windowSize; // sample idx of block
     
        AudioSampleBuffer block = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        
        for(int j=0; j<buffer->getNumChannels(); j++){
            block.copyFrom(j, 0, *buffer, j, blockSampleIdx, windowSize);
        }
        
        // TODO turn buffer into matrix here
        // TODO how to deal with multichannel?
        
        if(featuresToUse->rms){
            rmsIdx = featureIdx;
            float blockRMS = calculateBlockRMS(block);
            tmpDelta = blockRMS - rmsMean;
            rmsMean = rmsMean + tmpDelta / numProcessedBlocks;
            rmsVar = rmsVar + tmpDelta*(blockRMS - rmsMean);
            featureMatrix(blockIdx, featureIdx) = blockRMS;
            featureIdx += 1;
        }
        
        if(featuresToUse->zcr){
            zcrIdx = featureIdx;
            float blockZCR = calculateZeroCrossRate(block);
            tmpDelta = blockZCR - zcrMean;
            zcrMean = zcrMean + tmpDelta / numProcessedBlocks;
            zcrVar = zcrVar + tmpDelta*(blockZCR - zcrMean);
            featureMatrix(blockIdx, featureIdx) = blockZCR;
            featureIdx += 1;
        }
        
        if(featuresToUse->sf){
            float blockSf = calculateSprectralFlux(block);
            featureMatrix(blockIdx, featureIdx) = blockSf;
            featureIdx += 1;
        }
        
        if(featuresToUse->mfcc){
            Eigen::RowVectorXf blockMFCC = calculateMFCC(block);
            featureMatrix.block(blockIdx, featureIdx, 1, 12) = blockMFCC;
            featureIdx += 12; // note 12 spots taken!
        }
        
        blockIdx += 1;
    }
    
    float test = featureMatrix.col(rmsIdx).mean();
    
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

float AudioAnalysisController::calculateSprectralFlux(AudioSampleBuffer &block){
    
    return 0;
    
}

Eigen::RowVectorXf AudioAnalysisController::calculateMFCC(AudioSampleBuffer &block){
    
    Eigen::VectorXf stubMfcc = Eigen::RowVectorXf::Zero(12).transpose();
    return stubMfcc;
}


//float AudioAnalysisController::calculateMean(Array<float> values){
//    int numValues = values.size();
//    float runningAverage = 0;
//    
//    for(int i=0; i<numValues; i++){
//        runningAverage = runningAverage + (values[i] - runningAverage) / (i + 1);
//    }
//    
//    return runningAverage;
//}

float AudioAnalysisController::getLastMaxDistance(){
    return maxDistance;
}

Array<float> AudioAnalysisController::medianFilter(Array<float> distanceArray, int width){
    // check that width is odd
    // filter array
}

Array<AudioRegion> AudioAnalysisController::getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray){
    
    Array<AudioRegion> regionCandidates;
    
    Array<int> acceptedBlocks;
    
    int numBlocks = distanceArray->size();
    
    for(int blockIdx=0; blockIdx<numBlocks; blockIdx++){
        if((*distanceArray)[blockIdx] < clusterParams->threshold * maxDistance * 1 / 10){
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

bool AudioAnalysisController::saveRegionsToFile(Array<AudioRegion> &regions, AudioSampleBuffer* sourceBuffer, File &destinationFile, bool useSeparateFiles){
    
    return false;
}