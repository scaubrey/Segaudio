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

#include "ReferenceContainerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ReferenceContainer::ReferenceContainer ()
{
    addAndMakeVisible (audioSelector = new AudioSourceSelector());
    audioSelector->setName ("audioSelector");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    
    audioSelector->addActionListener(this);
    //[/Constructor]
}

ReferenceContainer::~ReferenceContainer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSelector = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ReferenceContainer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ReferenceContainer::resized()
{
    audioSelector->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ReferenceContainer::setFile(juce::File &newFile){
    audioSelector->setFile(newFile);
}

void ReferenceContainer::setCandidateRegions(Array<AudioRegion> newCandidateRegions){
    audioSelector->setCandidateRegions(newCandidateRegions);
}

bool ReferenceContainer::hasFileLoaded(){
    return audioSelector->hasFileLoaded();
}

AudioRegion ReferenceContainer::getSelectedRegion(){
    return audioSelector->getSelectedRegion();
}

SegaudioFile* ReferenceContainer::getLoadedFile(){
    return audioSelector->getLoadedFile();
}

void ReferenceContainer::clearRegion(){
    audioSelector->clearRegion();
}

void ReferenceContainer::startAudio(){
    audioSelector->startPositionBar();
}

void ReferenceContainer::stopAudio(){
    audioSelector->stopPositionBar();
}

float ReferenceContainer::getPositionBarTime(){
    return audioSelector->getPositionBarTime();
}

void ReferenceContainer::actionListenerCallback(const juce::String &message){
    
    sendActionMessage(message);
    
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ReferenceContainer" componentName=""
                 parentClasses="public Component, public ActionBroadcaster, public ActionListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="audioSelector" id="6129c3aa019f4bba" memberName="audioSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" class="AudioSourceSelector"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
