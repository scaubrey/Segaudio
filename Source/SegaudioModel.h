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

/*! parameters that control how to calculate candidate regions

*/
struct ClusterParameters{
    float threshold = 0;
    
    float regionConnectionWidth = 1;
    float minRegionTimeWidth = 0;
    float maxRegionTimeWidth = 1;
    
    bool shouldInvertRegions = false;
};

/*! for using combinations of features in similarity calculation

*/
struct SignalFeaturesToUse{
    bool rms = false;   // root mean square
    bool mfcc = false; // mel frequency celpstral coefficients
    bool sf = false; // spectral flux, not implemented yet!
    bool zcr = false; // zero cross rate
    bool sc = false; // spectral centroid

    /*! check if any features are selected
        @return bool
    */
    bool isNoneSelected(){
        if(rms || mfcc || sf || zcr || sc){
            return false;
        }
        return true;
    }

    /*! get number of selected features
        @return int: number of features selected
    */
    int getNumSelected(){
        int numSelected = 0;
        if(rms) numSelected += 1;
        if(mfcc) numSelected += 12; // note 12 features!
        if(sf) numSelected += 1;
        if(zcr) numSelected += 1;
        if(sc) numSelected += 1;
        
        return numSelected;
    }

    /*! check if we need to calculate fft for the selected features
        @return bool
    */
    bool needFft(){
        if(mfcc || sf || sc) return true;
        return false;
    }
};

/*! info for exporting regions

*/
struct ExportParameters{
    bool asOneFile = false; // combine all features into one file if true, separate files if not
    Array<AudioRegion> clusterRegions;
};

/*! parameters from search UI controls

*/
struct SearchParameters{
    int numRegions; // how many regions we're looking for
    float filePercentage; // how much of the file do the regions make up
    
    bool useWidthFilter = false; // use the width filter from cluster tuning
    float minWidth = 0; // holds val from width filter if used
    float maxWidth = 1; // holds val from width filter if used
};

class SegaudioModel
{
public:
    
    SegaudioModel(int maxFiles);
    ~SegaudioModel();

    /*! adds a new file with id
        @param SegaudioFile* newFile
        @param String componentId: id associated with file for lookup
    */
    bool addFile(SegaudioFile* newFile, String componentId);

    /*! current application cluster parameters
        @return ClusterParameters*
    */
    ClusterParameters* getClusterParams();

    /*! set new cluster params in the model
        @param ClusterParameters newParams
        @return void
    */
    void setClusterParams(ClusterParameters newParams);

    /*! sets new distance array for similarity function on the model
        @param Array<float> distanceArray
        @return void
    */
    void setDistanceArray(Array<float> distanceArray);

    /*! gets the current distance array for similarity function
        @return Array<float>*
    */
    Array<float>* getDistanceArray();

    /*! sets new max distance of similarity function on the model
        @param float distance
        @return void
    */
    void setMaxDistance(float distance);

    /*! gets the current max distance of similarity function
        return float*
    */
    float* getMaxDistance();

    /*! gets the SegaudioFile by id
        @param String componentId
        @return SegaudioFile*
    */
    SegaudioFile* getSegaudioFile(String componentId);

    /*! gets file buffer for file with id
        @param String componentId
        @return AudioSampleBuffer*
    */
    AudioSampleBuffer* getFileBuffer(String componentId);

    /*! gets file source for file with id
        @param String componentId
        @return AudioFormatReaderSource*
    */
    AudioFormatReaderSource* getFileSource(String componentId);

    /*! gets current signal features
        @return SignalFeaturesToUse*
    */
    SignalFeaturesToUse* getSignalFeaturesToUse();

    /*! gets current export parameters
        @return ExportParameters*
    */
    ExportParameters* getExportParameters();

    /*! gets current search parameters
        @return SearchParameters*
    */
    SearchParameters* getSearchParameters();

    /*! gets file with id
        @param String componentId
        @return SegaudioFile*
    */
    SegaudioFile* getFileById(String componentId);

    /*! gets current reference region, only one right now though we can hold more for later multi-reference processing
        @return Array<AudioRegion>*
    */
    Array<AudioRegion>* getReferenceRegions();

    /*! gets current target regions
        @return Array<AudioRegion>*
    */
    Array<AudioRegion>* getTargetRegions();

    /*! clears the current target regions and distance array
        @return void
    */
    void clearTargetRegions();
    
private:
        
    int maxFiles; // not used right now, for handling multiple files later
    
    ClusterParameters clusterParams; // parameters that calculate the clusters (regions) from the similarity function
    
    Array<float> distanceArray; // distances from similarity function

    HashMap<String, SegaudioFile*> files; // not used right now, for handling multiple files later
    
    SegaudioFile* refFile;
    SegaudioFile* targetFile;
    
    float maxDistance; // max distance in distance array for similarity function, used for scaling
    
    SignalFeaturesToUse featuresToUse; // which features used to calculate similarity function
    
    ExportParameters exportParameters; // parameters for exporting the clusters (regions)
    
    SearchParameters searchParameters; // parameters for searching for matching clusters (regions)

    Array<AudioRegion> referenceRegions; // holds regions used as reference
    Array<AudioRegion> targetRegions; // holds regions used for target
};



#endif  // SEGAUDIOMODEL_H_INCLUDED
