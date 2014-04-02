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

#ifndef __JUCE_HEADER_C3B8F999FE9961C4__
#define __JUCE_HEADER_C3B8F999FE9961C4__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioSourceSelector.h"
#include "SegaudioViewport.h"
#include "ReferenceContainerComponent.h"
#include "AudioController.h"
#include "SegaudioFile.h"
//#include "SegaudioPositionableSource.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ReferenceFileComponent  : public Component,
                                public ActionBroadcaster,
                                public ActionListener,
                                public ButtonListener,
                                public SliderListener
{
public:
    //==============================================================================
    ReferenceFileComponent (AudioDeviceManager& deviceManager);
    ~ReferenceFileComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    bool hasFileLoaded();
    AudioRegion getSelectedRegion();
    SegaudioFile* getLoadedFile();

    void setPlayable(bool isPlayable);

    void actionListenerCallback(const juce::String &message);

    void playAudio();
    void stopAudio();

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
    ScopedPointer<ReferenceContainer> container;
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<TextButton> loadFileButton;
    ScopedPointer<Slider> zoomSlider;
    ScopedPointer<Label> zoomLabel2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceFileComponent)
};

//[EndFile] You can add extra defines here...

//[/EndFile]

#endif   // __JUCE_HEADER_C3B8F999FE9961C4__
