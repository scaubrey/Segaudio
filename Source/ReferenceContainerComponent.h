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

#ifndef __JUCE_HEADER_529FE3EBF5AB5ECB__
#define __JUCE_HEADER_529FE3EBF5AB5ECB__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioSourceSelector.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ReferenceContainer  : public Component,
                            public ActionBroadcaster,
                            public ActionListener
{
public:
    //==============================================================================
    ReferenceContainer ();
    ~ReferenceContainer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setFile(File &newFile);

    void setCandidateRegions(Array<AudioRegion> newCandidateRegions);

    bool hasFileLoaded();
    AudioRegion getSelectedRegion();
    
    SegaudioFile* getLoadedFile();

    void clearRegion();

    void startAudio();
    void stopAudio();

    float getPositionBarTime();
    
    void actionListenerCallback(const String &message);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioSourceSelector> audioSelector;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceContainer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_529FE3EBF5AB5ECB__
