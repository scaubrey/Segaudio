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
AudioSourceSelector::AudioSourceSelector (AudioFormatManager &appFormatManager, AudioThumbnailCache &appThumbCache)
{
    setName ("audioSourceSelector");

    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 150);


    //[Constructor] You can add your own custom stuff here..
    thumbComponent = new AudioThumbnail (50, appFormatManager, appThumbCache);

    //[/Constructor]
}

AudioSourceSelector::~AudioSourceSelector()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    thumbComponent = nullptr;

    //[/Destructor]
}

//==============================================================================
void AudioSourceSelector::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffc76060));

    //[UserPaint] Add your own custom painting code here..
    
//    if(hasRegionSelected){
//        regionOverlay.setAlwaysOnTop(true);
        g.fillAll(Colour(Colours::chocolate));
//        regionOverlay.draw(g, 0.5);
        
        g.setOpacity(0.5);
    
        int x = regionOverlay.getX();
        int y = regionOverlay.getY();
        int w = regionOverlay.getWidth();
        int h = regionOverlay.getHeight();
        
        g.fillRect(x,y,w,h);
//    }
//    std::cout << getX() << " " << getY() << " " << getWidth() << " " << getHeight() << std::endl;
    
    thumbComponent->drawChannel(g, getBounds(), 0, thumbComponent->getTotalLength(), 0, 1.5);

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

void AudioSourceSelector::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    
    int startX = e.getMouseDownX();
    int width = e.getDistanceFromDragStartX();
    
    if(width < 0){  // enable dragging both ways
        startX = startX + width;
        width = abs(width);
    }
    
    drawSelectedRegion(startX, width);
    hasRegionSelected = true;
    
    //[/UserCode_mouseDrag]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void AudioSourceSelector::setSource(const File &referenceFile){
    
    FileInputSource fileInput(referenceFile);
    
    thumbComponent->setSource(&fileInput);
    
    repaint();
        
}

void AudioSourceSelector::drawSelectedRegion(int startX, int width){
    
//    if(hasRegionSelected){
        regionOverlay.setBounds(startX, 0, width, this->getHeight());
        
//    }
    repaint();

}

void AudioSourceSelector::getAudioSelection(){
    
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioSourceSelector" componentName="audioSourceSelector"
                 parentClasses="public Component" constructorParams="AudioFormatManager &amp;appFormatManager, AudioThumbnailCache &amp;appThumbCache"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="800" initialHeight="150">
  <METHODS>
    <METHOD name="visibilityChanged()"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffc76060"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
