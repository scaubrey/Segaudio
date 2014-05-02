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
