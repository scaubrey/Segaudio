/*
  ==============================================================================

    SegaudioModel.h
    Created: 15 Mar 2014 1:24:10am
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef SEGAUDIOMODEL_H_INCLUDED
#define SEGAUDIOMODEL_H_INCLUDED

#include "JuceHeader.h"
#include "SegaudioFile.h"
#include "AudioRegion.h"

struct ClusterParameters{
    float threshold;
    
    int regionConnectionWidth;
    
    float medianFilterWidth;
    
    float minRegionTimeWidth;
    float maxRegionTimeWidth;
};

struct SignalFeaturesToUse{
    bool rms;
    bool mfcc;
    bool sf;
    bool zcr;
    
    bool isNoneSelected(){
        if(rms || mfcc || sf || zcr){
            return true;
        }
        return false;
    }
};

class SegaudioModel
{
public:
    
    SegaudioModel(int maxFiles);
    ~SegaudioModel();
    
    bool addFile(SegaudioFile* newFile, String componentId);
    
    void setClusterParams(ClusterParameters newParams);
    
    void setDistanceArray(Array<float> distanceArray);
    Array<float>* getDistanceArray();


    void setRefRegion(AudioRegion newRefRegion);
    AudioRegion getRefRegion();
    
    void setMaxDistance(float distance);
    float getMaxDistance();
    
    AudioSampleBuffer* getFileBuffer(String componentId);
    
    SignalFeaturesToUse* getSignalFeaturesToUse();
    
private:
        
    int maxFiles;
    
    ClusterParameters clusterParams;
    
    Array<float> distanceArray;
    
    AudioRegion refRegion;
    
    HashMap<String, SegaudioFile*> files;
    
    float maxDistance;
    
    SignalFeaturesToUse featuresToUse;
};



#endif  // SEGAUDIOMODEL_H_INCLUDED
