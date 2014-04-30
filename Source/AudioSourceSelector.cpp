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
AudioSourceSelector::AudioSourceSelector (int mode_)
{
    setName ("audioSourceSelector");

    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 200);


    //[Constructor] You can add your own custom stuff here..
    thumbFormatManager = new AudioFormatManager();
    thumbFormatManager->registerBasicFormats();

    thumbCache = new AudioThumbnailCache(1);

    thumbComponent = new AudioThumbnail (1000, *thumbFormatManager, *thumbCache);

    fileInputSource = nullptr;

    mode = mode_ ;

    isAudioPlaying = false;
    audioPositionFrac = 0.0f;

    idxOfRegionHovered = 0;
    isRegionBeingEdited = false;
    touchPrecision = 5;

    //[/Constructor]
}

AudioSourceSelector::~AudioSourceSelector()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    thumbFormatManager->clearFormats();
    delete thumbFormatManager;
    thumbFormatManager = nullptr;

    thumbComponent->clear();
    delete thumbComponent;
    thumbComponent = nullptr;

    thumbCache->clear();
    delete thumbCache;
    thumbCache = nullptr;

    //[/Destructor]
}

//==============================================================================
void AudioSourceSelector::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    drawWaveform(g);
    drawCandidateRegions(g);

    if(fileLoaded){
        drawAudioPositionBar(g);
    }

    if(isAudioPlaying){
        repaint();
    }

    //[/UserPaint]
}

void AudioSourceSelector::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AudioSourceSelector::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    //[/UserCode_visibilityChanged]
}

void AudioSourceSelector::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    int numRegions = regions->size();
    int mouseX = e.getPosition().getX();

    // find region we might be hovering over, maybe better way to search?
    for(int i=0; i<numRegions; i++){
        float regionEnd = (*regions)[i].getEnd(getWidth());
        float regionStart = (*regions)[i].getStart(getWidth());

        if(fabs(mouseX - regionStart) < touchPrecision){  // near region start

            MouseCursor cursor;
            cursor = MouseCursor(MouseCursor::DraggingHandCursor);
            setMouseCursor(cursor);

            isHoveringOverRegionStart = true;
            idxOfRegionHovered = i;
            break;
        }
        else if(fabs(mouseX - regionEnd) < touchPrecision){ // near region end

            MouseCursor cursor;
            cursor = MouseCursor(MouseCursor::DraggingHandCursor);
            setMouseCursor(cursor);

            isHoveringOverRegionEnd = true;
            idxOfRegionHovered = i;
            break;
        }
        else{  // not near region start or end
            MouseCursor cursor;
            cursor = MouseCursor(MouseCursor::NormalCursor);
            setMouseCursor(cursor);

            isHoveringOverRegionEnd = false;
            isHoveringOverRegionStart = false;
        }
    }

    //[/UserCode_mouseMove]
}

void AudioSourceSelector::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

    if(isHoveringOverRegionEnd or isHoveringOverRegionStart){
        isRegionBeingEdited = true;
    }
    else{
        isAddingRegion = true;
        numRegions = regions->size();
    }

    if(!isRegionBeingEdited){ // set audio position if not editing region
        // set audio position

        int mouseX = e.getMouseDownX();
        audioPositionFrac = float(mouseX) / getWidth();

        if(isAudioPlaying){
            sendActionMessage("audioPositionUpdateWhilePlaying"); // update audio and keep playing
        }
    }

    if(e.mods.isRightButtonDown()){  // delete regions with right click
        int numRegions = regions->size();
        int mouseX = e.getPosition().getX();

        for(int i=0; i<numRegions; i++){
            if((*regions)[i].isInRegion(float(mouseX) / getWidth())){
                regions->remove(i);
                sendActionMessage("numRegionsChanged");
                break;
            }
        }
    }


    repaint();

    //[/UserCode_mouseDown]
}

