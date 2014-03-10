/*
  ==============================================================================

    AudioAnalysisController.h
    Created: 9 Mar 2014 10:45:52pm
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef AUDIOANALYSISCONTROLLER_H_INCLUDED
#define AUDIOANALYSISCONTROLLER_H_INCLUDED

#include "JuceHeader.h"

class AudioAnalysisController : public ActionListener
{
    
public:
    
    AudioAnalysisController();
    ~AudioAnalysisController();
    
    void setReferenceAudioReader(AudioFormatReader* incomingReader);
    void setTargetAudioReader(AudioFormatReader* incomingReader);
    bool isReady();
    
    Array<float> calculateDistances();
    Array<float> calculateFeatureVector();
    
    float calculateBlockRMS(AudioSampleBuffer &block);
    
    virtual void actionListenerCallback(const String &message);
    
private:
    
    AudioFormatReader* referenceAudioReader;
    AudioFormatReader* targetAudioReader;
    
    AudioSampleBuffer* refBuffer;
    AudioSampleBuffer* targetBuffer;
    
    Array<float> refFeatures;
    Array<float> targetFeatures;
    
    int windowSize;
    
    
};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
