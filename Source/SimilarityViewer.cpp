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
//[/Headers]

#include "SimilarityViewer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SimilarityViewer::SimilarityViewer ()
{
    addAndMakeVisible (simControlsContainer = new Component());
    simControlsContainer->setName ("simControlsContainer");

    addAndMakeVisible (thresholdSlider = new Slider ("new slider"));
    thresholdSlider->setRange (0, 1, 0);
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
    calcSimButton->setButtonText (TRANS("Compare"));
    calcSimButton->addListener (this);
    calcSimButton->setColour (TextButton::buttonColourId, Colour (0xff97fc74));

    addAndMakeVisible (rmsFeatureToggle = new ToggleButton ("rmsFeatureToggle"));
    rmsFeatureToggle->setButtonText (TRANS("RMS"));
    rmsFeatureToggle->addListener (this);
    rmsFeatureToggle->setToggleState (true, dontSendNotification);

    addAndMakeVisible (sfFeatureToggle = new ToggleButton ("sfFeatureToggle"));
    sfFeatureToggle->setButtonText (TRANS("SF"));
    sfFeatureToggle->addListener (this);

    addAndMakeVisible (graphContainer = new Component());
    graphContainer->setName ("graphContainer");

    addAndMakeVisible (mfccFeatureToggle = new ToggleButton ("mfccFeatureToggle"));
    mfccFeatureToggle->setButtonText (TRANS("MFCC"));
    mfccFeatureToggle->addListener (this);

    addAndMakeVisible (stickynessSlider = new Slider ("stickynessSlider"));
    stickynessSlider->setRange (0, 1, 0);
    stickynessSlider->setSliderStyle (Slider::LinearHorizontal);
    stickynessSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    stickynessSlider->addListener (this);

    addAndMakeVisible (stickynessLabel = new Label ("stickynessLabel",
                                                    TRANS("Stickyness")));
    stickynessLabel->setFont (Font (15.00f, Font::plain));
    stickynessLabel->setJustificationType (Justification::centredLeft);
    stickynessLabel->setEditable (false, false, false);
    stickynessLabel->setColour (TextEditor::textColourId, Colours::black);
    stickynessLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (smoothnessSlider = new Slider ("smoothnessSlider"));
    smoothnessSlider->setRange (0, 1, 0);
    smoothnessSlider->setSliderStyle (Slider::LinearHorizontal);
    smoothnessSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    smoothnessSlider->addListener (this);

    addAndMakeVisible (smoothnessLabel = new Label ("smoothnessLabel",
                                                    TRANS("Smoothness")));
    smoothnessLabel->setFont (Font (15.00f, Font::plain));
    smoothnessLabel->setJustificationType (Justification::centredLeft);
    smoothnessLabel->setEditable (false, false, false);
    smoothnessLabel->setColour (TextEditor::textColourId, Colours::black);
    smoothnessLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (presetComboBox = new ComboBox ("presetComboBox"));
    presetComboBox->setEditableText (false);
    presetComboBox->setJustificationType (Justification::centredLeft);
    presetComboBox->setTextWhenNothingSelected (TRANS("None"));
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


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 300);


    //[Constructor] You can add your own custom stuff here..

    setReadyToCompare(false);

    addActionListener(&analysisController);

    stickyness = 0;
    threshold = 0;
    //[/Constructor]
}

SimilarityViewer::~SimilarityViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    simControlsContainer = nullptr;
    thresholdSlider = nullptr;
    thresholdLabel = nullptr;
    calcSimButton = nullptr;
    rmsFeatureToggle = nullptr;
    sfFeatureToggle = nullptr;
    graphContainer = nullptr;
    mfccFeatureToggle = nullptr;
    stickynessSlider = nullptr;
    stickynessLabel = nullptr;
    smoothnessSlider = nullptr;
    smoothnessLabel = nullptr;
    presetComboBox = nullptr;
    presetsLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
//    thumbComponent = nullptr;
    //[/Destructor]
}

//==============================================================================
void SimilarityViewer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    drawThreshold(g);
    drawSimilarityFunction(g);

//    drawRegions(g);

    //[/UserPaint]
}

