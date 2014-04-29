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

class SegaudioFile : public File
{
  
public:
    SegaudioFile();
    ~SegaudioFile();
    
    void setFile(File &newFile);
    AudioSampleBuffer* getFileBuffer();
    
    AudioFormatReaderSource* getSource();
    
    int getNumSamples();
    int getSampleRate();
    int getNumChannels();
    
    
private:
    
    bool fileSet;
    
    File* internalFile;
    AudioSampleBuffer* internalFileBuffer;
    
    AudioFormatManager formatManager;

    ScopedPointer<AudioFormatReader> formatReader;

//    ScopedPointer<AudioFormatReaderSource> oldFileSource;
    ScopedPointer<AudioFormatReaderSource> newFileSource;
    
    int totalNumSamples;
    int sampleRate;
    int numChannels;
};


#endif  // SEGAUDIOFILE_H_INCLUDED
