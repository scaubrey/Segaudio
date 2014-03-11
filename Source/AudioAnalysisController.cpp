/*
  ==============================================================================

    AudioAnalysisController.cpp
    Created: 9 Mar 2014 10:45:52pm
    Author:  Cameron Summers

  ==============================================================================
*/

#include "AudioAnalysisController.h"


AudioAnalysisController::AudioAnalysisController(){
    referenceAudioReader = nullptr;
    targetAudioReader = nullptr;
//    refBuffer = nullptr;
//    targetBuffer = nullptr;
    
    windowSize = 2048;
    
    formatManager = new AudioFormatManager();
    formatManager->registerBasicFormats();
    
//    refBuffer = new AudioSampleBuffer(2, windowSize);
//    refBuffer->clear();
//    targetBuffer = new AudioSampleBuffer(2, windowSize);
//    targetBuffer->clear();
    

};

AudioAnalysisController::~AudioAnalysisController(){
//    delete refBuffer;
//    delete targetBuffer;
//    
//    refBuffer = 0;
//    targetBuffer = 0;
};


//void AudioAnalysisController::setReferenceAudioReader(AudioFormatReader* incomingReader){
//    referenceAudioReader = incomingReader;
//    AudioSampleBuffer* tmpBuffer = new AudioSampleBuffer(incomingReader->numChannels, incomingReader->lengthInSamples);
//    incomingReader->read(tmpBuffer, 0, incomingReader->lengthInSamples, 0, true, true);
//    
//    refBuffer = new AudioSampleBuffer(*tmpBuffer);
//}
//
//void AudioAnalysisController::setTargetAudioReader(AudioFormatReader* incomingReader){
//    targetAudioReader = incomingReader;
//    AudioSampleBuffer* tmpBuffer = new AudioSampleBuffer(incomingReader->numChannels, incomingReader->lengthInSamples);
//    incomingReader->read(tmpBuffer, 0, incomingReader->lengthInSamples, 0, true, true);
//    
//    targetBuffer = new AudioSampleBuffer(*tmpBuffer);
//}
//
//bool AudioAnalysisController::isReady(){
//    if(refBuffer and targetBuffer){
//        return true;
//    }
//    return false;
//}

Array<float> AudioAnalysisController::calculateDistances(File srcFile, AudioRegion selectedRegion, File targetFile){
    
    referenceAudioReader = formatManager->createReaderFor(srcFile);
    targetAudioReader = formatManager->createReaderFor(targetFile);
    
    
    AudioSampleBuffer* refBuffer = new AudioSampleBuffer(referenceAudioReader->numChannels, referenceAudioReader->lengthInSamples);
    referenceAudioReader->read(refBuffer, 0, referenceAudioReader->lengthInSamples, 0, true, true);

    
    AudioSampleBuffer* targetBuffer = new AudioSampleBuffer(targetAudioReader->numChannels, targetAudioReader->lengthInSamples);
    targetAudioReader->read(targetBuffer, 0, targetAudioReader->lengthInSamples, 0, true, true);

    
    Array<float> distanceArray;

    refFeatures = calculateFeatureVector(refBuffer, selectedRegion);
    targetFeatures = calculateFeatureVector(targetBuffer);
    
    
    float avgRegionVal = calculateMean(refFeatures);
    float maxDistanceVal = 0;
    
    for(int i=0; i<targetFeatures.size(); i++){
        
        float rmsVal = targetFeatures[i];
        
        float distanceVal = sqrtf(pow(fabs(rmsVal - avgRegionVal), 2));
        if(distanceVal > maxDistanceVal){
            maxDistanceVal = distanceVal;
        }
        
        distanceArray.add(distanceVal);
        
    }
    maxDistance = maxDistanceVal;
    
    return distanceArray;
}

Array<float> AudioAnalysisController::calculateFeatureVector(AudioSampleBuffer* buffer, AudioRegion selectedRegion){
    
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
    
    if(selectedRegion.isInitialized()){
        startBlock = floor(selectedRegion.getStart(numBlocks));
        endBlock = floor(selectedRegion.getEnd(numBlocks));
    }

    
    int blockIdx;
    
    for(int i=startBlock; i<endBlock; i++){
        
        blockIdx = i * windowSize;
     
        AudioSampleBuffer block = AudioSampleBuffer(buffer->getNumChannels(), windowSize);
        
        for(int j=0; j<buffer->getNumChannels(); j++){
            block.copyFrom(j, 0, *buffer, j, blockIdx, windowSize);
        }
        
        float blockRMS = calculateBlockRMS(block);
        featureVector.add(blockRMS);

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



void AudioAnalysisController::actionListenerCallback(const String &message){
    
    std::cout << message;
    
}