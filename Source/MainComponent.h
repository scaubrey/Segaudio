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

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioAnalysisController.h"
#include "SegaudioModel.h"
#include "ReferenceFileComponent.h"
#include "TargetFileComponent.h"
#include "ControlPanelComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public ActionListener
{
public:
    //==============================================================================
    MainComponent (AudioAnalysisController &analysisController);
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    virtual void actionListenerCallback(const String &message);

    void updateTargetComponent();

    bool isReadyToCompare();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    AudioAnalysisController* analysisController;
    AudioDeviceManager deviceManager;
    SegaudioModel* appModel;

    bool isRefFileLoaded;
    bool isTargetFileLoaded;
    bool isRegionSelected;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ReferenceFileComponent> referenceFileComponent;
    ScopedPointer<TargetFileComponent> targetFileComponent;
    ScopedPointer<ControlPanelComponent> controlPanelComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
