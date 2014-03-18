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
    
    if(featuresToUse->isNoneSelected()){
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

    // initialize feature matrix
    int numBlocksToProcess = endBlock - startBlock;
    int numFeaturesSelected = featuresToUse->getNumSelected();
    Eigen::MatrixXf featureMatrix = Eigen::MatrixXf::Zero(numBlocksToProcess, numFeaturesSelected);
    
    // process blocks
    int blockSampleIdx;
    int blockIdx = 0;
    for(int i=startBlock; i<endBlock-1; i++){
        
        int featureIdx = 0; // for indexing w/variable num features
        
        blockSampleIdx = i * windowSize; // sample idx of block
     
        AudioSampleBuffer block = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        
        for(int j=0; j<buffer->getNumChannels(); j++){
            block.copyFrom(j, 0, *buffer, j, blockSampleIdx, windowSize);
        }
        
        if(featuresToUse->rms){
            float blockRMS = calculateBlockRMS(block);
            featureMatrix(blockIdx, featureIdx) = blockRMS;
            featureIdx += 1;
        }
        
        if(featuresToUse->zcr){
            float blockZCR = calculateZeroCrossRate(block);
            featureMatrix(blockIdx, featureIdx) = blockZCR;
            featureIdx += 1;
        }
        
        blockIdx += 1;
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
    
    Array<int> indicesCandidates;
    
    for(int i=0; i<distanceArray->size(); i++){
        if((*distanceArray)[i] < clusterParams->threshold){
            indicesCandidates.add(i);
        }
    }
        
    int regionStart = indicesCandidates[0];
    int regionEnd = indicesCandidates[1];
    for(int i=1; i<indicesCandidates.size(); i++){
        if(indicesCandidates[i] - indicesCandidates[i-1] > clusterParams->regionConnectionWidth * 100 + 1){
            float regionFracWidth = (float(regionEnd) - float(regionStart)) / distanceArray->size();
            if(regionFracWidth > clusterParams->minRegionTimeWidth and regionFracWidth < clusterParams->maxRegionTimeWidth){
                regionCandidates.add(AudioRegion(regionStart, regionEnd, distanceArray->size()));
            }
            regionStart = indicesCandidates[i];
        }
        
        else{
            regionEnd = indicesCandidates[i];
        }
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