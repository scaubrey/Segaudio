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

#ifndef __JUCE_HEADER_98360490EE64D8A4__
#define __JUCE_HEADER_98360490EE64D8A4__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioRegion.h"
#include "TargetContainerComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TargetFileComponent  : public Component,
                             public ActionBroadcaster,
                             public ActionListener,
                             public ButtonListener,
                             public SliderListener
{
public:
    //==============================================================================
    TargetFileComponent (AudioDeviceManager& deviceManager);
    ~TargetFileComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void setTuningParameters(ClusterParameters* clusterTuningParams, Array<float>* newDistances, float* maxDistance);

    bool hasFileLoaded();
    SegaudioFile* getLoadedFile();

    void setPlayable(bool isPlayable);

    void actionListenerCallback(const juce::String &message);

    void playAudio();
    void stopAudio();

    void setThresholdValue(float threshold);

    void setCalculatingMask(bool status);

    void clearSimilarity();

    void setRegions(Array<AudioRegion>* regions_);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    bool isPlayable;

    AudioTransportSource audioTransport;
    AudioSourcePlayer audioSourcePlayer;

    SegaudioFile currentFile;

    AudioDeviceManager &deviceManager;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Viewport> viewport;
    ScopedPointer<TargetContainer> container;
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<TextButton> loadFileButton;
    ScopedPointer<Label> zoomLabel;
    ScopedPointer<Slider> zoomSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetFileComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_98360490EE64D8A4__