void SimilarityViewer::resized()
{
    simControlsContainer->setBounds (0, 0, proportionOfWidth (1.0000f), 100);
    thresholdSlider->setBounds (200, 40, 150, 24);
    thresholdLabel->setBounds (240, 16, 80, 24);
    calcSimButton->setBounds (proportionOfWidth (0.0081f), 16, 150, 24);
    rmsFeatureToggle->setBounds (getWidth() - 132, proportionOfHeight (0.0100f), 50, 24);
    sfFeatureToggle->setBounds (getWidth() - 68, proportionOfHeight (0.0100f), 50, 24);
    graphContainer->setBounds (0, 100, proportionOfWidth (1.0000f), 300);
    mfccFeatureToggle->setBounds (getWidth() - 188, proportionOfHeight (0.0100f), 50, 24);
    stickynessSlider->setBounds (360, 40, 150, 24);
    stickynessLabel->setBounds (400, 16, 80, 24);
    smoothnessSlider->setBounds (512, 40, 150, 24);
    smoothnessLabel->setBounds (552, 16, 80, 24);
    presetComboBox->setBounds (proportionOfWidth (0.8475f), proportionOfHeight (0.0596f), 100, 24);
    presetsLabel->setBounds (proportionOfWidth (0.7730f), proportionOfHeight (0.0596f), 60, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SimilarityViewer::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == thresholdSlider)
    {
        //[UserSliderCode_thresholdSlider] -- add your slider handling code here..
        threshold = thresholdSlider->getValue();

        updateRegions();
        repaint();
        //[/UserSliderCode_thresholdSlider]
    }
    else if (sliderThatWasMoved == stickynessSlider)
    {
        //[UserSliderCode_stickynessSlider] -- add your slider handling code here..
        stickyness = stickynessSlider->getValue();

        updateRegions();
        //[/UserSliderCode_stickynessSlider]
    }
    else if (sliderThatWasMoved == smoothnessSlider)
    {
        //[UserSliderCode_smoothnessSlider] -- add your slider handling code here..
        smoothness = smoothnessSlider->getValue();

        updateSimilarityFunction();
        //[/UserSliderCode_smoothnessSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SimilarityViewer::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == calcSimButton)
    {
        //[UserButtonCode_calcSimButton] -- add your button handler code here..
        sendActionMessage("calculateDistances");
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SimilarityViewer::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetComboBox)
    {
        //[UserComboBoxCode_presetComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_presetComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimilarityViewer::setDistanceArray(Array<float> newArray, float newMaxDistance){
    distanceArray = newArray;
    filteredDistanceArray = distanceArray;
    maxDistance = newMaxDistance;
    updateRegions();
    repaint();
};

void SimilarityViewer::drawThreshold(Graphics &g){

    g.setColour(Colours::blueviolet);
    g.drawHorizontalLine(graphContainer->getY() + graphContainer->getHeight() - threshold * graphContainer->getHeight(), getX(), getWidth());

}

void SimilarityViewer::drawSimilarityFunction(Graphics &g){

    g.setColour(Colours::green);

    int graphLengthInPixels = getWidth();

    int lastXPixel = 0;
    int currentXPixel;

    float yScale = graphContainer->getHeight() / maxDistance;

    float lastRms = graphContainer->getY() + graphContainer->getHeight() - floor(filteredDistanceArray[0] * graphLengthInPixels / filteredDistanceArray.size());
    if(std::isnan(lastRms)){
        lastRms = 0;
    }

    float currentRms;

    for(int i=1; i<filteredDistanceArray.size(); i++){

        currentXPixel = floor((i) * graphLengthInPixels / distanceArray.size());

        currentRms = graphContainer->getY() + graphContainer->getHeight() - filteredDistanceArray[i] * yScale;

        g.drawLine(lastXPixel, lastRms, currentXPixel, currentRms, 1.0f);

        lastXPixel = currentXPixel;
        lastRms = currentRms;

    }
}


void SimilarityViewer::setReadyToCompare(bool ready){
    calcSimButton->setVisible(ready);
    thresholdSlider->setVisible(ready);
    stickynessSlider->setVisible(ready);
    smoothnessSlider->setVisible(ready);
    mfccFeatureToggle->setVisible(ready);
    sfFeatureToggle->setVisible(ready);
    rmsFeatureToggle->setVisible(ready);
    thresholdLabel->setVisible(ready);
    stickynessLabel->setVisible(ready);
    smoothnessLabel->setVisible(ready);
    presetComboBox->setVisible(ready);
    presetsLabel->setVisible(ready);
}

void SimilarityViewer::drawRegions(Graphics &g){

    g.setOpacity(0.9);
    g.setColour(Colours::black);

    for(int i=0; i<regionCandidates.size(); i++){


        int startX = regionCandidates[i].getStart(getWidth());
        int width = regionCandidates[i].getEnd(getWidth()) - startX;

        g.fillRect(startX, graphContainer->getY(), width, graphContainer->getHeight());

    }
}

void SimilarityViewer::updateRegions(){
    regionCandidates = analysisController.getRegionsWithinThreshold(distanceArray, threshold * maxDistance, stickyness * 10);

    sendActionMessage("candidateRegionsUpdated");
}

Array<AudioRegion> SimilarityViewer::getCandidateRegions(){
    return regionCandidates;
}

void SimilarityViewer::updateSimilarityFunction(){
    filteredDistanceArray = analysisController.medianFilter(distanceArray, smoothness * 100);
}

void SimilarityViewer::updateComponent(){
    updateSimilarityFunction();
    updateRegions();
    repaint();
}

void SimilarityViewer::clear(){

    distanceArray.clear();
    filteredDistanceArray.clear();

    regionCandidates.clear();
    sendActionMessage("candidateRegionsUpdated");
    repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimilarityViewer" componentName=""
                 parentClasses="public Component, public ActionBroadcaster" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="800" initialHeight="300">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="simControlsContainer" id="d7eb2493d0021c3d" memberName="simControlsContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 100" class="Component"
                    params=""/>
  <SLIDER name="new slider" id="2ddea841d6d652ab" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="200 40 150 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4f564f498f058971" memberName="thresholdLabel"
         virtualName="" explicitFocusOrder="0" pos="240 16 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="calcSimButton" id="9ce3f6b1681a8658" memberName="calcSimButton"
              virtualName="" explicitFocusOrder="0" pos="0.815% 16 150 24"
              bgColOff="ff97fc74" buttonText="Compare" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="rmsFeatureToggle" id="92a1f05376de0623" memberName="rmsFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="132R 0.993% 50 24"
                buttonText="RMS" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
  <TOGGLEBUTTON name="sfFeatureToggle" id="9eb603aec59d0a37" memberName="sfFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="68R 0.993% 50 24"
                buttonText="SF" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <GENERICCOMPONENT name="graphContainer" id="a6f81aed259b1d6e" memberName="graphContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 100 100% 300" class="Component"
                    params=""/>
  <TOGGLEBUTTON name="mfccFeatureToggle" id="f946313658ff3956" memberName="mfccFeatureToggle"
                virtualName="" explicitFocusOrder="0" pos="188R 0.993% 50 24"
                buttonText="MFCC" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="stickynessSlider" id="47ae86c160831f8" memberName="stickynessSlider"
          virtualName="" explicitFocusOrder="0" pos="360 40 150 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="stickynessLabel" id="32983a34059e5df1" memberName="stickynessLabel"
         virtualName="" explicitFocusOrder="0" pos="400 16 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Stickyness" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="smoothnessSlider" id="11a9f6de9a840203" memberName="smoothnessSlider"
          virtualName="" explicitFocusOrder="0" pos="512 40 150 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="smoothnessLabel" id="b8d50e7cbed6b69c" memberName="smoothnessLabel"
         virtualName="" explicitFocusOrder="0" pos="552 16 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Smoothness" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="presetComboBox" id="2a56f7bafaec946f" memberName="presetComboBox"
            virtualName="" explicitFocusOrder="0" pos="84.75% 5.955% 100 24"
            editable="0" layout="33" items="Speech&#10;Music&#10;Noise&#10;Silence"
            textWhenNonSelected="None" textWhenNoItems=""/>
  <LABEL name="presetsLabel" id="555dd5c766efb7a1" memberName="presetsLabel"
         virtualName="" explicitFocusOrder="0" pos="77.299% 5.955% 60 24"
         edTextCol="ff000000" edBkgCol="0" labelText="Presets" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
