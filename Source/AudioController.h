/*
  ==============================================================================

    AudioController.h
    Created: 15 Mar 2014 12:34:52am
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef AUDIOCONTROLLER_H_INCLUDED
#define AUDIOCONTROLLER_H_INCLUDED

#include "JuceHeader.h"
#include "SegaudioFile.h"


class AudioController : public ActionBroadcaster
{
    
public:
    
    AudioController();
    ~AudioController();
    
    void setFile(SegaudioFile newFile);
    
private:
    
    ScopedPointer<AudioTransportSource> audioTransport;
    
    
    
    
};


#endif  // AUDIOCONTROLLER_H_INCLUDED
