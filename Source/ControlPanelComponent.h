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

    /*! gets the current cluster parameters shown on the UI
        @return ClusterParameters*
    */
    ClusterParameters* getClusterParams();

    /*! sets cluster parameters on the UI, primarily from the search function
        @param ClusterParameters* clusterParams
        @return void
    */
    void setClusterParams(ClusterParameters* clusterParams);

    /*! gets current signal features for use shown on the UI
        @return SignalFeaturesToUse*
    */
    SignalFeaturesToUse* getSignalFeaturesToUse(SignalFeaturesToUse* featuresToUse);

    /*! gets current export parameters on the UI
        @return ExportParameters*
    */
    ExportParameters* getExportParameters(ExportParameters* exportParams);

    /*! enables the UI for calculations
        @param bool readyForCalc
        @return void
    */
    void setCalcEnabled(bool readyForCalc);

    /*! partially enable UI for post-calculation tuning - not implemented yet
        @param bool readyToTune
        @return void
    */
    void setClusterTuningEnabled(bool readyToTune);

    /*! update UI count when there are new regions available
        @param Array<AudioRegion>* newRegions
        @return void
    */
    void newRegionsUpdate(Array<AudioRegion>* newRegions);

    /*! gets current search aparmaters on the UI
        @param SearchParameters* searchParams
        @return void
    */
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
    ScopedPointer<ToggleButton> scFeatureToggle;
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
    ScopedPointer<TextButton> exportTxtButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanelComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B5FA465D82E29D30__
