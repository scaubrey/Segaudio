/*
  ==============================================================================

    SegaudioFile.h
    Created: 15 Mar 2014 10:45:00am
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef SEGAUDIOFILE_H_INCLUDED
#define SEGAUDIOFILE_H_INCLUDED

#include "JuceHeader.h"
#include "AudioRegion.h"

/*! wrapper for Juce file to hide away some of the logic for getting file info

*/
class SegaudioFile : public File
{
  
public:
    SegaudioFile();
    ~SegaudioFile();

    /*! sets the internal file
        @param File &newFile
        @return void
    */
    void setFile(File &newFile);

    /*! gets the samples in a buffer
        @return AudioSampleBuffer*
    */
    AudioSampleBuffer* getFileBuffer();

    /*! gets a format source for the file, used by various other components in the application
        @return AudioFormatReaderSource*
    */
    AudioFormatReaderSource* getSource();
    
    int getNumSamples();
    int getSampleRate();
    int getNumChannels();
    
    
private:
    
    bool fileSet; // whether a file is set
    
    File* internalFile;
    AudioSampleBuffer* internalFileBuffer;
    
    AudioFormatManager formatManager;  // used for getting a reader

    ScopedPointer<AudioFormatReader> formatReader; // for reading the file

    ScopedPointer<AudioFormatReaderSource> newFileSource; // used by audio transport
    
    int totalNumSamples;
    int sampleRate;
    int numChannels;
};


#endif  // SEGAUDIOFILE_H_INCLUDED
