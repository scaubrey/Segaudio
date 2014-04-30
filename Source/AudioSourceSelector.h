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

    enum { // This class can function as reference or target
        Reference,
        Target
    } Mode;

    /*! checks if file is loaded
        @return bool
    */
    bool hasFileLoaded();

    /*! sets reference or target mode
        @param int newMode
        @return void
    */
    void setMode(int newMode);

    /*! sets the file info for drawing
        @param File &newFile
        @return void
    */
    void setFile(File &newFile);

    /*! draws the audio samples from the file
        @param Graphics &g
        @return void
    */
    void drawWaveform(Graphics &g);

    /*! sets candidate regions, for target mode
        @param Array<AudioRegion>* regions_
        @return void
    */
    void setRegions(Array<AudioRegion>* regions_);

    /*! draws the regions for target mode
        @param Graphics &g
        @return void
    */
    void drawCandidateRegions(Graphics &g);

    /*! draws the bar for audio position
        @param Graphics &g
        @return void
    */
    void drawAudioPositionBar(Graphics &g);

    /*! gets the time of the position bar
        @return @float: time of position bar in seconds
    */
    float getPositionBarTime();

    /*! starts the position bar moving
        @return void
    */
    void startPositionBar();

    /*! stops the position bar moving
        @return void
    */
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

    AudioThumbnail *thumbComponent; // for displaying waveform
    AudioThumbnailCache* thumbCache; // cache for thubmnail waveform display

    int touchPrecision; // num pixels away for touch

    bool isHoveringOverRegionStart; // mouse over for drag editing regions
    bool isHoveringOverRegionEnd;  // mouse over for drag editing regions
    int idxOfRegionHovered;  // holds idx of region hovered

    bool isRegionBeingEdited; // set when mouse down on region boundary
    bool isAddingRegion;

    int numRegions;

    bool isAudioPlaying;
    bool fileLoaded;

    AudioFormatManager* thumbFormatManager; // manages formats for thumb component
    int mode; // reference or target

    float audioPositionFrac; // keeps fractional position of position bar

    int numChannels;
    int numSamples;
    int sampleRate;

    Array<AudioRegion>* regions; // holds reference region in reference mode or candidate regions in target mode

//    AudioRegion regionToAdd;

    FileInputSource* fileInputSource; // input source for file


    // TODO: inherit Timer for AudioSourceSelector instead
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
