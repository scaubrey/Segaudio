/*
  ==============================================================================

    SegaudioPositionableSource.cpp
    Created: 16 Mar 2014 5:30:11pm
    Author:  Cameron Summers

  ==============================================================================
*/

#include "SegaudioPositionableSource.h"

SegaudioPositionableAudioSource::SegaudioPositionableAudioSource(SegaudioFile newFile){
//    internalFile = newFile;
}

SegaudioPositionableAudioSource::~SegaudioPositionableAudioSource(){
    
}

void SegaudioPositionableAudioSource::setNextReadPosition(int64 newPosition){

    readIdx = newPosition;
    
}

int64 SegaudioPositionableAudioSource::getNextReadPosition() const {
    return readIdx;
}

int64 SegaudioPositionableAudioSource::getTotalLength() const {
    return 0;
}

bool SegaudioPositionableAudioSource::isLooping() const {
    return false;
}

void SegaudioPositionableAudioSource::setLooping(bool shouldLoop){
    
}

void SegaudioPositionableAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate){
    
}

void SegaudioPositionableAudioSource::releaseResources(){
    
}

void SegaudioPositionableAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill){
    
}