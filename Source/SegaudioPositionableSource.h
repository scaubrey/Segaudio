/*
  ==============================================================================

    SegaudioPositionableSource.h
    Created: 16 Mar 2014 5:30:11pm
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef SEGAUDIOPOSITIONABLESOURCE_H_INCLUDED
#define SEGAUDIOPOSITIONABLESOURCE_H_INCLUDED

#include "JuceHeader.h"
#include "SegaudioFile.h"

class SegaudioPositionableAudioSource : public PositionableAudioSource
{
    
public:
    
    SegaudioPositionableAudioSource(SegaudioFile newFile);
    ~SegaudioPositionableAudioSource();
    
    virtual void setNextReadPosition(int64 newPosition) override;
    virtual int64 getNextReadPosition() const override ;
    virtual int64 getTotalLength() const override;
    virtual bool isLooping() const override;
    virtual void setLooping(bool shouldLoop) override;
    
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    virtual void releaseResources() override;
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    
private:
    
    SegaudioFile internalFile;
    int readIdx;
    
};



#endif  // SEGAUDIOPOSITIONABLESOURCE_H_INCLUDED
