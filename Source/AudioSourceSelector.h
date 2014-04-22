/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_90189DFC3624428__
#define __JUCE_HEADER_90189DFC3624428__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioAnalysisController.h"
#include "AudioRegion.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AudioSourceSelector  : public Component,
                             public ActionBroadcaster
{
public:
    //==============================================================================
    AudioSourceSelector (int mode_);
    ~AudioSourceSelector();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    enum {
        Reference,
        Target
    } Mode;

    bool hasFileLoaded();
    void setMode(int newMode);

    SegaudioFile* getLoadedFile();

    void setFile(File &newFile);

    void drawWaveform(Graphics &g);

    void setRegions(Array<AudioRegion>* regions_);

    void drawCandidateRegions(Graphics &g);
    void drawAudioPositionBar(Graphics &g);

    float getPositionBarTime();

    void startPositionBar();
    void stopPositionBar();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void visibilityChanged();
    void mouseMove (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    String id;
    AudioThumbnail *thumbComponent;
    AudioThumbnailCache* thumbCache;

    int touchPrecision; // num pixels away for touch

    bool isHoveringOverRegionStart;
    bool isHoveringOverRegionEnd;
    int idxOfRegionHovered;


    bool isRegionBeingEdited;

    bool hasRegionSelected;
    bool fileLoaded;

    bool editableRegions;

    bool audioPLaying;

    int regionStartFraction;
    int regionEndFraction;

    AudioFormatManager* thumbFormatManager;
    int mode;

    SegaudioFile selectedFile;
    int numChannels;
    int numSamples;
    int sampleRate;

    Array<AudioRegion>* regions;

    FileInputSource* fileInputSource;

    float audioPostionFrac;

    class PositionBarTimer : public Timer
    {
    public:

        PositionBarTimer(float &positionFraction, int numSamples, int sampleRate){
            positionFrac = &positionFraction;
            totalSamples = numSamples;
            fileSampleRate = sampleRate;
        };

        ~PositionBarTimer(){

        };


        virtual void timerCallback(){
            *positionFrac += float(getTimerInterval()) * 0.001 / (totalSamples / fileSampleRate);
            if(*positionFrac > 1){ // finished playing
                stopTimer();
            }
        }

    private:
        float* positionFrac;
        int totalSamples;
        int fileSampleRate;

    };

    ScopedPointer<PositionBarTimer> positionBarTimer;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSourceSelector)
};

//[EndFile] You can add extra defines here...


//[/EndFile]

#endif   // __JUCE_HEADER_90189DFC3624428__
