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

#include "TargetContainerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TargetContainer::TargetContainer ()
{
    addAndMakeVisible (audioSelector = new AudioSourceSelector (AudioSourceSelector::Target));
    audioSelector->setName ("audioSelector");

    addAndMakeVisible (similarityViewer = new SimilarityViewer());
    similarityViewer->setName ("similarityViewer");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    audioSelector->addActionListener(this);

    audioSelector->setMode(AudioSourceSelector::Target);

    //[/Constructor]
}

TargetContainer::~TargetContainer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSelector = nullptr;
    similarityViewer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TargetContainer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffb5b2b2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TargetContainer::resized()
{
    audioSelector->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.4901f));
    similarityViewer->setBounds (0, getHeight() - proportionOfHeight (0.4901f), proportionOfWidth (1.0000f), proportionOfHeight (0.4901f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TargetContainer::setFile(juce::File newFile){
    audioSelector->setFile(newFile);
}
void TargetContainer::setTuningParameters(ClusterParameters* clusterTuningParams, Array<float>* newDistances, float* maxDistance){

    audioSelector->repaint();
    similarityViewer->setTuningParameters(clusterTuningParams, newDistances, maxDistance);
}

void TargetContainer::startAudio(){
    audioSelector->startPositionBar();
}

void TargetContainer::stopAudio(){
    audioSelector->stopPositionBar();
}

float TargetContainer::getPositionBarTime(){
    return audioSelector->getPositionBarTime();
}

void TargetContainer::actionListenerCallback(const juce::String &message){
    sendActionMessage(message);
}

void TargetContainer::clearSimilarity(){
    similarityViewer->clear();
}

void TargetContainer::setRegions(Array<AudioRegion> *regions_) {
    audioSelector->setRegions(regions_);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TargetContainer" componentName=""
                 parentClasses="public Component, public ActionBroadcaster, public ActionListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffb5b2b2"/>
  <GENERICCOMPONENT name="audioSelector" id="7f10809d3b4712d6" memberName="audioSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 49.007%"
                    class="AudioSourceSelector" params="AudioSourceSelector::Target"/>
  <GENERICCOMPONENT name="similarityViewer" id="95cef1a3b684967d" memberName="similarityViewer"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 100% 49.007%"
                    class="SimilarityViewer" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
