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
    addAndMakeVisible (graphContainer = new Component());
    graphContainer->setName ("graphContainer");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 300);


    //[Constructor] You can add your own custom stuff here..
    stickyness = 0;
    threshold = 0;
    maxDistance = 0;

    distanceArray = NULL;
    filteredDistanceArray = NULL;
    
    isWaiting = false;
    
    waitGraphic = Rectangle<int>(0, 0, getWidth()/50, getHeight());
  
    //[/Constructor]
}

SimilarityViewer::~SimilarityViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    graphContainer = nullptr;


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

    if(maxDistance != 0 and !isWaiting){
        drawSimilarityFunction(g);
        drawThreshold(g);
    }
    
    if(isWaiting){
        drawWaitGraphic(g);
    }

    //[/UserPaint]
}

void SimilarityViewer::resized()
{
    graphContainer->setBounds (0, proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.8995f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimilarityViewer::setTuningParameters(ClusterParameters* clusterTuningParams, Array<float>* newArray, float distance){

    threshold = clusterTuningParams->threshold;
    stickyness = clusterTuningParams->regionConnectionWidth;
    smoothness = clusterTuningParams->medianFilterWidth;

    distanceArray = newArray;
    filteredDistanceArray = distanceArray;
    maxDistance = distance;
    repaint();
};

void SimilarityViewer::drawThreshold(Graphics &g){

    g.setColour(Colours::blueviolet);
    g.drawHorizontalLine(graphContainer->getHeight() - threshold * graphContainer->getHeight() * 1/10, getX(), getWidth());

}

void SimilarityViewer::drawSimilarityFunction(Graphics &g){

    g.setColour(Colours::green);

    int graphLengthInPixels = getWidth();

    int lastXPixel = 0;
    int currentXPixel;

    float yScale = graphContainer->getHeight() / maxDistance;

    float lastRms = graphContainer->getY() + graphContainer->getHeight() - floor((*filteredDistanceArray)[0] * graphLengthInPixels / filteredDistanceArray->size());
    if(std::isnan(lastRms)){
        lastRms = 0;
    }

    float currentRms;

    for(int i=1; i<filteredDistanceArray->size(); i++){

        currentXPixel = floor((i) * graphLengthInPixels / distanceArray->size());

        currentRms = graphContainer->getY() + graphContainer->getHeight() - (*filteredDistanceArray)[i] * yScale;

        g.drawLine(lastXPixel, lastRms, currentXPixel, currentRms, 1.0f);

        lastXPixel = currentXPixel;
        lastRms = currentRms;

    }
}

void SimilarityViewer::clear(){

    distanceArray->clear();
    filteredDistanceArray->clear();

    repaint();
}

void SimilarityViewer::setCalculating(bool status){
    isWaiting = status;
    if(isWaiting){
        startTimer(10);
    }
    else{
        stopTimer();
    }
}

void SimilarityViewer::timerCallback(){
    int oldX = waitGraphic.getX();
    float speed = 100.0f; // pixels/sec
    
    int newX = oldX + speed * 0.05;
    if(newX > getWidth()) newX = 0;
    
    waitGraphic.setX(newX);
}

void SimilarityViewer::drawWaitGraphic(Graphics &g){
    g.fillRect(waitGraphic);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimilarityViewer" componentName=""
                 parentClasses="public Component, public ActionBroadcaster, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="300">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="graphContainer" id="a6f81aed259b1d6e" memberName="graphContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 0% 100% 89.95%"
                    class="Component" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
