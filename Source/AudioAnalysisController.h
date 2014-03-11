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
#include "AudioRegion.h"

class AudioAnalysisController : public ActionListener
{
    
public:
    
    AudioAnalysisController();
    ~AudioAnalysisController();
    
    void setReferenceAudioReader(AudioFormatReader* incomingReader);
    void setTargetAudioReader(AudioFormatReader* incomingReader);
    bool isReady();
    
    Array<float> calculateDistances(File srcFile, AudioRegion selectedRegion, File targetFile);
    Array<float> calculateFeatureVector(AudioSampleBuffer* buffer, AudioRegion selectedRegion=AudioRegion());
    
    float calculateBlockRMS(AudioSampleBuffer &block);
    
    float getLastMaxDistance();
    float calculateMean(Array<float> values);
    
    virtual void actionListenerCallback(const String &message);
    
private:
    
    AudioFormatManager* formatManager;
    
    AudioFormatReader* referenceAudioReader;
    AudioFormatReader* targetAudioReader;
    
//    AudioSampleBuffer* refBuffer;
//    AudioSampleBuffer* targetBuffer;
    
    Array<float> refFeatures;
    Array<float> targetFeatures;
    
    float maxDistance;
    
    int windowSize;
    
    
};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
