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

#include "AudioSourceSelector.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudioSourceSelector::AudioSourceSelector ()
{
    setName ("audioSourceSelector");
    addAndMakeVisible (playButton = new TextButton ("playButton"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    addAndMakeVisible (stopButton = new TextButton ("stopButton"));
    stopButton->setButtonText (TRANS("Stop"));
    stopButton->addListener (this);

    addAndMakeVisible (playSelectionButton = new TextButton ("playSelectionButton"));
    playSelectionButton->setButtonText (TRANS("Play Selection"));
    playSelectionButton->addListener (this);
    playSelectionButton->setColour (TextButton::buttonColourId, Colour (0xfffffbb6));

    addAndMakeVisible (loadFileButton = new TextButton ("loadFileButton"));
    loadFileButton->setButtonText (TRANS("Load File"));
    loadFileButton->addListener (this);
    loadFileButton->setColour (TextButton::buttonColourId, Colour (0xfffbfbfd));

    addAndMakeVisible (clearSelectionButton = new TextButton ("clearSelectionButton"));
    clearSelectionButton->setButtonText (TRANS("Clear Selection"));
    clearSelectionButton->addListener (this);
    clearSelectionButton->setColour (TextButton::buttonColourId, Colour (0xfffffbb6));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 200);


    //[Constructor] You can add your own custom stuff here..
    thumbFormatManager = new AudioFormatManager();
    thumbFormatManager->registerBasicFormats();

    controllerFormatManager = new AudioFormatManager();
    controllerFormatManager->registerBasicFormats();

    thumbCache = new AudioThumbnailCache(1);

    thumbComponent = new AudioThumbnail (500, *thumbFormatManager, *thumbCache);

    isDraggable = true; // default to true


    //[/Constructor]
}

AudioSourceSelector::~AudioSourceSelector()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    playButton = nullptr;
    stopButton = nullptr;
    playSelectionButton = nullptr;
    loadFileButton = nullptr;
    clearSelectionButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    thumbComponent = nullptr;

    delete thumbFormatManager;
    thumbFormatManager = nullptr;

    delete controllerFormatManager;
    controllerFormatManager = nullptr;
    //[/Destructor]
}

//==============================================================================
void AudioSourceSelector::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffc76060));

    //[UserPaint] Add your own custom painting code here..

    drawWaveform(g);
    
    if(hasRegionSelected){
        drawRegion(g);
    }

    //[/UserPaint]
}

void AudioSourceSelector::resized()
{
    playButton->setBounds (129, 8, 75, 24);
    stopButton->setBounds (211, 8, 75, 24);
    playSelectionButton->setBounds (412 - 100, 8, 100, 24);
    loadFileButton->setBounds (proportionOfWidth (0.0087f), 8, 100, 24);
    clearSelectionButton->setBounds (422, 8, 100, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AudioSourceSelector::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        sendActionMessage("playButton pressed in selector");
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == playSelectionButton)
    {
        //[UserButtonCode_playSelectionButton] -- add your button handler code here..
        //[/UserButtonCode_playSelectionButton]
    }
    else if (buttonThatWasClicked == loadFileButton)
    {
        //[UserButtonCode_loadFileButton] -- add your button handler code here..
        FileChooser myChooser ("Please select the file you want to load...");
        if (myChooser.browseForFileToOpen())
        {
            selectedFile = myChooser.getResult();
            FileInputSource fileInput(selectedFile);
            thumbComponent->setSource(&fileInput);

            String name = getName();
            if(name == "audioSrcSelector"){
                sendActionMessage("setSourceFile");
            }
            else if(name == "targetFileSelector"){
                sendActionMessage("setTargetFile");
            }

            fileLoaded = true;
            repaint();
        }
        //[/UserButtonCode_loadFileButton]
    }
    else if (buttonThatWasClicked == clearSelectionButton)
    {
        //[UserButtonCode_clearSelectionButton] -- add your button handler code here..
        regionOverlay.clear();
        repaint();

        sendActionMessage("srcRegionCleared");

        //[/UserButtonCode_clearSelectionButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AudioSourceSelector::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    //[/UserCode_visibilityChanged]
}

void AudioSourceSelector::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    std::cout << "clicked: " << e.getMouseDownX();
    //[/UserCode_mouseDown]
}

void AudioSourceSelector::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    if(fileLoaded and isDraggable){
        int startX = e.getMouseDownX();
        int endX = startX + e.getDistanceFromDragStartX();

        if(endX < startX){  // enable dragging both ways
            int tmp = endX;
            endX = startX;
            startX = tmp;
        }
        
//        std::cout << startX << " " << endX << std::endl;;

        setSelectedRegion(startX, endX);
    }
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AudioSourceSelector::setSelectedRegion(int startX, int endX){

    regionOverlay  = AudioRegion(startX, endX, getWidth());
    hasRegionSelected = true;

    repaint();

    sendActionMessage("srcRegionSelected");
}

void AudioSourceSelector::getAudioSelection(){

}

void AudioSourceSelector::setDraggable(bool makeDraggable){
    isDraggable = makeDraggable;

    playSelectionButton->setVisible(false);
    clearSelectionButton->setVisible(false);

}

bool AudioSourceSelector::hasFileLoaded(){
    return fileLoaded;
}

File AudioSourceSelector::getLoadedFile(){
    return selectedFile;
}

void AudioSourceSelector::drawRegion(juce::Graphics &g){
    g.setColour(Colours::black);
    
    g.setOpacity(0.5);
    int x = regionOverlay.getStart(getWidth());
    int y = getY();
    int w = regionOverlay.getEnd(getWidth()) - regionOverlay.getStart(getWidth());
    int h = getHeight();
    
    g.fillRect(x,y,w,h);
}

void AudioSourceSelector::drawWaveform(juce::Graphics &g){
    g.setColour(Colours::chocolate);

    Rectangle<int> bounds = Rectangle<int>();
    bounds.setX(getX());
    bounds.setY(0); // relative y position
    bounds.setWidth(getWidth());
    bounds.setHeight(getHeight());
    
    thumbComponent->drawChannel(g, bounds, 0, thumbComponent->getTotalLength(), 0, 1);
    
    if(!thumbComponent->isFullyLoaded()){
        repaint();
    }
}

AudioRegion AudioSourceSelector::getSelectedRegion(){
    return regionOverlay;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioSourceSelector" componentName="audioSourceSelector"
                 parentClasses="public Component, public ActionBroadcaster" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="800" initialHeight="200">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="visibilityChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffc76060"/>
  <TEXTBUTTON name="playButton" id="2e944592a12d5b22" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="129 8 75 24" buttonText="Play"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stopButton" id="b3bb395d3bc0e4a9" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="211 8 75 24" buttonText="Stop"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="playSelectionButton" id="8e3de633a39789c" memberName="playSelectionButton"
              virtualName="" explicitFocusOrder="0" pos="412r 8 100 24" bgColOff="fffffbb6"
              buttonText="Play Selection" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="loadFileButton" id="3d0772bc202e3d3" memberName="loadFileButton"
              virtualName="" explicitFocusOrder="0" pos="0.873% 8 100 24" bgColOff="fffbfbfd"
              buttonText="Load File" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="clearSelectionButton" id="93b16b318257d1ed" memberName="clearSelectionButton"
              virtualName="" explicitFocusOrder="0" pos="422 8 100 24" bgColOff="fffffbb6"
              buttonText="Clear Selection" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
