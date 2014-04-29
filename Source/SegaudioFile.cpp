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
    internalFileBuffer = nullptr;
}

void SegaudioFile::setFile(File &newFile){
    
    internalFile = &newFile;

    formatReader = formatManager.createReaderFor(*internalFile);

    newFileSource = new AudioFormatReaderSource(formatReader, false);

    internalFileBuffer->setSize(formatReader->numChannels, formatReader->lengthInSamples);
    
    totalNumSamples = formatReader->lengthInSamples;
    sampleRate = formatReader->sampleRate;
    numChannels = formatReader->numChannels;
    
    formatReader->read(internalFileBuffer, 0, formatReader->lengthInSamples, 0, true, true);
    
    fileSet = true;
}


AudioSampleBuffer* SegaudioFile::getFileBuffer(){
    if(fileSet){
        return internalFileBuffer;
    }
    return NULL;
}

AudioFormatReaderSource* SegaudioFile::getSource(){
    return newFileSource;
}

int SegaudioFile::getNumSamples(){
    return totalNumSamples;
}

int SegaudioFile::getNumChannels(){
    return numChannels;
}

int SegaudioFile::getSampleRate(){
    return sampleRate;
}