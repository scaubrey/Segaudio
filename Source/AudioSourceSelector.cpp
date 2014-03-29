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

    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 200);


    //[Constructor] You can add your own custom stuff here..
    thumbFormatManager = new AudioFormatManager();
    thumbFormatManager->registerBasicFormats();

    thumbCache = new AudioThumbnailCache(1);

    thumbComponent = new AudioThumbnail (1000, *thumbFormatManager, *thumbCache);

    fileInputSource = nullptr;

    isDraggable = true; // default to true
    
    audioPLaying = false;

    regionOverlay.clear();
    
    audioPostionFrac = 0.0f;
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

    if(hasRegionSelected){
        drawRegion(g);
    }

    drawCandidateRegions(g);
    
    if(fileLoaded){
        drawAudioPositionBar(g);
    }
    
    if(audioPLaying){
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

void AudioSourceSelector::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    int mouseX = e.getMouseDownX();
    
    audioPostionFrac = float(mouseX) / getWidth();
    
    if(audioPLaying){
        sendActionMessage("audioPositionUpdateWhilePlaying"); // update audio and keep playing 
    }
    
    repaint();
    
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

void AudioSourceSelector::clearAll(){
    clearRegion();
    // clear file?
}

void AudioSourceSelector::clearRegion(){
    regionOverlay.clear();
    repaint();

    sendActionMessage("srcRegionCleared");
}

void AudioSourceSelector::setSelectedRegion(int startX, int endX){

    regionOverlay  = AudioRegion(startX, endX, getWidth());
    hasRegionSelected = true;

    repaint();

    sendActionMessage("srcRegionSelected");
}


void AudioSourceSelector::setDraggable(bool makeDraggable){
    isDraggable = makeDraggable;

}

bool AudioSourceSelector::hasFileLoaded(){
    return fileLoaded;
}

SegaudioFile* AudioSourceSelector::getLoadedFile(){
    return &selectedFile;
}

void AudioSourceSelector::setFile(File &newFile){

    fileInputSource = new FileInputSource(newFile);
    thumbComponent->setSource(fileInputSource);
    
    ScopedPointer<AudioFormatReader> tmpReader = thumbFormatManager->createReaderFor(newFile);
    numChannels = tmpReader->numChannels;
    numSamples = tmpReader->lengthInSamples;
    sampleRate = tmpReader->sampleRate;
    
    positionBarTimer = new PositionBarTimer(audioPostionFrac, numSamples, sampleRate);
    
    selectedFile.setFile(newFile);
    
    fileLoaded = true;
    audioPostionFrac = 0;
    repaint();
}

void AudioSourceSelector::drawRegion(juce::Graphics &g){
    g.setColour(Colours::yellow);

    g.setOpacity(0.5);
    int x = regionOverlay.getStart(getWidth());
    int y = getY();
    int w = regionOverlay.getEnd(getWidth()) - regionOverlay.getStart(getWidth());
    int h = getHeight();

    g.fillRect(x,y,w,h);
}

void AudioSourceSelector::drawWaveform(juce::Graphics &g){
    g.setColour(Colours::blue);

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

void AudioSourceSelector::setCandidateRegions(Array<AudioRegion> newCandidateRegions){

    candidateRegions = newCandidateRegions;
    repaint();
}

void AudioSourceSelector::drawCandidateRegions(juce::Graphics &g){

    g.setColour(Colours::black);
    g.setOpacity(0.5);

    for(int i=0; i<candidateRegions.size(); i++){


        int startX = candidateRegions[i].getStart(getWidth());
        int width = candidateRegions[i].getEnd(getWidth()) - startX;

        g.fillRect(startX, 0, width, getHeight());

    }
}

void AudioSourceSelector::drawAudioPositionBar(Graphics &g){
    g.setColour(Colours::red);
    g.setOpacity(0.8);
    
    int positionBarInPixels = round(audioPostionFrac * getWidth());
    
    g.drawLine(positionBarInPixels, 0, positionBarInPixels, getHeight());
    
}

float AudioSourceSelector::getPositionBarTime(){
    float currentPositionBarTime = audioPostionFrac * float(numSamples) / float(sampleRate);
    return currentPositionBarTime;
}

void AudioSourceSelector::startPositionBar(){
    if(fileLoaded){
        positionBarTimer->startTimer(50);
    }
    audioPLaying = true;
};

void AudioSourceSelector::stopPositionBar(){
    if(positionBarTimer->isTimerRunning()){
        positionBarTimer->stopTimer();
    }
    
    audioPLaying = false;
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
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
