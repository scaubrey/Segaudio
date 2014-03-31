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
MainComponent::MainComponent (AudioAnalysisController &analysisController)
    : analysisController(&analysisController)
{
    addAndMakeVisible (referenceFileComponent = new ReferenceFileComponent (deviceManager));
    referenceFileComponent->setName ("referenceFileComponent");

    addAndMakeVisible (targetFileComponent = new TargetFileComponent (deviceManager));
    targetFileComponent->setName ("targetFileComponent");

    addAndMakeVisible (controlPanelComponent = new ControlPanelComponent());
    controlPanelComponent->setName ("controlPanelComponent");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1000, 600);


    //[Constructor] You can add your own custom stuff here..

    referenceFileComponent->addActionListener(this);
    targetFileComponent->addActionListener(this);
    controlPanelComponent->addActionListener(this);

    isRefFileLoaded = false;
    isTargetFileLoaded = false;
    isRegionSelected = false;

    appModel = new SegaudioModel(2);

    deviceManager.initialise(2, 2, 0, true, String::empty, 0);

	AudioIODeviceType* const audioDeviceType = deviceManager.getCurrentDeviceTypeObject();
	StringArray audioInputDevices (audioDeviceType->getDeviceNames(true));
    StringArray audioOutputDevices (audioDeviceType->getDeviceNames(false));
	AudioDeviceManager::AudioDeviceSetup deviceConfig;
    deviceManager.getAudioDeviceSetup(deviceConfig);

	deviceConfig.inputDeviceName = audioInputDevices[0];
	deviceConfig.outputDeviceName= audioOutputDevices[0];
    String result = deviceManager.setAudioDeviceSetup (deviceConfig, true);

    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    referenceFileComponent = nullptr;
    targetFileComponent = nullptr;
    controlPanelComponent = nullptr;


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
    referenceFileComponent->setBounds ((0) + (proportionOfWidth (0.2235f)), 0, proportionOfWidth (0.7730f), proportionOfHeight (0.1998f));
    targetFileComponent->setBounds ((0) + (proportionOfWidth (0.2235f)), proportionOfHeight (0.1985f), proportionOfWidth (0.7730f), proportionOfHeight (0.5000f));
    controlPanelComponent->setBounds (0, 0, proportionOfWidth (0.2235f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::actionListenerCallback(const juce::String &message){

    if(message.contains("setReferenceFile")){

//        int delimiterIdx = message.indexOfChar(wchar_t("-"));
//        String componentId = message.substring(delimiterIdx+1);

        appModel->addFile(referenceFileComponent->getLoadedFile(), "0");
        isRefFileLoaded = true;
        if(isReadyToCompare()) controlPanelComponent->setCalcEnabled(true);
    }
    else if(message.contains("setTargetFile")){

        appModel->addFile(targetFileComponent->getLoadedFile(), "1");
        isTargetFileLoaded = true;
        if(isReadyToCompare()) controlPanelComponent->setCalcEnabled(true);
    }
    else if(message == "srcRegionSelected"){

        AudioRegion selectedRegion = referenceFileComponent->getSelectedRegion();
        appModel->setRefRegion(selectedRegion);
        isRegionSelected = true;
        if(isReadyToCompare()) controlPanelComponent->setCalcEnabled(true);
    }
    else if(message == "srcRegionCleared"){
//        similarityViewer->setReadyToCompare(false);
//        similarityViewer->clear();
    }
    else if(message == "calculateSimilarity"){

        targetFileComponent->clearSimilarity();
        targetFileComponent->setCalculatingMask(true);
        
        analysisController->calculateDistances(appModel->getDistanceArray(), appModel->getFileBuffer("0"), appModel->getFileBuffer("1"), appModel->getRefRegion(), controlPanelComponent->getSignalFeaturesToUse(appModel->getSignalFeaturesToUse()));
        appModel->setMaxDistance(analysisController->getLastMaxDistance());
        
        targetFileComponent->setCalculatingMask(false);

        newRegionsUpdate();
    }
    else if(message == "clusterParamsChanged"){
        newRegionsUpdate();
    }
    else if(message == "search"){
        controlPanelComponent->getSearchParameters(appModel->getSearchParameters());
                                                   
        analysisController->findRegionsBinarySearch(appModel->getSearchParameters(), appModel->getDistanceArray(), appModel->getClusterParams());
        
        // set found params on control panel
        controlPanelComponent->setClusterParams(appModel->getClusterParams());
        
        newRegionsUpdate();
    }
    else if(message == "exportRegions"){
        
        ClusterParameters* clusterTuningParams = controlPanelComponent->getClusterParams();
        Array<AudioRegion> clusterRegions = analysisController->getClusterRegions(clusterTuningParams, appModel->getDistanceArray());
        
        ExportParameters* exportParams = appModel->getExportParameters();
        controlPanelComponent->getExportParameters(exportParams);
        String prompt = "Saving " + String(clusterRegions.size()) + " regions";
        if(exportParams->asOneFile){
            prompt += " as one file...";
        }
        else{
            prompt += " as multiple files...";
        }

        FileChooser myChooser (prompt);
        if (myChooser.browseForFileToSave(true))
        {
            File destinationFile = myChooser.getResult();

            DBG(destinationFile.getFullPathName());
            
            analysisController->saveRegionsToFile(clusterRegions, appModel->getFileBuffer("1"), destinationFile, true);
        }
    }

    std::cout << "Message fired: " << message << std::endl;

}

void MainComponent::newRegionsUpdate(){

    ClusterParameters* clusterTuningParams = controlPanelComponent->getClusterParams();
    Array<AudioRegion> clusterRegions = analysisController->getClusterRegions(clusterTuningParams, appModel->getDistanceArray());

    targetFileComponent->update(clusterTuningParams, clusterRegions, appModel->getDistanceArray(), appModel->getMaxDistance());
    
    controlPanelComponent->newRegionsUpdate(clusterRegions);
}



bool MainComponent::isReadyToCompare(){
    if(isRefFileLoaded and isTargetFileLoaded and isRegionSelected){
        return true;
    }
    return false;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public ActionListener" constructorParams="AudioAnalysisController &amp;analysisController"
                 variableInitialisers="analysisController(&amp;analysisController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="600">
  <BACKGROUND backgroundColour="ff6f6f6f"/>
  <GENERICCOMPONENT name="referenceFileComponent" id="6129c3aa019f4bba" memberName="referenceFileComponent"
                    virtualName="" explicitFocusOrder="0" pos="0R 0 77.299% 19.975%"
                    posRelativeX="a6f0554ce8852899" class="ReferenceFileComponent"
                    params="deviceManager"/>
  <GENERICCOMPONENT name="targetFileComponent" id="7f10809d3b4712d6" memberName="targetFileComponent"
                    virtualName="" explicitFocusOrder="0" pos="0R 19.851% 77.299% 50%"
                    posRelativeX="a6f0554ce8852899" class="TargetFileComponent" params="deviceManager"/>
  <GENERICCOMPONENT name="controlPanelComponent" id="a6f0554ce8852899" memberName="controlPanelComponent"
                    virtualName="" explicitFocusOrder="0" pos="0 0 22.352% 100%"
                    class="ControlPanelComponent" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
