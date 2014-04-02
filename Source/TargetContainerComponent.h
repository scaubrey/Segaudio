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

#ifndef __JUCE_HEADER_3C8A12E4FBE1152B__
#define __JUCE_HEADER_3C8A12E4FBE1152B__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioSourceSelector.h"
#include "SimilarityViewer.h"
#include "AudioRegion.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TargetContainer  : public Component,
                         public ActionBroadcaster,
                         public ActionListener
{
public:
    //==============================================================================
    TargetContainer ();
    ~TargetContainer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setFile(File newFile);

    void update(ClusterParameters* clusterTuningParams, Array<AudioRegion> newCandidateRegions, Array<float>* newDistances, float maxDistance);

    bool hasFileLoaded();
    AudioRegion getSelectedRegion();
    SegaudioFile* getLoadedFile();

    void startAudio();
    void stopAudio();

    float getPositionBarTime();

    void actionListenerCallback(const String &message);

    void setCalculatingMask(bool status);


    void clearSimilarity();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioSourceSelector> audioSelector;
    ScopedPointer<SimilarityViewer> similarityViewer;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetContainer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3C8A12E4FBE1152B__
