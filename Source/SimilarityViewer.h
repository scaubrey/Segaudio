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

#ifndef __JUCE_HEADER_685B8D664892D24A__
#define __JUCE_HEADER_685B8D664892D24A__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioAnalysisController.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SimilarityViewer  : public Component,
                          public ActionBroadcaster,
                          public SliderListener,
                          public ButtonListener,
                          public ComboBoxListener
{
public:
    //==============================================================================
    SimilarityViewer ();
    ~SimilarityViewer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setDistanceArray(Array<float> newArray, float maxDistance);
    void drawThreshold(Graphics &g);
    void drawSimilarityFunction(Graphics &g);

    void setReadyToCompare(bool ready);

    void getAudioRegionsUnderThreshold();

    void drawRegions(Graphics &g);

    void updateRegions();

    Array<AudioRegion> getCandidateRegions();

    void updateSimilarityFunction();

    void updateComponent();

    void clear();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


    Array<float> distanceArray;
    Array<float> filteredDistanceArray;

    float maxDistance;

    bool readyToCompare;
    AudioAnalysisController analysisController;

    float threshold;
    float stickyness;
    float smoothness;

    Array<AudioRegion> regionCandidates;


    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Component> simControlsContainer;
    ScopedPointer<Slider> thresholdSlider;
    ScopedPointer<Label> thresholdLabel;
    ScopedPointer<TextButton> calcSimButton;
    ScopedPointer<ToggleButton> rmsFeatureToggle;
    ScopedPointer<ToggleButton> sfFeatureToggle;
    ScopedPointer<Component> graphContainer;
    ScopedPointer<ToggleButton> mfccFeatureToggle;
    ScopedPointer<Slider> stickynessSlider;
    ScopedPointer<Label> stickynessLabel;
    ScopedPointer<Slider> smoothnessSlider;
    ScopedPointer<Label> smoothnessLabel;
    ScopedPointer<ComboBox> presetComboBox;
    ScopedPointer<Label> presetsLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimilarityViewer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_685B8D664892D24A__
