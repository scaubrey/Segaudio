/*
  ==============================================================================

    SegaudioModel.cpp
    Created: 15 Mar 2014 1:24:10am
    Author:  Cameron Summers

  ==============================================================================
*/

#include "SegaudioModel.h"



SegaudioModel::SegaudioModel(int maxFiles) :
    maxFiles(maxFiles)
{

}

SegaudioModel::~SegaudioModel(){
    
}

bool SegaudioModel::addFile(SegaudioFile* newFile, String componentId){
        
    if(files.getNumSlots() == 0){
        return false;
    }

    files.set(componentId, newFile);
    return false;
}
    

void SegaudioModel::setClusterParams(ClusterParameters newParams){
    clusterParams = newParams;
}

void SegaudioModel::setDistanceArray(Array<float> distanceArray){
    distanceArray = distanceArray;
}

void SegaudioModel::setRefRegion(AudioRegion newRefRegion){
    refRegion = newRefRegion;
}

AudioRegion SegaudioModel::getRefRegion(){
    return refRegion;
}

Array<float>* SegaudioModel::getDistanceArray(){
    return &distanceArray;
}


void SegaudioModel::setMaxDistance(float distance){
    maxDistance = distance;
}

float SegaudioModel::getMaxDistance(){
    return maxDistance;
}

AudioSampleBuffer* SegaudioModel::getFileBuffer(String componenetId){
    return files[componenetId]->getFileBuffer();
}


SignalFeaturesToUse* SegaudioModel::getSignalFeaturesToUse(){
    return &featuresToUse;
}