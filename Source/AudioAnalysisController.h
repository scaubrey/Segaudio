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

class AudioAnalysisController {
    
public:
    
    AudioAnalysisController();
    ~AudioAnalysisController();
    
    void setAudioSource(Array<float>);

    
private:
    
    Array<float> audioSource;
    
    
};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
