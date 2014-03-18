/*
  ==============================================================================

    SegaudioFile.cpp
    Created: 15 Mar 2014 10:45:00am
    Author:  Cameron Summers

  ==============================================================================
*/

#include "SegaudioFile.h"

SegaudioFile::SegaudioFile(){
    
    formatManager.registerBasicFormats();
    internalFileBuffer = new AudioSampleBuffer(2, 1);
    fileSet = false;

}

SegaudioFile::~SegaudioFile(){
    delete internalFileBuffer;
}

void SegaudioFile::setFile(File &newFile){
    internalFile = &newFile;
    
    ScopedPointer<AudioFormatReader> tmpReader = formatManager.createReaderFor(*internalFile);
    
    internalFileBuffer->setSize(tmpReader->numChannels, tmpReader->lengthInSamples);
    
    tmpReader->read(internalFileBuffer, 0, tmpReader->lengthInSamples, 0, true, true);
    
    fileSet = true;
}


AudioSampleBuffer* SegaudioFile::getFileBuffer(){
    if(fileSet){
        return internalFileBuffer;
    }
    return NULL;
}

AudioFormatReaderSource* SegaudioFile::getSource(){
    
    if(fileSet){
        AudioFormatReader* semiTmpReader = formatManager.createReaderFor(*internalFile);
        
        fileSource = new AudioFormatReaderSource(semiTmpReader, true);
        
        return fileSource;
    }
    return NULL;
}