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

class SegaudioFile
{
  
public:
    SegaudioFile();
    ~SegaudioFile();
    
    void setFile(File &newFile);
    AudioSampleBuffer* getFileBuffer();
    
    AudioFormatReaderSource* getSource();
    
    
private:
    
    bool fileSet;
    
    File* internalFile;
    AudioSampleBuffer* internalFileBuffer;
    
    AudioFormatManager formatManager;
    
    AudioFormatReaderSource* fileSource;
};


#endif  // SEGAUDIOFILE_H_INCLUDED
