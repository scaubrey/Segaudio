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

// This class represents regions of audio
class AudioRegion
{
    
public:
    AudioRegion();

    /*! creates region from fractions
        @param float start: fractional value
        @param float end: fractional value
    */
    AudioRegion(float start, float end);

    /*! creats region from values relative to reference width
        @param float start: value between 0 and referenceWidth
        @param float end: value between 0 and reference Width
    */
    AudioRegion(float start, float end, float referenceWidth);
    ~AudioRegion();

    /*! gets size of region
        @return float: length of region in fraction
    */
    float getLength();

    /*! sets start and end to -1, uninitialized state
        @return void
    */
    void clear();

    /*! gets raw fractional start value
        @return float: raw start value
    */
    float getStart();

    /*! gets raw fractional end value
        @return float: raw end value
    */
    float getEnd();


    /*! gets start value relative to refStart and refEnd
        @param float referenceStart: starting value of actual region
        @param float referenceEnd: ending value of actual region
        @return float: start value relative to referenceStart and referenceEnd
    */
    float getStart(float referenceStart, float referenceEnd);

    /*! gets start value relative to referenceWidth
        @param float referenceWidth: length of actual region
        @return float: start value relative to referenceWidth
    */
    float getStart(float referenceWidth);

    /*! gets end value relative to refStart and refEnd
       @param float referenceStart: starting value of actual region
       @param float referenceEnd: ending value of actual region
       @return float: end value relative to referenceStart and referenceEnd
   */
    float getEnd(float referenceStart, float referenceEnd);

    /*! gets end value relative to referenceWidth
        @param float referenceWidth: length of actual region
        @return float: end value relative to referenceWidth
    */
    float getEnd(float referenceWidth);

    /*! checks if fractional value is in region
        @param float: value as fraction
        @return bool
    */
    bool isInRegion(float value);

    /*! checks if passed region overlaps with this one
        @param AudioRegion region
        @return vool
    */
    bool isOverlapping(AudioRegion region);
    

    /*! checks if the region is initialized, ie if end is not 0
        @return bool
    */
    bool isInitialized();
    
private:
    
    float startValue; // raw fractional start value of larger whole
    float endValue; // raw fractional end value of large whole
    
};



#endif  // AUDIOREGION_H_INCLUDED
