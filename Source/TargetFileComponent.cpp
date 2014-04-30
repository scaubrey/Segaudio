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

#include "TargetFileComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TargetFileComponent::TargetFileComponent (AudioDeviceManager& deviceManager)
    : deviceManager(deviceManager)
{
    addAndMakeVisible (viewport = new Viewport());
    viewport->setName ("viewport");

    addAndMakeVisible (container = new TargetContainer());
    container->setName ("container");

    addAndMakeVisible (playButton = new TextButton ("playButton"));
    playButton->setButtonText ("Play");
    playButton->addListener (this);

    addAndMakeVisible (stopButton = new TextButton ("stopButton"));
    stopButton->setButtonText ("Stop");
    stopButton->addListener (this);

    addAndMakeVisible (loadFileButton = new TextButton ("loadFileButton"));
    loadFileButton->setButtonText ("Load File");
    loadFileButton->addListener (this);
    loadFileButton->setColour (TextButton::buttonColourId, Colour (0xfffbfbfd));

    addAndMakeVisible (zoomLabel = new Label ("zoomLabel",
                                              "ZoomX"));
    zoomLabel->setFont (Font (15.00f, Font::plain));
    zoomLabel->setJustificationType (Justification::centredLeft);
    zoomLabel->setEditable (false, false, false);
    zoomLabel->setColour (TextEditor::textColourId, Colours::black);
    zoomLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (zoomSlider = new Slider ("zoomSlider"));
    zoomSlider->setRange (1, 5, 0.1);
    zoomSlider->setSliderStyle (Slider::LinearHorizontal);
    zoomSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 35, 20);
    zoomSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    viewport->setViewedComponent(container, false);

    isPlayable = false;
    setPlayable(isPlayable);

    deviceManager.addAudioCallback(&audioSourcePlayer);
    audioSourcePlayer.setSource(&audioTransport);

    container->addActionListener(this);

    currentFile = new SegaudioFile();


    //[/Constructor]
}

TargetFileComponent::~TargetFileComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    viewport = nullptr;
    container = nullptr;
    playButton = nullptr;
    stopButton = nullptr;
    loadFileButton = nullptr;
    zoomLabel = nullptr;
    zoomSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TargetFileComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffa71616));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TargetFileComponent::resized()
{
    viewport->setBounds (5, 5, getWidth() - 10, getHeight() - 10);
    container->setBounds (5, 5, 849, getHeight() - 10);
    playButton->setBounds (153, 16, 75, 24);
    stopButton->setBounds (235, 16, 75, 24);
    loadFileButton->setBounds (proportionOfWidth (0.0254f), 16, 100, 24);
    zoomLabel->setBounds (getWidth() - 251, 16, 48, 24);
    zoomSlider->setBounds (getWidth() - 203, 16, 160, 24);
    //[UserResized] Add your own custom resize handling here..

    container->setSize(getWidth(), getHeight());

    //[/UserResized]
}

void TargetFileComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        playAudio();
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        stopAudio();
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == loadFileButton)
    {
        //[UserButtonCode_loadFileButton] -- add your button handler code here..
        FileChooser myChooser ("Please select the file you want to load...");
        if (myChooser.browseForFileToOpen())
        {
            audioTransport.setSource(nullptr); // this fixes memory issue with loading new file

            File selectedFile = myChooser.getResult();
            currentFile->setFile(selectedFile);

            container->setFile(selectedFile);

            audioTransport.setSource(currentFile->getSource());

            isPlayable = true;
            setPlayable(true);
            sendActionMessage("setTargetFile");

        }
        //[/UserButtonCode_loadFileButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TargetFileComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == zoomSlider)
    {
        //[UserSliderCode_zoomSlider] -- add your slider handling code here..
        container->setSize(zoomSlider->getValue()*getWidth(), container->getHeight());
        //[/UserSliderCode_zoomSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TargetFileComponent::setTuningParameters(ClusterParameters* clusterTuningParams, Array<float>* newDistances, float* maxDistance){
    container->setTuningParameters(clusterTuningParams, newDistances, maxDistance);
}

SegaudioFile* TargetFileComponent::getLoadedFile(){
    return currentFile;
}

void TargetFileComponent::setPlayable(bool isPlayable){
    playButton->setEnabled(isPlayable);
    stopButton->setEnabled(isPlayable);
    zoomSlider->setEnabled(isPlayable);
}

void TargetFileComponent::actionListenerCallback(const juce::String &message){

    if(message == "audioPositionUpdateWhilePlaying"){
        playAudio();
    }
    else{
        sendActionMessage(message);
    }
//    DBG(message);
}

void TargetFileComponent::playAudio(){
    container->startAudio();
    float currentAudioTime = container->getPositionBarTime();
    audioTransport.setPosition(currentAudioTime);
    audioTransport.start();
}

void TargetFileComponent::stopAudio(){
    container->stopAudio();
    audioTransport.stop();
}

void TargetFileComponent::clearSimilarity(){
    container->clearSimilarity();
}

void TargetFileComponent::setRegions(Array<AudioRegion> *regions_) {
    container->setRegions(regions_);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TargetFileComponent" componentName=""
                 parentClasses="public Component, public ActionBroadcaster, public ActionListener"
                 constructorParams="AudioDeviceManager&amp; deviceManager" variableInitialisers="deviceManager(deviceManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffa71616"/>
  <GENERICCOMPONENT name="viewport" id="fbe83dc2467ab07a" memberName="viewport" virtualName=""
                    explicitFocusOrder="0" pos="5 5 10M 10M" class="Viewport" params=""/>
  <GENERICCOMPONENT name="container" id="37992296fdbdbb3c" memberName="container"
                    virtualName="" explicitFocusOrder="0" pos="5 5 849 10M" class="TargetContainer"
                    params=""/>
  <TEXTBUTTON name="playButton" id="2e944592a12d5b22" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="153 16 75 24" buttonText="Play"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stopButton" id="b3bb395d3bc0e4a9" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="235 16 75 24" buttonText="Stop"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="loadFileButton" id="3d0772bc202e3d3" memberName="loadFileButton"
              virtualName="" explicitFocusOrder="0" pos="2.537% 16 100 24"
              bgColOff="fffbfbfd" buttonText="Load File" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="zoomLabel" id="292ada877f7dc70f" memberName="zoomLabel"
         virtualName="" explicitFocusOrder="0" pos="251R 16 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="ZoomX" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="zoomSlider" id="c9fdacb0eb021f55" memberName="zoomSlider"
          virtualName="" explicitFocusOrder="0" pos="203R 16 160 24" min="1"
          max="5" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="35"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
