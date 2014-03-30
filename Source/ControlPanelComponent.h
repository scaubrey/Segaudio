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

#ifndef __JUCE_HEADER_B5FA465D82E29D30__
#define __JUCE_HEADER_B5FA465D82E29D30__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ControlPanelComponent  : public Component,
                               public ActionBroadcaster,
                               public SliderListener,
                               public ButtonListener,
                               public ComboBoxListener
{
public:
    //==============================================================================
    ControlPanelComponent ();
    ~ControlPanelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    ClusterParameters* getClusterParams();
    void setClusterParams(ClusterParameters* clusterParams);

    SignalFeaturesToUse* getSignalFeaturesToUse(SignalFeaturesToUse* featuresToUse);

    ExportParameters* getExportParameters(ExportParameters* exportParams);

    void setCalcEnabled(bool readyForCalc);
    void setClusterTuningEnabled(bool readyToTune);

    void newRegionsUpdate(Array<AudioRegion> &newRegions);

    void getSearchParameters(SearchParameters* searchParams);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<ClusterParameters> clusterParams;
    ScopedPointer<SignalFeaturesToUse> featuresToUse;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> thresholdSlider;
    ScopedPointer<Label> thresholdLabel;
    ScopedPointer<TextButton> calcSimButton;
    ScopedPointer<ToggleButton> rmsFeatureToggle;
    ScopedPointer<ToggleButton> sfFeatureToggle;
    ScopedPointer<ToggleButton> mfccFeatureToggle;
    ScopedPointer<Label> stickynessLabel;
    ScopedPointer<ComboBox> presetComboBox;
    ScopedPointer<Label> presetsLabel;
    ScopedPointer<Slider> stickynessSlider;
    ScopedPointer<Label> widthLabel;
    ScopedPointer<Slider> widthSlider;
    ScopedPointer<Label> header2;
    ScopedPointer<Label> header1;
    ScopedPointer<ToggleButton> zcrFeatureToggle;
    ScopedPointer<ToggleButton> invertRegionsToggle;
    ScopedPointer<TextButton> exportSeparateButton;
    ScopedPointer<Label> regionDescriptionLabel;
    ScopedPointer<Label> regionCountLabel;
    ScopedPointer<ToggleButton> saveSingleFileToggleButton;
    ScopedPointer<Label> widthMinLabel;
    ScopedPointer<Label> widthMaxLabel;
    ScopedPointer<ComboBox> numRegionsComboBox;
    ScopedPointer<Label> header3;
    ScopedPointer<ComboBox> searchPercentComboBox;
    ScopedPointer<TextButton> searchButton;
    ScopedPointer<ToggleButton> widthFilterSearchToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanelComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B5FA465D82E29D30__
