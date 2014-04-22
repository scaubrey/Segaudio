/*
  ==============================================================================

    AudioRegion.h
    Created: 10 Mar 2014 7:15:30pm
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef AUDIOREGION_H_INCLUDED
#define AUDIOREGION_H_INCLUDED

#include "JuceHeader.h"

class AudioRegion //: public Component
{
    
public:
    AudioRegion();
    AudioRegion(float start, float end);
    AudioRegion(float start, float end, float referenceWidth);
    ~AudioRegion();
    
    float getLength();
    
    void clear();
    
    float getStart();
    float getEnd();
    
    float getStart(float referenceStart, float referenceEnd);
    float getStart(float referenceWidth);
    float getEnd(float referenceStart, float referenceEnd);
    float getEnd(float referenceWidth);

    bool isInRegion(float value);

    bool isOverlapping(AudioRegion region);
    
    
    bool isInitialized();
    
private:
    
    float startValue;
    float endValue;
    
};



#endif  // AUDIOREGION_H_INCLUDED
