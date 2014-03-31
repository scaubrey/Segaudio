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
    float threshold = 0;
    
    float regionConnectionWidth = 1;
    
//    float medianFilterWidth;
    
    float minRegionTimeWidth = 0;
    float maxRegionTimeWidth = 1;
    
    bool shouldInvertRegions = false;
};

struct SignalFeaturesToUse{
    bool rms = false;
    bool mfcc = false;
    bool sf = false;
    bool zcr = false;
    
    bool isNoneSelected(){
        if(rms || mfcc || sf || zcr){
            return false;
        }
        return true;
    }
    
    int getNumSelected(){
        int numSelected = 0;
        if(rms) numSelected += 1;
        if(mfcc) numSelected += 12; // note 12 features!
        if(sf) numSelected += 1;
        if(zcr) numSelected += 1;
        
        return numSelected;
    }
    
    bool needFft(){
        if(mfcc || sf) return true;
        return false;
    }
};

struct ExportParameters{
    bool asOneFile = false;
    Array<AudioRegion> clusterRegions;
};

struct SearchParameters{
    int numRegions;
    float filePercentage;
    
    bool useWidthFilter = false;
    float minWidth = 0;
    float maxWidth = 1;
};

class SegaudioModel
{
public:
    
    SegaudioModel(int maxFiles);
    ~SegaudioModel();
    
    bool addFile(SegaudioFile* newFile, String componentId);
    
    ClusterParameters* getClusterParams();
    
    void setClusterParams(ClusterParameters newParams);
    
    void setDistanceArray(Array<float> distanceArray);
    Array<float>* getDistanceArray();


    void setRefRegion(AudioRegion newRefRegion);
    AudioRegion getRefRegion();
    
    void setMaxDistance(float distance);
    float getMaxDistance();
    
    AudioSampleBuffer* getFileBuffer(String componentId);
    
    SignalFeaturesToUse* getSignalFeaturesToUse();
    
    ExportParameters* getExportParameters();
    
    SearchParameters* getSearchParameters();
    
private:
        
    int maxFiles;
    
    ClusterParameters clusterParams;
    
    Array<float> distanceArray;
    
    AudioRegion refRegion;
    
    HashMap<String, SegaudioFile*> files;
    
    float maxDistance;
    
    SignalFeaturesToUse featuresToUse;
    
    ExportParameters exportParameters;
    
    SearchParameters searchParameters;
};



#endif  // SEGAUDIOMODEL_H_INCLUDED
