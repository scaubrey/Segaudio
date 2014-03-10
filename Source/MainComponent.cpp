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
MainComponent::MainComponent (AudioFormatManager &appFormatManager, AudioThumbnailCache &appThumbCache)
{
    addAndMakeVisible (thresholdSlider = new Slider ("thresholdSlider"));
    thresholdSlider->setRange (0, 10, 0);
    thresholdSlider->setSliderStyle (Slider::LinearVertical);
    thresholdSlider->setTextBoxStyle (Slider::TextBoxAbove, true, 80, 20);
    thresholdSlider->addListener (this);

    addAndMakeVisible (thresholdSliderLabel = new Label ("thresholdSliderLabel",
                                                         TRANS("Threshold")));
    thresholdSliderLabel->setFont (Font (15.00f, Font::plain));
    thresholdSliderLabel->setJustificationType (Justification::centredLeft);
    thresholdSliderLabel->setEditable (false, false, false);
    thresholdSliderLabel->setColour (TextEditor::textColourId, Colours::black);
    thresholdSliderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rmsToggle = new ToggleButton ("new toggle button"));
    rmsToggle->setButtonText (TRANS("RMS"));
    rmsToggle->addListener (this);

    addAndMakeVisible (analyzeButton = new TextButton ("analyzeButton"));
    analyzeButton->setButtonText (TRANS("Open File to Analyze"));
    analyzeButton->addListener (this);

    addAndMakeVisible (audioSrcSelector = new AudioSourceSelector (appFormatManager, appThumbCache));
    audioSrcSelector->setName ("audioSrcSelector");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1000, 600);


    //[Constructor] You can add your own custom stuff here..
    sourceSamplesPerThumbnailSample = 50;

    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    thresholdSlider = nullptr;
    thresholdSliderLabel = nullptr;
    rmsToggle = nullptr;
    analyzeButton = nullptr;
    audioSrcSelector = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff6f6f6f));

    g.setColour (Colours::black);
    g.setFont (Font (15.00f, Font::plain));
    g.drawText (TRANS("Your text goes here"),
                448, 384, 200, 30,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    thresholdSlider->setBounds (528, 64, 48, 296);
    thresholdSliderLabel->setBounds (520, 32, 72, 24);
    rmsToggle->setBounds (616, 296, 150, 24);
    analyzeButton->setBounds (24, 24, 150, 24);
    audioSrcSelector->setBounds (8, 116, 840, 300);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == thresholdSlider)
    {
        //[UserSliderCode_thresholdSlider] -- add your slider handling code here..
        //[/UserSliderCode_thresholdSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == rmsToggle)
    {
        //[UserButtonCode_rmsToggle] -- add your button handler code here..
        //[/UserButtonCode_rmsToggle]
    }
    else if (buttonThatWasClicked == analyzeButton)
    {
        //[UserButtonCode_analyzeButton] -- add your button handler code here..
        FileChooser myChooser ("Please select the file you want to load...");
        if (myChooser.browseForFileToOpen())
        {
            const File referenceFile = myChooser.getResult();
            
            audioSrcSelector->setSource(referenceFile);
            std::cout << referenceFile.getFileName();
        }
        //[/UserButtonCode_analyzeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="AudioFormatManager appFormatManager, AudioThumbnailCache appThumbCache"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="1000" initialHeight="600">
  <BACKGROUND backgroundColour="ff6f6f6f">
    <TEXT pos="448 384 200 30" fill="solid: ff000000" hasStroke="0" text="Your text goes here"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="thresholdSlider" id="f0c1941bf1c4bcc1" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="528 64 48 296" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="thresholdSliderLabel" id="d44bed1d6775735c" memberName="thresholdSliderLabel"
         virtualName="" explicitFocusOrder="0" pos="520 32 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="20012ffca5548d38" memberName="rmsToggle"
                virtualName="" explicitFocusOrder="0" pos="616 296 150 24" buttonText="RMS"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="analyzeButton" id="128801367cca2e0d" memberName="analyzeButton"
              virtualName="" explicitFocusOrder="0" pos="24 24 150 24" buttonText="Open File to Analyze"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="audioSrcSelector" id="6129c3aa019f4bba" memberName="audioSrcSelector"
                    virtualName="" explicitFocusOrder="0" pos="8 416 840 200" class="AudioSourceSelector"
                    params="appFormatManager, appThumbCache"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
