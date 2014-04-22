/*
  ==============================================================================

    AudioRegion.cpp
    Created: 10 Mar 2014 7:15:30pm
    Author:  Cameron Summers

  ==============================================================================
*/

#include "AudioRegion.h"

AudioRegion::AudioRegion(){
    startValue = 0;
    endValue = 0;
}

AudioRegion::AudioRegion(float start, float end):
    startValue(start),
    endValue(end)
{
    if(startValue < 0) startValue = 0;
    if(endValue > 1) endValue = 1;

    if(end < start){
        endValue = startValue + 0.01;
    }

}

AudioRegion::AudioRegion(float start, float end, float referenceWidth){
    
    startValue = start / referenceWidth;
    endValue = end / referenceWidth;
    
    if(startValue < 0) startValue = 0;
    if(endValue > 1) endValue = 1;

    if(end < start){
        endValue = startValue + 0.01;
    }

}

AudioRegion::~AudioRegion(){
    
}

float AudioRegion::getLength(){
    return endValue - startValue;
}

void AudioRegion::clear(){
    startValue = -1;
    endValue = -1;
}

float AudioRegion::getStart(){
    
    return startValue;
}

float AudioRegion::getEnd(){
    return endValue;
}


float AudioRegion::getStart(float referenceStart, float referenceEnd){
    if(isInitialized()){
        return startValue * (referenceStart - referenceEnd);
    }
    else{
        return 0;
    }
}

float AudioRegion::getStart(float referenceWidth){
    if(isInitialized()){
        return startValue * referenceWidth;
    }
    else{
        return 0;
    }
}

float AudioRegion::getEnd(float referenceStart, float referenceEnd){
    if(isInitialized()){
        return endValue * (referenceStart - referenceEnd);
    }
    else{
        return referenceEnd;
    }
}

float AudioRegion::getEnd(float referenceWidth){
    if(isInitialized()){
        return endValue * referenceWidth;
    }
    else{
        return referenceWidth;
    }
}

bool AudioRegion::isInitialized(){
    if(endValue != 0){
        return true;
    }
    return false;
}

bool AudioRegion::isInRegion(float value) {
    if(value > startValue && value < endValue){
        return true;
    }
    return false;
}

bool AudioRegion::isOverlapping(AudioRegion region) {
    if(isInRegion(region.getStart()) or isInRegion(region.getEnd())){
        return true;
    }
    return false;
}





