/*
This file is part of Segaudio.

Segaudio is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Segaudio is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Segaudio.  If not, see <http://www.gnu.org/licenses/>.
/**/

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