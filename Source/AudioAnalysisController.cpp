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
    windowSize = 2048;
    
//    refBuffer = new AudioSampleBuffer(2, windowSize);
//    refBuffer->clear();
//    targetBuffer = new AudioSampleBuffer(2, windowSize);
//    targetBuffer->clear();
    

};

AudioAnalysisController::~AudioAnalysisController(){
    delete refBuffer;
    delete targetBuffer;
    
    refBuffer = 0;
    targetBuffer = 0;
};


void AudioAnalysisController::setReferenceAudioReader(AudioFormatReader* incomingReader){
//    referenceAudioReader = incomingReader;
    refBuffer = new AudioSampleBuffer(incomingReader->numChannels, incomingReader->lengthInSamples);
    incomingReader->read(refBuffer, 0, incomingReader->lengthInSamples, 0, true, true);
}

void AudioAnalysisController::setTargetAudioReader(AudioFormatReader* incomingReader){
//    targetAudioReader = incomingReader;
    targetBuffer = new AudioSampleBuffer(incomingReader->numChannels, incomingReader->lengthInSamples);
    incomingReader->read(targetBuffer, 0, incomingReader->lengthInSamples, 0, true, true);
}

bool AudioAnalysisController::isReady(){
    if(refBuffer->getNumSamples() > 0 and targetBuffer->getNumSamples() > 0){
        return true;
    }
    return false;
}

Array<float> AudioAnalysisController::calculateDistances(){
    
    Array<float> distanceArray;

    refFeatures = calculateFeatureVector();
    targetFeatures = calculateFeatureVector();
    
    for(int i=0; i<targetFeatures.size(); i++){
        
        distanceArray.add(sqrtf(pow(targetFeatures[i] - refFeatures[0], 2)));
        
    }
    
    return distanceArray;
}

Array<float> AudioAnalysisController::calculateFeatureVector(){
    
    Array<float> featureVector = Array<float>();
    
    int totalNumSamples = refBuffer->getNumSamples();

    int approxNumBlocks = floor(totalNumSamples / windowSize);
    int numBlocks;
    if(approxNumBlocks * windowSize == totalNumSamples){
        numBlocks = approxNumBlocks;
    }
    else{
        numBlocks = approxNumBlocks + 1;
    }
    
    
    int blockIdx;
    
    float runningAverage = 0;

    for(int i=0; i<numBlocks; i++){
        
        blockIdx = i * windowSize;
     
        AudioSampleBuffer block = AudioSampleBuffer(refBuffer->getNumChannels(), windowSize);
        
        for(int j=0; j<refBuffer->getNumChannels(); j++){
            block.copyFrom(i, 0, *refBuffer, i, blockIdx, windowSize);
        }
        
        float blockRMS = calculateBlockRMS(block);
        
        runningAverage = runningAverage + (blockRMS - runningAverage) / (i + 1);
        
    }
    
    featureVector.add(runningAverage);
    
    return featureVector;
    
}


float AudioAnalysisController::calculateBlockRMS(AudioSampleBuffer &block){
    
    int runningTotal = 0;
    float** channelArray = block.getArrayOfChannels();
    
    for(int j=0; j<block.getNumChannels(); j++){
        for(int i=0; i<block.getNumSamples(); i++){
            runningTotal += powf(channelArray[j][i], 2);
        }
    }
    
    float rms = sqrtf(runningTotal);
    
    return rms;
}


void AudioAnalysisController::actionListenerCallback(const String &message){
    
    std::cout << message;
    
}