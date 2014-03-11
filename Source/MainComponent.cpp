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

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent (AudioFormatManager &appFormatManager, AudioThumbnailCache &appThumbCache, AudioAnalysisController &analysisController)
    : analysisController(analysisController)
{
    addAndMakeVisible (audioSrcSelector = new AudioSourceSelector());
    audioSrcSelector->setName ("audioSrcSelector");

    addAndMakeVisible (similarityViewer = new SimilarityViewer());
    similarityViewer->setName ("similarityViewer");

    addAndMakeVisible (targetFileSelector = new AudioSourceSelector());
    targetFileSelector->setName ("targetFileSelector");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1000, 600);


    //[Constructor] You can add your own custom stuff here..
    targetFileSelector->setDraggable(false);

    audioSrcSelector->addActionListener(this);
    targetFileSelector->addActionListener(this);
    similarityViewer->addActionListener(this);

    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSrcSelector = nullptr;
    similarityViewer = nullptr;
    targetFileSelector = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6f6f6f));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    audioSrcSelector->setBounds (0, 0, proportionOfWidth (1.0000f), 200);
    similarityViewer->setBounds (0, getHeight() - 450, proportionOfWidth (1.0000f), 450);
    targetFileSelector->setBounds (0, 208, proportionOfWidth (1.0000f), 200);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::actionListenerCallback(const juce::String &message){

    if(message == "srcRegionSelected" and audioSrcSelector->hasFileLoaded() and targetFileSelector->hasFileLoaded()){

        similarityViewer->setReadyToCompare(true);
    }
    else if(message == "srcRegionCleared"){
        similarityViewer->setReadyToCompare(false);
    }
    else if(message == "calculateDistances"){

        File srcFile = audioSrcSelector->getLoadedFile();
        AudioRegion selectedRegion = audioSrcSelector->getSelectedRegion();

        File targetFile = targetFileSelector->getLoadedFile();

        Array<float> distanceArray = analysisController.calculateDistances(srcFile, selectedRegion, targetFile);

        similarityViewer->setDistanceArray(distanceArray, analysisController.getLastMaxDistance());
    }
    else if(message == "candidateRegionsUpdated"){
        Array<AudioRegion> candidateRegions = similarityViewer->getCandidateRegions();

        targetFileSelector->setCandidateRegions(candidateRegions);
        targetFileSelector->repaint();

    }

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public ActionListener" constructorParams="AudioFormatManager &amp;appFormatManager, AudioThumbnailCache &amp;appThumbCache, AudioAnalysisController &amp;analysisController"
                 variableInitialisers="analysisController(analysisController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="600">
  <BACKGROUND backgroundColour="ff6f6f6f"/>
  <GENERICCOMPONENT name="audioSrcSelector" id="6129c3aa019f4bba" memberName="audioSrcSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 200" class="AudioSourceSelector"
                    params=""/>
  <GENERICCOMPONENT name="similarityViewer" id="95cef1a3b684967d" memberName="similarityViewer"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 100% 450" class="SimilarityViewer"
                    params=""/>
  <GENERICCOMPONENT name="targetFileSelector" id="7f10809d3b4712d6" memberName="targetFileSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 208 100% 200" class="AudioSourceSelector"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
