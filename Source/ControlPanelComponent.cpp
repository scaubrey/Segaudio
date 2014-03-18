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

//[Headers] You can add your own extra header files here...
#include "SegaudioModel.h"
//[/Headers]

#include "ControlPanelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ControlPanelComponent::ControlPanelComponent ()
{
    addAndMakeVisible (thresholdSlider = new Slider ("thresholdSlider"));
    thresholdSlider->setRange (0, 1, 0.01);
    thresholdSlider->setSliderStyle (Slider::LinearHorizontal);
    thresholdSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    thresholdSlider->addListener (this);

    addAndMakeVisible (thresholdLabel = new Label ("new label",
                                                   TRANS("Threshold")));
    thresholdLabel->setFont (Font (15.00f, Font::plain));
    thresholdLabel->setJustificationType (Justification::centredLeft);
    thresholdLabel->setEditable (false, false, false);
    thresholdLabel->setColour (TextEditor::textColourId, Colours::black);
    thresholdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (calcSimButton = new TextButton ("calcSimButton"));
    calcSimButton->setButtonText (TRANS("Calculate"));
    calcSimButton->addListener (this);
    calcSimButton->setColour (TextButton::buttonColourId, Colour (0xff97fc74));

    addAndMakeVisible (rmsFeatureToggle = new ToggleButton ("rmsFeatureToggle"));
    rmsFeatureToggle->setTooltip (TRANS("Root Mean Square"));
    rmsFeatureToggle->setButtonText (TRANS("RMS"));
    rmsFeatureToggle->addListener (this);
    rmsFeatureToggle->setToggleState (true, dontSendNotification);

    addAndMakeVisible (sfFeatureToggle = new ToggleButton ("sfFeatureToggle"));
    sfFeatureToggle->setTooltip (TRANS("Spectral Flux"));
    sfFeatureToggle->setButtonText (TRANS("SF"));
    sfFeatureToggle->addListener (this);

    addAndMakeVisible (mfccFeatureToggle = new ToggleButton ("mfccFeatureToggle"));
    mfccFeatureToggle->setButtonText (TRANS("MFCC"));
    mfccFeatureToggle->addListener (this);

    addAndMakeVisible (stickynessLabel = new Label ("stickynessLabel",
                                                    TRANS("Stickyness")));
    stickynessLabel->setFont (Font (15.00f, Font::plain));
    stickynessLabel->setJustificationType (Justification::centredLeft);
    stickynessLabel->setEditable (false, false, false);
    stickynessLabel->setColour (TextEditor::textColourId, Colours::black);
    stickynessLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (smoothnessLabel = new Label ("smoothnessLabel",
                                                    TRANS("Smoothing\n")));
    smoothnessLabel->setFont (Font (15.00f, Font::plain));
    smoothnessLabel->setJustificationType (Justification::centredLeft);
    smoothnessLabel->setEditable (false, false, false);
    smoothnessLabel->setColour (TextEditor::textColourId, Colours::black);
    smoothnessLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (presetComboBox = new ComboBox ("presetComboBox"));
    presetComboBox->setEditableText (false);
    presetComboBox->setJustificationType (Justification::centredLeft);
    presetComboBox->setTextWhenNothingSelected (TRANS("Custom"));
    presetComboBox->setTextWhenNoChoicesAvailable (String::empty);
    presetComboBox->addItem (TRANS("Speech"), 1);
    presetComboBox->addItem (TRANS("Music"), 2);
    presetComboBox->addItem (TRANS("Noise"), 3);
    presetComboBox->addItem (TRANS("Silence"), 4);
    presetComboBox->addListener (this);

    addAndMakeVisible (presetsLabel = new Label ("presetsLabel",
                                                 TRANS("Presets")));
    presetsLabel->setFont (Font (15.00f, Font::plain));
    presetsLabel->setJustificationType (Justification::centredLeft);
    presetsLabel->setEditable (false, false, false);
    presetsLabel->setColour (TextEditor::textColourId, Colours::black);
    presetsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (stickynessSlider = new Slider ("stickynessSlider"));
    stickynessSlider->setRange (0, 1, 0.01);
    stickynessSlider->setSliderStyle (Slider::LinearHorizontal);
    stickynessSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    stickynessSlider->addListener (this);

    addAndMakeVisible (smoothingSlider = new Slider ("smoothingSlider"));
    smoothingSlider->setRange (0, 1, 0.01);
    smoothingSlider->setSliderStyle (Slider::LinearHorizontal);
    smoothingSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    smoothingSlider->addListener (this);

    addAndMakeVisible (widthLabel = new Label ("widthLabel",
                                               TRANS("Width")));
    widthLabel->setFont (Font (15.00f, Font::plain));
    widthLabel->setJustificationType (Justification::centredLeft);
    widthLabel->setEditable (false, false, false);
    widthLabel->setColour (TextEditor::textColourId, Colours::black);
    widthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (widthSlider = new Slider ("widthSlider"));
    widthSlider->setRange (0, 1, 0.01);
    widthSlider->setSliderStyle (Slider::TwoValueHorizontal);
    widthSlider->setTextBoxStyle (Slider::NoTextBox, true, 40, 20);
    widthSlider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Cluster Tuning")));
    label->setFont (Font (18.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Feature Selection")));
    label2->setFont (Font (18.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (zcrFeatureToggle = new ToggleButton ("zcrFeatureToggle"));
    zcrFeatureToggle->setTooltip (TRANS("Zero Cross Rate"));
    zcrFeatureToggle->setButtonText (TRANS("ZCR"));
    zcrFeatureToggle->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    widthSlider->setMinAndMaxValues(0.0, 1.0); // allow all regions
    setEnabled(false);

    clusterParams = new ClusterParameters();
    //[/Constructor]
}

ControlPanelComponent::~ControlPanelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    thresholdSlider = nullptr;
    thresholdLabel = nullptr;
    calcSimButton = nullptr;
    rmsFeatureToggle = nullptr;
    sfFeatureToggle = nullptr;
    mfccFeatureToggle = nullptr;
    stickynessLabel = nullptr;
    smoothnessLabel = nullptr;
    presetComboBox = nullptr;
    presetsLabel = nullptr;
    stickynessSlider = nullptr;
    smoothingSlider = nullptr;
    widthLabel = nullptr;
    widthSlider = nullptr;
    label = nullptr;
    label2 = nullptr;
    zcrFeatureToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControlPanelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffc96d));

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, 260, 788, 4);

    g.setColour (Colours::black);
    g.setFont (Font ("Arial", 22.00f, Font::plain));
    g.drawText (TRANS("Control Panel"),
                (getWidth() / 2) + -70, 4, 140, 36,
                Justification::centred, true);

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, 44, 788, 4);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControlPanelComponent::resized()
{
    thresholdSlider->setBounds (proportionOfWidth (0.0279f), proportionOfHeight (0.4169f), proportionOfWidth (0.8498f), 16);
    thresholdLabel->setBounds (proportionOfWidth (0.0186f), proportionOfHeight (0.3871f), 80, 17);
    calcSimButton->setBounds (getWidth() - 61 - 86, 224, 86, 20);
    rmsFeatureToggle->setBounds (96, proportionOfHeight (0.1787f), 50, 24);
    sfFeatureToggle->setBounds (24, proportionOfHeight (0.2283f), 50, 24);
    mfccFeatureToggle->setBounds (24, proportionOfHeight (0.1787f), 50, 24);
    stickynessLabel->setBounds (proportionOfWidth (0.0186f), proportionOfHeight (0.4467f), 72, 18);
    smoothnessLabel->setBounds (proportionOfWidth (0.0186f), proportionOfHeight (0.5050f), 80, 24);
    presetComboBox->setBounds (96, 96, 100, 24);
    presetsLabel->setBounds (21, 94, 60, 24);
    stickynessSlider->setBounds (proportionOfWidth (0.0279f), proportionOfHeight (0.4764f), proportionOfWidth (0.8498f), 16);
    smoothingSlider->setBounds (proportionOfWidth (0.0279f), proportionOfHeight (0.5360f), proportionOfWidth (0.8498f), 16);
    widthLabel->setBounds (proportionOfWidth (0.0186f), proportionOfHeight (0.5658f), 80, 24);
    widthSlider->setBounds (proportionOfWidth (0.0279f), proportionOfHeight (0.5955f), proportionOfWidth (0.8498f), 16);
    label->setBounds (16, 272, 150, 24);
    label2->setBounds (16, 56, 150, 24);
    zcrFeatureToggle->setBounds (96, proportionOfHeight (0.2283f), 50, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ControlPanelComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == thresholdSlider)
    {
        //[UserSliderCode_thresholdSlider] -- add your slider handling code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserSliderCode_thresholdSlider]
    }
    else if (sliderThatWasMoved == stickynessSlider)
    {
        //[UserSliderCode_stickynessSlider] -- add your slider handling code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserSliderCode_stickynessSlider]
    }
    else if (sliderThatWasMoved == smoothingSlider)
    {
        //[UserSliderCode_smoothingSlider] -- add your slider handling code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserSliderCode_smoothingSlider]
    }
    else if (sliderThatWasMoved == widthSlider)
    {
        //[UserSliderCode_widthSlider] -- add your slider handling code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserSliderCode_widthSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void ControlPanelComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == calcSimButton)
    {
        //[UserButtonCode_calcSimButton] -- add your button handler code here..
        sendActionMessage("calculateSimilarity");
        //[/UserButtonCode_calcSimButton]
    }
    else if (buttonThatWasClicked == rmsFeatureToggle)
    {
        //[UserButtonCode_rmsFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_rmsFeatureToggle]
    }
    else if (buttonThatWasClicked == sfFeatureToggle)
    {
        //[UserButtonCode_sfFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_sfFeatureToggle]
    }
    else if (buttonThatWasClicked == mfccFeatureToggle)
    {
        //[UserButtonCode_mfccFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_mfccFeatureToggle]
    }
    else if (buttonThatWasClicked == zcrFeatureToggle)
    {
        //[UserButtonCode_zcrFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_zcrFeatureToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ControlPanelComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetComboBox)
    {
        //[UserComboBoxCode_presetComboBox] -- add your combo box handling code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserComboBoxCode_presetComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
ClusterParameters* ControlPanelComponent::getClusterParams(){

    clusterParams->threshold = thresholdSlider->getValue();
    clusterParams->regionConnectionWidth = stickynessSlider->getValue();
    clusterParams->minRegionTimeWidth = widthSlider->getMinValue();
    clusterParams->maxRegionTimeWidth = widthSlider->getMaxValue();
    clusterParams->medianFilterWidth = smoothingSlider->getValue();

    return clusterParams;
}

SignalFeaturesToUse* ControlPanelComponent::getSignalFeaturesToUse(SignalFeaturesToUse* featuresToUse){

    featuresToUse->rms = rmsFeatureToggle->getToggleState();
    featuresToUse->mfcc = mfccFeatureToggle->getToggleState();
    featuresToUse->sf = sfFeatureToggle->getToggleState();
    featuresToUse->zcr = zcrFeatureToggle->getToggleState();

    return featuresToUse;
}

void ControlPanelComponent::setCalcEnabled(bool readyForCalc){
    setEnabled(readyForCalc);
    rmsFeatureToggle->setEnabled(readyForCalc);
    mfccFeatureToggle->setEnabled(readyForCalc);
    sfFeatureToggle->setEnabled(readyForCalc);
    calcSimButton->setEnabled(readyForCalc);
}

void ControlPanelComponent::setClusterTuningEnabled(bool readyToTune){
    thresholdSlider->setEnabled(readyToTune);
    smoothingSlider->setEnabled(readyToTune);
    widthSlider->setEnabled(readyToTune);
    stickynessSlider->setEnabled(readyToTune);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ControlPanelComponent" componentName=""
                 parentClasses="public Component, public ActionBroadcaster" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffc96d">
    <RECT pos="12 260 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
    <TEXT pos="-70C 4 140 36" fill="solid: ff000000" hasStroke="0" text="Control Panel"
          fontname="Arial" fontsize="22" bold="0" italic="0" justification="36"/>
    <RECT pos="12 44 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="thresholdSlider" id="2ddea841d6d652ab" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="2.794% 41.687% 84.983% 16"
          min="0" max="1" int="0.010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4f564f498f058971" memberName="thresholdLabel"
         virtualName="" explicitFocusOrder="0" pos="1.863% 38.71% 80 17"
         edTextCol="ff000000" edBkgCol="0" labelText="Threshold" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="calcSimButton" id="9ce3f6b1681a8658" memberName="calcSimButton"
              virtualName="" explicitFocusOrder="0" pos="61Rr 224 86 20" bgColOff="ff97fc74"
              buttonText="Calculate" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="rmsFeatureToggle" id="92a1f05376de0623" memberName="rmsFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="96 17.866% 50 24"
                tooltip="Root Mean Square" buttonText="RMS" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="sfFeatureToggle" id="9eb603aec59d0a37" memberName="sfFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="24 22.829% 50 24"
                tooltip="Spectral Flux" buttonText="SF" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="mfccFeatureToggle" id="f946313658ff3956" memberName="mfccFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="24 17.866% 50 24"
                buttonText="MFCC" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="stickynessLabel" id="32983a34059e5df1" memberName="stickynessLabel"
         virtualName="" explicitFocusOrder="0" pos="1.863% 44.665% 72 18"
         edTextCol="ff000000" edBkgCol="0" labelText="Stickyness" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="smoothnessLabel" id="b8d50e7cbed6b69c" memberName="smoothnessLabel"
         virtualName="" explicitFocusOrder="0" pos="1.863% 50.496% 80 24"
         edTextCol="ff000000" edBkgCol="0" labelText="Smoothing&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="presetComboBox" id="2a56f7bafaec946f" memberName="presetComboBox"
            virtualName="" explicitFocusOrder="0" pos="96 96 100 24" editable="0"
            layout="33" items="Speech&#10;Music&#10;Noise&#10;Silence" textWhenNonSelected="Custom"
            textWhenNoItems=""/>
  <LABEL name="presetsLabel" id="555dd5c766efb7a1" memberName="presetsLabel"
         virtualName="" explicitFocusOrder="0" pos="21 94 60 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Presets" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="stickynessSlider" id="64d7b64d40a66223" memberName="stickynessSlider"
          virtualName="" explicitFocusOrder="0" pos="2.794% 47.643% 84.983% 16"
          min="0" max="1" int="0.010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="smoothingSlider" id="11086795620394cc" memberName="smoothingSlider"
          virtualName="" explicitFocusOrder="0" pos="2.794% 53.598% 84.983% 16"
          min="0" max="1" int="0.010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="widthLabel" id="fb630a6f3e08259a" memberName="widthLabel"
         virtualName="" explicitFocusOrder="0" pos="1.863% 56.576% 80 24"
         edTextCol="ff000000" edBkgCol="0" labelText="Width" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="widthSlider" id="51e7ac04e76a9203" memberName="widthSlider"
          virtualName="" explicitFocusOrder="0" pos="2.794% 59.553% 84.983% 16"
          min="0" max="1" int="0.010000000000000000208" style="TwoValueHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4feb41a7e4880c44" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 272 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cluster Tuning" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e7329f5e02bd959" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 56 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feature Selection" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="zcrFeatureToggle" id="e8b2bb7bef7e0e1f" memberName="zcrFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="96 22.829% 50 24"
                tooltip="Zero Cross Rate" buttonText="ZCR" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
