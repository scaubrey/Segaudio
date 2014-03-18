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
    
    distanceArray->clear(); // don't keep adding to it

    refFeatures = calculateFeatureVector(refRegionBuffer, featuresToUse, refRegion);
    targetFeatures = calculateFeatureVector(targetBuffer, featuresToUse);
    
    
    float avgRegionVal = calculateMean(refFeatures);
    float maxDistanceVal = 0;
    
    for(int i=0; i<targetFeatures.size(); i++){
        
        float rmsVal = targetFeatures[i];
        
        float distanceVal = sqrtf(pow(fabs(rmsVal - avgRegionVal), 2));
        if(distanceVal > maxDistanceVal){
            maxDistanceVal = distanceVal;
        }
        
        distanceArray->add(distanceVal);
        
    }
    maxDistance = maxDistanceVal;

}

Array<float> AudioAnalysisController::calculateFeatureVector(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion region){
    
    Array<float> featureVector = Array<float>();
    
    int totalNumSamples = buffer->getNumSamples();

    int approxNumBlocks = floor(totalNumSamples / windowSize);
    int numBlocks, startBlock, endBlock;
    if(approxNumBlocks * windowSize == totalNumSamples){
        numBlocks = approxNumBlocks;
    }
    else{
        numBlocks = approxNumBlocks + 1;
    }
    
    startBlock = 0;
    endBlock = numBlocks;
    
    if(region.isInitialized()){ // take subsection if provided
        startBlock = floor(region.getStart(numBlocks));
        endBlock = floor(region.getEnd(numBlocks));
    }

    
    int blockIdx;
    
    for(int i=startBlock; i<endBlock-1; i++){
        
        blockIdx = i * windowSize;
     
        AudioSampleBuffer block = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        
        for(int j=0; j<buffer->getNumChannels(); j++){
            block.copyFrom(j, 0, *buffer, j, blockIdx, windowSize);
        }
        
        if(featuresToUse->isNoneSelected()){
            featureVector.add(0.0);
        }
        
        if(featuresToUse->rms){
            float blockRMS = calculateBlockRMS(block);
            featureVector.add(blockRMS);
        }
        if(featuresToUse->zcr){
            float blockZCR = calculateZeroCrossRate(block);
            featureVector.add(blockZCR);
        }
        

    }
    
    
    return featureVector;
    
}


float AudioAnalysisController::calculateBlockRMS(AudioSampleBuffer &block){
    
    float runningTotal = 0;
    float** channelArray = block.getArrayOfChannels();
    
    for(int j=0; j<block.getNumChannels(); j++){
        for(int i=0; i<block.getNumSamples(); i++){
//            std::cout << channelArray[j][i] << std::endl;
            runningTotal += powf(channelArray[j][i], 2);
        }
    }
    
    float rms = sqrtf(runningTotal);
    
    return rms;
}

float AudioAnalysisController::calculateZeroCrossRate(juce::AudioSampleBuffer &block){
    
    
}

float AudioAnalysisController::calculateMean(Array<float> values){
    int numValues = values.size();
    float runningAverage = 0;
    
    for(int i=0; i<numValues; i++){
        runningAverage = runningAverage + (values[i] - runningAverage) / (i + 1);
    }
    
    return runningAverage;
}

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