void AudioSourceSelector::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    int mouseDownX = e.getMouseDownX();
    int dragX = e.getPosition().getX();


    if(fileLoaded and mode == Reference){  // draw reference region if in reference mode
        int endX = mouseDownX + e.getDistanceFromDragStartX();

        if(endX < mouseDownX){  // enable dragging both ways
            int tmp = endX;
            endX = mouseDownX;
            mouseDownX = tmp;
        }
        regions->set(0, AudioRegion(mouseDownX, endX, getWidth()));

        sendActionMessage("srcRegionSelected");
    }
    else if(fileLoaded and mode == Target and isRegionBeingEdited){ // edit region if in target mode
        float regionStart;
        float regionEnd;

        if(isHoveringOverRegionStart){
            regionStart = float(dragX)/ getWidth();
            regionEnd = (*regions)[idxOfRegionHovered].getEnd();
        }
        else if(isHoveringOverRegionEnd){
            regionStart = (*regions)[idxOfRegionHovered].getStart();
            regionEnd = float(dragX)/ getWidth();
        }

        regions->set(idxOfRegionHovered, AudioRegion(regionStart, regionEnd));
    }
    else if(fileLoaded and mode==Target and isAddingRegion){
        int endX = mouseDownX + e.getDistanceFromDragStartX();

        if(endX < mouseDownX){  // enable dragging both ways
            int tmp = endX;
            endX = mouseDownX;
            mouseDownX = tmp;
        }
        regions->set(numRegions, AudioRegion(mouseDownX, endX, getWidth()));
        sendActionMessage("numRegionsChanged");
        DBG("test: numRegionsChanged");
    }

    repaint();

    //[/UserCode_mouseDrag]
}

void AudioSourceSelector::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...

    isHoveringOverRegionStart = false;
    isHoveringOverRegionEnd = false;
    isRegionBeingEdited = false;
    idxOfRegionHovered = 0;

    isAddingRegion = false;

    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void AudioSourceSelector::setMode(int newMode) {
    mode = newMode;
}

void AudioSourceSelector::setFile(File &newFile){

    fileInputSource = new FileInputSource(newFile);
    thumbComponent->setSource(fileInputSource);

    ScopedPointer<AudioFormatReader> tmpReader = thumbFormatManager->createReaderFor(newFile);
    numChannels = tmpReader->numChannels;
    numSamples = tmpReader->lengthInSamples;
    sampleRate = tmpReader->sampleRate;

    positionBarTimer = new PositionBarTimer(audioPositionFrac, numSamples, sampleRate);

    fileLoaded = true;
    audioPositionFrac = 0;
    repaint();
}

void AudioSourceSelector::drawWaveform(juce::Graphics &g){
    g.setColour(Colours::blue);

    Rectangle<int> bounds = Rectangle<int>();
    bounds.setX(getX());
    bounds.setY(0); // relative y position
    bounds.setWidth(getWidth());
    bounds.setHeight(getHeight());

    thumbComponent->drawChannel(g, bounds, 0, thumbComponent->getTotalLength(), 0, 1);

    if(!thumbComponent->isFullyLoaded()){ // have to force this
        repaint();
    }
}


void AudioSourceSelector::setRegions(Array<AudioRegion>* regions_){
    regions = regions_;
    repaint();
}

void AudioSourceSelector::drawCandidateRegions(juce::Graphics &g){

    if(mode == Reference){
        g.setColour(Colours::yellow);
    }
    else if(mode == Target){
        g.setColour(Colours::black);
    }
    g.setOpacity(0.5);

    for(int i=0; i<regions->size(); i++){

        int startX = (*regions)[i].getStart(getWidth());
        int width = (*regions)[i].getEnd(getWidth()) - startX;

        g.fillRect(startX, 0, width, getHeight());

    }
}

void AudioSourceSelector::drawAudioPositionBar(Graphics &g){
    g.setColour(Colours::red);
    g.setOpacity(0.8);

    int positionBarInPixels = round(audioPositionFrac * getWidth());

    g.drawLine(positionBarInPixels, 0, positionBarInPixels, getHeight());

}

float AudioSourceSelector::getPositionBarTime(){
    float currentPositionBarTime = audioPositionFrac * float(numSamples) / float(sampleRate);
    return currentPositionBarTime;
}

void AudioSourceSelector::startPositionBar(){
    if(fileLoaded){
        positionBarTimer->startTimer(50);
    }
    isAudioPlaying = true;
};

void AudioSourceSelector::stopPositionBar(){
    if(positionBarTimer->isTimerRunning()){
        positionBarTimer->stopTimer();
    }
    isAudioPlaying = false;
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioSourceSelector" componentName="audioSourceSelector"
                 parentClasses="public Component, public ActionBroadcaster" constructorParams="int mode_"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="800" initialHeight="200">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="visibilityChanged()"/>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
