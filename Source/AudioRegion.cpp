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

}

AudioRegion::AudioRegion(float start, float end, float referenceWidth){
    
    startValue = start / referenceWidth;
    endValue = end / referenceWidth;
    
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





