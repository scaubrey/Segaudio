/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "AudioAnalysisController.h"


//==============================================================================
class SegaudioApplication  : public JUCEApplication
{
public:
    //==============================================================================
    SegaudioApplication() {}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Add your application's initialisation code here..
        mainWindow = new MainWindow();
    }

    void shutdown()
    {
        // Add your application's shutdown code here..
        mainWindow = nullptr;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }
    
     //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow()  : DocumentWindow ("MainWindow",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
        {
            
            appFormatManager = new AudioFormatManager();
            appFormatManager->registerBasicFormats();
            
            appThumbCache = new AudioThumbnailCache(3);  // store 3 thumbnails
            
            analysisController = new AudioAnalysisController;
            
            setContentOwned (new MainComponent(*appFormatManager, *appThumbCache, *analysisController), true);

            maximiseButtonPressed();
            setVisible (true);
        }

        void closeButtonPressed()
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            appFormatManager = nullptr;
            appThumbCache = nullptr;
            
            analysisController = nullptr;
            
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        
        AudioAnalysisController* analysisController;
        
        AudioFormatManager* appFormatManager;
        AudioThumbnailCache* appThumbCache;
    };
    
private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (SegaudioApplication)
