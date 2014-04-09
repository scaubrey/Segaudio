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

//using namespace Eigen;

class AudioAnalysisController : public ActionListener
{
    
public:
    
    AudioAnalysisController();
    ~AudioAnalysisController();
    
    void setReferenceAudioReader(AudioFormatReader* incomingReader);
    void setTargetAudioReader(AudioFormatReader* incomingReader);
    bool isReady();
    
    void calculateDistances(Array<float>* distanceArray, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, AudioRegion* refRegion, SignalFeaturesToUse* featuresToUse);
    
    Eigen::MatrixXf calculateFeatureMatrix(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion* region);
    
    
    float getLastMaxDistance();
    
    virtual void actionListenerCallback(const String &message);
    
    Array<AudioRegion> getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray);
    
    bool isRegionWithinWidth(float regionFracWidth, ClusterParameters* clusterParams);
    
    int signum(float value);
    
    Array<AudioRegion> invertClusterRegions(Array<AudioRegion> &regions);
    
    void findRegionsGridSearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);
    
    void findRegionsBinarySearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);
    
    void findRegionsGradientDescent(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);
    
    float getRegionCost(Array<AudioRegion> &regions, SearchParameters* searchParams);
        
    bool saveRegionsToAudioFile(Array<AudioRegion> &regions, SegaudioFile* sourceFile, File &destinationFile, bool useSingleFile);
    
    bool saveRegionsToTxtFile(Array<AudioRegion> &regions, SegaudioFile* sourceFile, File &destinationFile);
    
private:
    
    AudioFormatManager* formatManager;
    
    Eigen::MatrixXf refFeatureMat;
    Eigen::MatrixXf targetFeatureMat;
    
    float maxDistance;
    
    int windowSize;
    
    float calculateBlockRMS(AudioSampleBuffer &block);
    
    float calculateZeroCrossRate(AudioSampleBuffer &block);
    
    float calculateSprectralFlux(Eigen::RowVectorXcf &blockFft);
    
    float calculateSpectralCentroid(Eigen::RowVectorXcf &blockFft);
    
    Eigen::RowVectorXf calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate);

};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
