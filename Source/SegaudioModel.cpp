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
    // TODO set max files here?
}

SegaudioModel::~SegaudioModel(){
    
}

bool SegaudioModel::addFile(SegaudioFile* newFile, String componentId){
        
//    if(files.getNumSlots() == 0){
//        return false;
//    }
    
    if(componentId == "0"){
        refFile = newFile;
    }
    else if(componentId == "1"){
        targetFile = newFile;
    }

//    files.set(componentId, newFile);
    return true;
}

ClusterParameters* SegaudioModel::getClusterParams(){
    return &clusterParams;
}

void SegaudioModel::setClusterParams(ClusterParameters newParams){
    clusterParams = newParams;
}

void SegaudioModel::setDistanceArray(Array<float> distanceArray){
    distanceArray = distanceArray;
}

Array<float>* SegaudioModel::getDistanceArray(){
    return &distanceArray;
}

void SegaudioModel::setMaxDistance(float distance){
    maxDistance = distance;
}

float* SegaudioModel::getMaxDistance(){
    return &maxDistance;
}

SegaudioFile* SegaudioModel::getSegaudioFile(String componentId){
//    return files[componentId];
    return getFileById(componentId);
}

AudioSampleBuffer* SegaudioModel::getFileBuffer(String componentId){
//    return files[componenetId]->getFileBuffer();
    return getFileById(componentId)->getFileBuffer();
}

AudioFormatReaderSource* SegaudioModel::getFileSource(String componentId){
//    return files[componenetId]->getSource();
    return getFileById(componentId)->getSource();
}

SignalFeaturesToUse* SegaudioModel::getSignalFeaturesToUse(){
    return &featuresToUse;
}

ExportParameters* SegaudioModel::getExportParameters(){
    return &exportParameters;
}

SearchParameters* SegaudioModel::getSearchParameters(){
    return &searchParameters;
}

SegaudioFile* SegaudioModel::getFileById(String componentId){
    if(componentId == "0"){
        return refFile;
    }
    else if(componentId == "1"){
        return targetFile;
    }
    
    return NULL;
}

Array<AudioRegion> *SegaudioModel::getReferenceRegions() {
    return &referenceRegions;
}

Array<AudioRegion> *SegaudioModel::getTargetRegions() {
    return &targetRegions;
}

void SegaudioModel::clearTargetRegions() {
    targetRegions.clear();
    distanceArray.clear();
}
