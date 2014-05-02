/*
This file is part of Segaudio.

Segaudio is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Segaudio is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Segaudio.  If not, see <http://www.gnu.org/licenses/>.
/**/

#include "AudioRegion.h"

AudioRegion::AudioRegion(){
    startValue = 0;
    endValue = 0;
}

AudioRegion::AudioRegion(float start, float end):
    startValue(start),
    endValue(end)
{
    // check for out of bounds values
    if(startValue < 0 || startValue > 1) startValue = 0;
    if(endValue > 1 || endValue < 0) endValue = 1;

    if(end < start){
        endValue = startValue + 0.01;
    }

}

AudioRegion::AudioRegion(float start, float end, float referenceWidth){
    
    startValue = start / referenceWidth;
    endValue = end / referenceWidth;

    // check for out of bounds values
    if(startValue < 0) startValue = 0;
    if(endValue > 1) endValue = referenceWidth;

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
        return startValue * (referenceEnd - referenceStart) + referenceStart;
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
        return endValue * (referenceEnd - referenceStart) + referenceStart;
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





