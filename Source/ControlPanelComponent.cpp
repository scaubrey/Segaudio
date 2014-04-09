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
    thresholdSlider->setRange (0, 1, 1e-06);
    thresholdSlider->setSliderStyle (Slider::LinearHorizontal);
    thresholdSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 60, 20);
    thresholdSlider->addListener (this);

    addAndMakeVisible (thresholdLabel = new Label ("new label",
                                                   TRANS("Threshold")));
    thresholdLabel->setFont (Font (15.00f, Font::plain));
    thresholdLabel->setJustificationType (Justification::centredLeft);
    thresholdLabel->setEditable (false, false, false);
    thresholdLabel->setColour (Label::textColourId, Colours::white);
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
    rmsFeatureToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (scFeatureToggle = new ToggleButton ("scFeatureToggle"));
    scFeatureToggle->setTooltip (TRANS("Spectral Centroid"));
    scFeatureToggle->setButtonText (TRANS("SC"));
    scFeatureToggle->addListener (this);
    scFeatureToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (mfccFeatureToggle = new ToggleButton ("mfccFeatureToggle"));
    mfccFeatureToggle->setButtonText (TRANS("MFCC"));
    mfccFeatureToggle->addListener (this);
    mfccFeatureToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (stickynessLabel = new Label ("stickynessLabel",
                                                    TRANS("Smoothing")));
    stickynessLabel->setFont (Font (15.00f, Font::plain));
    stickynessLabel->setJustificationType (Justification::centredLeft);
    stickynessLabel->setEditable (false, false, false);
    stickynessLabel->setColour (Label::textColourId, Colours::white);
    stickynessLabel->setColour (TextEditor::textColourId, Colours::black);
    stickynessLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
    presetsLabel->setColour (Label::textColourId, Colours::white);
    presetsLabel->setColour (TextEditor::textColourId, Colours::black);
    presetsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (stickynessSlider = new Slider ("stickynessSlider"));
    stickynessSlider->setRange (0, 1, 0.01);
    stickynessSlider->setSliderStyle (Slider::LinearHorizontal);
    stickynessSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    stickynessSlider->addListener (this);

    addAndMakeVisible (widthLabel = new Label ("widthLabel",
                                               TRANS("Width Filter")));
    widthLabel->setFont (Font (15.00f, Font::plain));
    widthLabel->setJustificationType (Justification::centredLeft);
    widthLabel->setEditable (false, false, false);
    widthLabel->setColour (Label::textColourId, Colours::white);
    widthLabel->setColour (TextEditor::textColourId, Colours::black);
    widthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (widthSlider = new Slider ("widthSlider"));
    widthSlider->setRange (0, 1, 0.01);
    widthSlider->setSliderStyle (Slider::TwoValueHorizontal);
    widthSlider->setTextBoxStyle (Slider::NoTextBox, true, 40, 20);
    widthSlider->addListener (this);

    addAndMakeVisible (header2 = new Label ("header2",
                                            TRANS("Cluster Tuning")));
    header2->setFont (Font (18.00f, Font::plain));
    header2->setJustificationType (Justification::centredLeft);
    header2->setEditable (false, false, false);
    header2->setColour (Label::textColourId, Colours::white);
    header2->setColour (TextEditor::textColourId, Colours::black);
    header2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (header1 = new Label ("header1",
                                            TRANS("Feature Selection")));
    header1->setFont (Font (18.00f, Font::plain));
    header1->setJustificationType (Justification::centredLeft);
    header1->setEditable (false, false, false);
    header1->setColour (Label::textColourId, Colours::white);
    header1->setColour (TextEditor::textColourId, Colours::black);
    header1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (zcrFeatureToggle = new ToggleButton ("zcrFeatureToggle"));
    zcrFeatureToggle->setTooltip (TRANS("Zero Cross Rate"));
    zcrFeatureToggle->setButtonText (TRANS("ZCR"));
    zcrFeatureToggle->addListener (this);
    zcrFeatureToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (invertRegionsToggle = new ToggleButton ("invertRegionsToggle"));
    invertRegionsToggle->setTooltip (TRANS("Invert Regions"));
    invertRegionsToggle->setButtonText (TRANS("Invert Regions"));
    invertRegionsToggle->addListener (this);
    invertRegionsToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (exportSeparateButton = new TextButton ("exportSeparateButton"));
    exportSeparateButton->setButtonText (TRANS("Export Audio"));
    exportSeparateButton->addListener (this);
    exportSeparateButton->setColour (TextButton::buttonColourId, Colours::coral);

    addAndMakeVisible (regionDescriptionLabel = new Label ("regionDescriptionLabel",
                                                           TRANS("# Regions:")));
    regionDescriptionLabel->setFont (Font (15.00f, Font::plain));
    regionDescriptionLabel->setJustificationType (Justification::centredLeft);
    regionDescriptionLabel->setEditable (false, false, false);
    regionDescriptionLabel->setColour (Label::textColourId, Colours::white);
    regionDescriptionLabel->setColour (TextEditor::textColourId, Colours::black);
    regionDescriptionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (regionCountLabel = new Label ("new label",
                                                     TRANS("0")));
    regionCountLabel->setFont (Font (15.00f, Font::plain));
    regionCountLabel->setJustificationType (Justification::centredLeft);
    regionCountLabel->setEditable (false, false, false);
    regionCountLabel->setColour (Label::textColourId, Colours::white);
    regionCountLabel->setColour (TextEditor::textColourId, Colours::black);
    regionCountLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveSingleFileToggleButton = new ToggleButton ("saveSingleFileToggleButton"));
    saveSingleFileToggleButton->setButtonText (TRANS("As One File"));
    saveSingleFileToggleButton->addListener (this);
    saveSingleFileToggleButton->setToggleState (true, dontSendNotification);
    saveSingleFileToggleButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (widthMinLabel = new Label ("widthMinLabel",
                                                  TRANS("0")));
    widthMinLabel->setFont (Font (15.00f, Font::plain));
    widthMinLabel->setJustificationType (Justification::centredLeft);
    widthMinLabel->setEditable (false, false, false);
    widthMinLabel->setColour (Label::textColourId, Colours::white);
    widthMinLabel->setColour (TextEditor::textColourId, Colours::black);
    widthMinLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (widthMaxLabel = new Label ("widthMinLabel",
                                                  TRANS("0")));
    widthMaxLabel->setFont (Font (15.00f, Font::plain));
    widthMaxLabel->setJustificationType (Justification::centredLeft);
    widthMaxLabel->setEditable (false, false, false);
    widthMaxLabel->setColour (Label::textColourId, Colours::white);
    widthMaxLabel->setColour (TextEditor::textColourId, Colours::black);
    widthMaxLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (numRegionsComboBox = new ComboBox ("numRegionsComboBox"));
    numRegionsComboBox->setEditableText (false);
    numRegionsComboBox->setJustificationType (Justification::centredLeft);
    numRegionsComboBox->setTextWhenNothingSelected (TRANS("# of Regions"));
    numRegionsComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    numRegionsComboBox->addItem (TRANS("1"), 1);
    numRegionsComboBox->addItem (TRANS("2"), 2);
    numRegionsComboBox->addItem (TRANS("3"), 3);
    numRegionsComboBox->addItem (TRANS("4"), 4);
    numRegionsComboBox->addItem (TRANS("5"), 5);
    numRegionsComboBox->addItem (TRANS("6"), 6);
    numRegionsComboBox->addItem (TRANS("7"), 7);
    numRegionsComboBox->addItem (TRANS("8"), 8);
    numRegionsComboBox->addItem (TRANS("9"), 9);
    numRegionsComboBox->addListener (this);

    addAndMakeVisible (header3 = new Label ("header3",
                                            TRANS("Smart Search")));
    header3->setFont (Font (18.00f, Font::plain));
    header3->setJustificationType (Justification::centredLeft);
    header3->setEditable (false, false, false);
    header3->setColour (Label::textColourId, Colours::white);
    header3->setColour (TextEditor::textColourId, Colours::black);
    header3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (searchPercentComboBox = new ComboBox ("searchPercentComboBox"));
    searchPercentComboBox->setEditableText (false);
    searchPercentComboBox->setJustificationType (Justification::centredLeft);
    searchPercentComboBox->setTextWhenNothingSelected (TRANS("% of File"));
    searchPercentComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    searchPercentComboBox->addItem (TRANS("1"), 1);
    searchPercentComboBox->addItem (TRANS("2"), 2);
    searchPercentComboBox->addItem (TRANS("3"), 3);
    searchPercentComboBox->addItem (TRANS("4"), 4);
    searchPercentComboBox->addItem (TRANS("5"), 5);
    searchPercentComboBox->addItem (TRANS("6"), 6);
    searchPercentComboBox->addItem (TRANS("7"), 7);
    searchPercentComboBox->addItem (TRANS("8"), 8);
    searchPercentComboBox->addItem (TRANS("9"), 9);
    searchPercentComboBox->addItem (TRANS("10"), 10);
    searchPercentComboBox->addItem (TRANS("15"), 11);
    searchPercentComboBox->addItem (TRANS("20"), 12);
    searchPercentComboBox->addItem (TRANS("25"), 13);
    searchPercentComboBox->addItem (TRANS("30"), 14);
    searchPercentComboBox->addItem (TRANS("35"), 15);
    searchPercentComboBox->addItem (TRANS("40"), 16);
    searchPercentComboBox->addItem (TRANS("45"), 17);
    searchPercentComboBox->addItem (TRANS("50"), 18);
    searchPercentComboBox->addListener (this);

    addAndMakeVisible (searchButton = new TextButton ("searchButton"));
    searchButton->setButtonText (TRANS("Search"));
    searchButton->addListener (this);

    addAndMakeVisible (widthFilterSearchToggle = new ToggleButton ("widthFilterSearchToggle"));
    widthFilterSearchToggle->setTooltip (TRANS("Invert Regions"));
    widthFilterSearchToggle->setButtonText (TRANS("Use Width Filter"));
    widthFilterSearchToggle->addListener (this);
    widthFilterSearchToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (exportTxtButton = new TextButton ("exportTxtButton"));
    exportTxtButton->setButtonText (TRANS("Export CSV"));
    exportTxtButton->addListener (this);
    exportTxtButton->setColour (TextButton::buttonColourId, Colours::coral);


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
    scFeatureToggle = nullptr;
    mfccFeatureToggle = nullptr;
    stickynessLabel = nullptr;
    presetComboBox = nullptr;
    presetsLabel = nullptr;
    stickynessSlider = nullptr;
    widthLabel = nullptr;
    widthSlider = nullptr;
    header2 = nullptr;
    header1 = nullptr;
    zcrFeatureToggle = nullptr;
    invertRegionsToggle = nullptr;
    exportSeparateButton = nullptr;
    regionDescriptionLabel = nullptr;
    regionCountLabel = nullptr;
    saveSingleFileToggleButton = nullptr;
    widthMinLabel = nullptr;
    widthMaxLabel = nullptr;
    numRegionsComboBox = nullptr;
    header3 = nullptr;
    searchPercentComboBox = nullptr;
    searchButton = nullptr;
    widthFilterSearchToggle = nullptr;
    exportTxtButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControlPanelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff4d4d4d));

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, proportionOfHeight (0.2928f), 788, 4);

    g.setColour (Colours::white);
    g.setFont (Font ("Arial", 22.00f, Font::plain));
    g.drawText (TRANS("Control Panel"),
                (getWidth() / 2) + -70, 4, 140, 36,
                Justification::centred, true);

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, proportionOfHeight (0.0546f), 788, 4);

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, proportionOfHeight (0.7097f), 788, 4);

    g.setColour (Colour (0xff2a75a5));
    g.fillRect (12, proportionOfHeight (0.8883f), 788, 4);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControlPanelComponent::resized()
{
    thresholdSlider->setBounds (proportionOfWidth (0.0288f), proportionOfHeight (0.3983f), proportionOfWidth (0.8489f), 16);
    thresholdLabel->setBounds (proportionOfWidth (0.0185f), proportionOfHeight (0.3673f), 80, 17);
    calcSimButton->setBounds (getWidth() - 61 - 86, 184, 86, 20);
    rmsFeatureToggle->setBounds (96, proportionOfHeight (0.1774f), 50, 24);
    scFeatureToggle->setBounds (24, proportionOfHeight (0.2270f), 50, 24);
    mfccFeatureToggle->setBounds (24, proportionOfHeight (0.1774f), 50, 24);
    stickynessLabel->setBounds (proportionOfWidth (0.0185f), proportionOfHeight (0.4280f), 72, 18);
    presetComboBox->setBounds (96, proportionOfHeight (0.1191f), 100, 24);
    presetsLabel->setBounds (21, proportionOfHeight (0.1166f), 60, 24);
    stickynessSlider->setBounds (proportionOfWidth (0.0288f), proportionOfHeight (0.4578f), proportionOfWidth (0.8489f), 16);
    widthLabel->setBounds (proportionOfWidth (0.0185f), proportionOfHeight (0.5248f), 80, 24);
    widthSlider->setBounds (proportionOfWidth (0.0288f), proportionOfHeight (0.5546f), proportionOfWidth (0.8489f), 16);
    header2->setBounds (16, proportionOfHeight (0.3176f), 150, 24);
    header1->setBounds (16, proportionOfHeight (0.0695f), 150, 24);
    zcrFeatureToggle->setBounds (96, proportionOfHeight (0.2270f), 50, 24);
    invertRegionsToggle->setBounds (proportionOfWidth (0.0288f), proportionOfHeight (0.6452f), 120, 24);
    exportSeparateButton->setBounds (24, proportionOfHeight (0.9132f), 104, 24);
    regionDescriptionLabel->setBounds (getWidth() - 138, proportionOfHeight (0.6340f), 72, 24);
    regionCountLabel->setBounds ((getWidth() - 138) + 80, proportionOfHeight (0.6340f), 30, 25);
    saveSingleFileToggleButton->setBounds ((24) + 0, proportionOfHeight (0.9529f), 112, 24);
    widthMinLabel->setBounds ((proportionOfWidth (0.0288f)) + 0, (proportionOfHeight (0.5546f)) + 17, 56, 24);
    widthMaxLabel->setBounds ((proportionOfWidth (0.0288f)) + roundFloatToInt ((proportionOfWidth (0.8489f)) * 0.9647f), (proportionOfHeight (0.5546f)) + 17, 48, 24);
    numRegionsComboBox->setBounds ((16) + 8, proportionOfHeight (0.7841f), 120, 24);
    header3->setBounds (16, proportionOfHeight (0.7246f), 120, 24);
    searchPercentComboBox->setBounds ((16) + 144, proportionOfHeight (0.7841f), 104, 24);
    searchButton->setBounds (24, proportionOfHeight (0.8437f), 96, 24);
    widthFilterSearchToggle->setBounds ((16) + 136, proportionOfHeight (0.7246f), 120, 24);
    exportTxtButton->setBounds ((24) + 152, proportionOfHeight (0.9132f), 104, 24);
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
    else if (sliderThatWasMoved == widthSlider)
    {
        //[UserSliderCode_widthSlider] -- add your slider handling code here..
        widthMinLabel->setText(String(widthSlider->getMinValue()*100) + "%", dontSendNotification);
        widthMaxLabel->setText(String(widthSlider->getMaxValue()*100) + "%", dontSendNotification);
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
    else if (buttonThatWasClicked == scFeatureToggle)
    {
        //[UserButtonCode_scFeatureToggle] -- add your button handler code here..
        //[/UserButtonCode_scFeatureToggle]
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
    else if (buttonThatWasClicked == invertRegionsToggle)
    {
        //[UserButtonCode_invertRegionsToggle] -- add your button handler code here..
        sendActionMessage("clusterParamsChanged");
        //[/UserButtonCode_invertRegionsToggle]
    }
    else if (buttonThatWasClicked == exportSeparateButton)
    {
        //[UserButtonCode_exportSeparateButton] -- add your button handler code here..
        sendActionMessage("exportAudio");
        //[/UserButtonCode_exportSeparateButton]
    }
    else if (buttonThatWasClicked == saveSingleFileToggleButton)
    {
        //[UserButtonCode_saveSingleFileToggleButton] -- add your button handler code here..
        //[/UserButtonCode_saveSingleFileToggleButton]
    }
    else if (buttonThatWasClicked == searchButton)
    {
        //[UserButtonCode_searchButton] -- add your button handler code here..
        sendActionMessage("search");
        //[/UserButtonCode_searchButton]
    }
    else if (buttonThatWasClicked == widthFilterSearchToggle)
    {
        //[UserButtonCode_widthFilterSearchToggle] -- add your button handler code here..
        //[/UserButtonCode_widthFilterSearchToggle]
    }
    else if (buttonThatWasClicked == exportTxtButton)
    {
        //[UserButtonCode_exportTxtButton] -- add your button handler code here..
        sendActionMessage("exportCsv");
        //[/UserButtonCode_exportTxtButton]
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

        if(presetComboBox->getText() == "Speech"){
            mfccFeatureToggle->setToggleState(true, dontSendNotification);
            rmsFeatureToggle->setToggleState(false, dontSendNotification);
            scFeatureToggle->setToggleState(false, dontSendNotification);
            zcrFeatureToggle->setToggleState(false, dontSendNotification);
        }
        else if(presetComboBox->getText() == "Silence"){
            mfccFeatureToggle->setToggleState(false, dontSendNotification);
            rmsFeatureToggle->setToggleState(true, dontSendNotification);
            scFeatureToggle->setToggleState(false, dontSendNotification);
            zcrFeatureToggle->setToggleState(false, dontSendNotification);
        }
        else if(presetComboBox->getText() == "Noise"){
            mfccFeatureToggle->setToggleState(false, dontSendNotification);
            rmsFeatureToggle->setToggleState(false, dontSendNotification);
            scFeatureToggle->setToggleState(false, dontSendNotification);
            zcrFeatureToggle->setToggleState(true, dontSendNotification);
        }
        else if(presetComboBox->getText() == "Music"){
            mfccFeatureToggle->setToggleState(false, dontSendNotification);
            rmsFeatureToggle->setToggleState(false, dontSendNotification);
            scFeatureToggle->setToggleState(true, dontSendNotification);
            zcrFeatureToggle->setToggleState(false, dontSendNotification);
        }
        //[/UserComboBoxCode_presetComboBox]
    }
    else if (comboBoxThatHasChanged == numRegionsComboBox)
    {
        //[UserComboBoxCode_numRegionsComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_numRegionsComboBox]
    }
    else if (comboBoxThatHasChanged == searchPercentComboBox)
    {
        //[UserComboBoxCode_searchPercentComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_searchPercentComboBox]
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
//    clusterParams->medianFilterWidth = smoothingSlider->getValue();

    clusterParams->shouldInvertRegions = invertRegionsToggle->getToggleState();

    return clusterParams;
}

void ControlPanelComponent::setClusterParams(ClusterParameters* clusterParams){
    thresholdSlider->setValue(clusterParams->threshold);
    stickynessSlider->setValue(clusterParams->regionConnectionWidth);
}


SignalFeaturesToUse* ControlPanelComponent::getSignalFeaturesToUse(SignalFeaturesToUse* featuresToUse){

    featuresToUse->rms = rmsFeatureToggle->getToggleState();
    featuresToUse->mfcc = mfccFeatureToggle->getToggleState();
    featuresToUse->sc = scFeatureToggle->getToggleState();
    featuresToUse->zcr = zcrFeatureToggle->getToggleState();

    return featuresToUse;
}

ExportParameters* ControlPanelComponent::getExportParameters(ExportParameters* exportParams){

    exportParams->asOneFile = saveSingleFileToggleButton->getToggleState();

    return exportParams;
}

void ControlPanelComponent::setCalcEnabled(bool readyForCalc){
    setEnabled(readyForCalc);
    rmsFeatureToggle->setEnabled(readyForCalc);
    mfccFeatureToggle->setEnabled(readyForCalc);
    scFeatureToggle->setEnabled(readyForCalc);
    calcSimButton->setEnabled(readyForCalc);
}

void ControlPanelComponent::setClusterTuningEnabled(bool readyToTune){
    thresholdSlider->setEnabled(readyToTune);
//    smoothingSlider->setEnabled(readyToTune);
    widthSlider->setEnabled(readyToTune);
    stickynessSlider->setEnabled(readyToTune);
}

void ControlPanelComponent::newRegionsUpdate(Array<AudioRegion> &newRegions){
    regionCountLabel->setText(String(newRegions.size()), dontSendNotification);
}

void ControlPanelComponent::getSearchParameters(SearchParameters* searchParams){
    searchParams->numRegions = numRegionsComboBox->getText().getIntValue();
    searchParams->filePercentage = float(searchPercentComboBox->getText().getFloatValue()) / 100.0f;

    searchParams->useWidthFilter = widthFilterSearchToggle->getToggleState();
    searchParams->minWidth = widthSlider->getMinValue();
    searchParams->maxWidth = widthSlider->getMaxValue();

//    return searchParams;
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
  <BACKGROUND backgroundColour="ff4d4d4d">
    <RECT pos="12 29.28% 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
    <TEXT pos="-70C 4 140 36" fill="solid: ffffffff" hasStroke="0" text="Control Panel"
          fontname="Arial" fontsize="22" bold="0" italic="0" justification="36"/>
    <RECT pos="12 5.459% 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
    <RECT pos="12 70.968% 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
    <RECT pos="12 88.834% 788 4" fill="solid: ff2a75a5" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="thresholdSlider" id="2ddea841d6d652ab" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="2.884% 39.826% 84.89% 16"
          min="0" max="1" int="9.9999999999999995475e-07" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4f564f498f058971" memberName="thresholdLabel"
         virtualName="" explicitFocusOrder="0" pos="1.845% 36.725% 80 17"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Threshold"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="calcSimButton" id="9ce3f6b1681a8658" memberName="calcSimButton"
              virtualName="" explicitFocusOrder="0" pos="61Rr 184 86 20" bgColOff="ff97fc74"
              buttonText="Calculate" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="rmsFeatureToggle" id="92a1f05376de0623" memberName="rmsFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="96 17.742% 50 24"
                tooltip="Root Mean Square" txtcol="ffffffff" buttonText="RMS"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="scFeatureToggle" id="9eb603aec59d0a37" memberName="scFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="24 22.705% 50 24"
                tooltip="Spectral Centroid" txtcol="ffffffff" buttonText="SC"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="mfccFeatureToggle" id="f946313658ff3956" memberName="mfccFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="24 17.742% 50 24"
                txtcol="ffffffff" buttonText="MFCC" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <LABEL name="stickynessLabel" id="32983a34059e5df1" memberName="stickynessLabel"
         virtualName="" explicitFocusOrder="0" pos="1.845% 42.804% 72 18"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Smoothing"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="presetComboBox" id="2a56f7bafaec946f" memberName="presetComboBox"
            virtualName="" explicitFocusOrder="0" pos="96 11.911% 100 24"
            editable="0" layout="33" items="Speech&#10;Music&#10;Noise&#10;Silence"
            textWhenNonSelected="Custom" textWhenNoItems=""/>
  <LABEL name="presetsLabel" id="555dd5c766efb7a1" memberName="presetsLabel"
         virtualName="" explicitFocusOrder="0" pos="21 11.663% 60 24"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Presets"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="stickynessSlider" id="64d7b64d40a66223" memberName="stickynessSlider"
          virtualName="" explicitFocusOrder="0" pos="2.884% 45.782% 84.89% 16"
          min="0" max="1" int="0.010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="widthLabel" id="fb630a6f3e08259a" memberName="widthLabel"
         virtualName="" explicitFocusOrder="0" pos="1.845% 52.481% 80 24"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Width Filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="widthSlider" id="51e7ac04e76a9203" memberName="widthSlider"
          virtualName="" explicitFocusOrder="0" pos="2.884% 55.459% 84.89% 16"
          min="0" max="1" int="0.010000000000000000208" style="TwoValueHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="header2" id="4feb41a7e4880c44" memberName="header2" virtualName=""
         explicitFocusOrder="0" pos="16 31.762% 150 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Cluster Tuning"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="header1" id="e7329f5e02bd959" memberName="header1" virtualName=""
         explicitFocusOrder="0" pos="16 6.948% 150 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Feature Selection"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="zcrFeatureToggle" id="e8b2bb7bef7e0e1f" memberName="zcrFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="96 22.705% 50 24"
                tooltip="Zero Cross Rate" txtcol="ffffffff" buttonText="ZCR"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="invertRegionsToggle" id="b0589c37aecfe236" memberName="invertRegionsToggle"
                virtualName="" explicitFocusOrder="0" pos="2.884% 64.516% 120 24"
                tooltip="Invert Regions" txtcol="ffffffff" buttonText="Invert Regions"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="exportSeparateButton" id="a631088d4d356323" memberName="exportSeparateButton"
              virtualName="" explicitFocusOrder="0" pos="24 91.315% 104 24"
              bgColOff="ffff7f50" buttonText="Export Audio" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="regionDescriptionLabel" id="a04caca43e46440c" memberName="regionDescriptionLabel"
         virtualName="" explicitFocusOrder="0" pos="138R 63.4% 72 24"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="# Regions:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a0c4f9bc684a7ae" memberName="regionCountLabel"
         virtualName="" explicitFocusOrder="0" pos="80 63.4% 30 25" posRelativeX="a04caca43e46440c"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="saveSingleFileToggleButton" id="f85d7a508934cb85" memberName="saveSingleFileToggleButton"
                virtualName="" explicitFocusOrder="0" pos="0 95.285% 112 24"
                posRelativeX="a631088d4d356323" txtcol="ffffffff" buttonText="As One File"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="widthMinLabel" id="a0b81fc5519f0525" memberName="widthMinLabel"
         virtualName="" explicitFocusOrder="0" pos="0 17 56 24" posRelativeX="51e7ac04e76a9203"
         posRelativeY="51e7ac04e76a9203" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="widthMinLabel" id="1321e6b8d7b57a1d" memberName="widthMaxLabel"
         virtualName="" explicitFocusOrder="0" pos="96.467% 17 48 24"
         posRelativeX="51e7ac04e76a9203" posRelativeY="51e7ac04e76a9203"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="numRegionsComboBox" id="47e3c11d037570f1" memberName="numRegionsComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 78.412% 120 24"
            posRelativeX="74213fc8a34693ad" editable="0" layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9"
            textWhenNonSelected="# of Regions" textWhenNoItems="(no choices)"/>
  <LABEL name="header3" id="74213fc8a34693ad" memberName="header3" virtualName=""
         explicitFocusOrder="0" pos="16 72.457% 120 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Smart Search" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="searchPercentComboBox" id="da9bbdad378a720a" memberName="searchPercentComboBox"
            virtualName="" explicitFocusOrder="0" pos="144 78.412% 104 24"
            posRelativeX="74213fc8a34693ad" editable="0" layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;15&#10;20&#10;25&#10;30&#10;35&#10;40&#10;45&#10;50"
            textWhenNonSelected="% of File" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="searchButton" id="f6b9cb23f7da3ea9" memberName="searchButton"
              virtualName="" explicitFocusOrder="0" pos="24 84.367% 96 24"
              buttonText="Search" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="widthFilterSearchToggle" id="46345d311cd9365e" memberName="widthFilterSearchToggle"
                virtualName="" explicitFocusOrder="0" pos="136 72.457% 120 24"
                posRelativeX="74213fc8a34693ad" tooltip="Invert Regions" txtcol="ffffffff"
                buttonText="Use Width Filter" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TEXTBUTTON name="exportTxtButton" id="ca703147fabed5" memberName="exportTxtButton"
              virtualName="" explicitFocusOrder="0" pos="152 91.315% 104 24"
              posRelativeX="a631088d4d356323" bgColOff="ffff7f50" buttonText="Export CSV"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
