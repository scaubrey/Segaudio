/*
  ==============================================================================

    AudioAnalysisController.h
    Created: 9 Mar 2014 10:45:52pm
    Author:  Cameron Summers

  ==============================================================================
*/

#ifndef AUDIOANALYSISCONTROLLER_H_INCLUDED
#define AUDIOANALYSISCONTROLLER_H_INCLUDED

#include "JuceHeader.h"
#include "AudioRegion.h"
#include "SegaudioModel.h"
#include "Eigen.h"
#include "Eigen/FFT.h"
#include <math.h>

class AudioAnalysisController : public ActionListener,
                                public ThreadWithProgressWindow
{
    
public:
    
    AudioAnalysisController();
    ~AudioAnalysisController();

    /*! calculate distances between reference region and target file for similarity function
        @param Array<float>* distanceArray: holds the distances calculated
        @param float* maxDistance: holds the maximum distance, so we don't have to calculate later
        @param AudioSampleBuffer* refRegionBuffer: samples from reference region
        @param AudioSampleBuffer* targetBuffer: samples from target file
        @param Array<AudioRegion>* refRegions: region (one for now) to use a reference
        @param SignalFeaturesToUse* featuresToUse: features to calculate in feature matrix
        @return void
    */
    void calculateDistances(Array<float>* distanceArray, float* maxDistance, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, Array<AudioRegion>* refRegions, SignalFeaturesToUse* featuresToUse);

    /*! calculates the features matrix for the selected features
        @param AudioSampleBuffer* buffer: actual samples to use for calculation
        @param SignalFeaturesToUse* featuresToUse: which features to calculate
        @param AudioRegion region: for reference, this is a part of reference file, for target this is region from 0 to 1
        @return Eigen::MatrixXf: x dimensional matrix, since we don't know how many features
    */
    Eigen::MatrixXf calculateFeatureMatrix(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion region);

    /*! handle action callbacks
        @param const String &message
        @return void
    */
    virtual void actionListenerCallback(const String &message);

    /*! calculates the regions to extract given the similarity function
        @param ClusterParameters* clusterParams: values from UI that determine regions (ie threshold of similarity)
        @param Array<float>* distanceArray: similarity function data points
        @param float* maxDistance: maximium distance
        @param Array<AudioRegion>* regions: holds the calculated regions
        @return void
    */
    void getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray, float* maxDistance,  Array<AudioRegion>* regions);

    /*! checks in if the width of a candidate region is within width filter
        @param float regionFracWidth: raw width of region
        @param ClusterParameters* clusterParams: get width values from here
        @return bool
    */
    bool isRegionWithinWidth(float regionFracWidth, ClusterParameters* clusterParams);

    /*! get sign, used for zero cross calculation
        @param float value: value for which to get sign
        @return int: 1 for positive, -1 for negative, 0 if 0
    */
    int signum(float value);

    /*! given a set of cluster regions, get new set connecting ends with starts and starts with ends
        @param Array<AudioRegion>* regions: regions to invert and replace
        @return void
    */
    void invertClusterRegions(Array<AudioRegion>* regions);

    /*! grid search of cluster parameters that provide lowest cost from getRegionCost
        @param SearchParameters* searchParams: params from search of UI
        @param Array<float>* distanceArray: similarity function data points
        @param float* maxDistance: max distance of similarity function
        @param ClusterParameters* bestParams: params that give lowest cost to pass to model
        @param Array<AudioRegion>* regions: regions to calculate from best params
        @return void
    */
    void findRegionsGridSearch(SearchParameters* searchParams, Array<float>* distanceArray, float* maxDistance, ClusterParameters* bestParams, Array<AudioRegion>* regions);


    // not used, but leaving for now
    void findRegionsBinarySearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams, Array<AudioRegion>* regions);

    // not implemented, may be best option for search
    void findRegionsGradientDescent(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);

    /*! assigns a cost to the regions calculated from a set of cluster parameters
        @param Array<AudioRegion>* regions: regions used for calculating cost of cluster params
        @param SearchParameters* searchParams: used to evaluate cost
        @return float: cost
    */
    float getRegionCost(Array<AudioRegion>* regions, SearchParameters* searchParams);

    /*! saves regions of audio to audio file(s)
        @param Array<AudioRegion>* regions: regions to save
        @param SegaudioFile* sourceFile: file to save from
        @param File &destinationFile: file(s) to save to
        @param bool useSingleFile: save all regions into one file or multiple files
        @return bool
    */
    bool saveRegionsToAudioFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile, bool useSingleFile);

    /*! saves region boundaries in seconds in a CSV
        @param Array<AudioRegion>* regions: regions to save
        @param SegaudioFile* sourceFile: used for getting boundary values in seconds
        @param File &destinationFile: file to save to
        @return bool
    */
    bool saveRegionsToTxtFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile);
    
private:
    
    AudioFormatManager* formatManager; // handles audio format for creating readers and writers
    
    Eigen::MatrixXf refFeatureMat; // feature matrix for reference region, maybe doesn't need to be a member
    Eigen::MatrixXf targetFeatureMat; // feature matrix for target file, maybe doesn't need to be a member

    int windowSize; // size of blocks and fft, can be made variable in UI easily if we want

    /*! calculate RMS for block of audio samples
        @param AudioSampleBuffer &block
        @return float: RMS val
    */
    float calculateBlockRMS(AudioSampleBuffer &block);

    /*! calculate zero cross rate for block of audio samples
        @param AudioSampleBuffer &block
        @return float: zero cross rate val
    */
    float calculateZeroCrossRate(AudioSampleBuffer &block);

    /*! calculate spectral flux from an fft of a block
        @param Eigen::RowVectorXcf &blockFft
        @return float: spectral flux val
    */
    float calculateSprectralFlux(Eigen::RowVectorXcf &blockFft);

    /*! calculate spectral centroid from an fft of a block
        @param Eigen::RowVectorXcf &blockFft
        @return float: spectral centroid val
    */
    float calculateSpectralCentroid(Eigen::RowVectorXcf &blockFft);

    /*! calculate MFCCs from an fft of a block
        @param Eigen::RowVectorXcf &blockFft
        @param int sampleRate
        @return Eigen::RowVectorXf: coefficient vals
    */
    Eigen::RowVectorXf calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate);

    /*! dummy implementation so we can use JUCE progess bar for calculation
        @return void
    */
    void run();

};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
