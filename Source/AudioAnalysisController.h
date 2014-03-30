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
    
    void calculateDistances(Array<float>* distanceArray, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, AudioRegion refRegion, SignalFeaturesToUse* featuresToUse);
    
    Eigen::MatrixXf calculateFeatureMatrix(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion region=AudioRegion());
    
    
    float getLastMaxDistance();
    
    virtual void actionListenerCallback(const String &message);
    
    Array<AudioRegion> getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray);
        
    int signum(float value);
    
    Array<AudioRegion> invertClusterRegions(Array<AudioRegion> &regions);
    
    void findRegions(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);
    
    float getRegionCost(Array<AudioRegion> &regions, SearchParameters* searchParams);
    
    bool saveRegionsToFile(Array<AudioRegion> &regions, AudioSampleBuffer* sourceBuffer, File &destinationFile, bool useSeparateFiles);
    
    
private:
    
    AudioFormatManager* formatManager;
    
    Eigen::MatrixXf refFeatureMat;
    Eigen::MatrixXf targetFeatureMat;
    
    float maxDistance;
    
    int windowSize;
    
//    float calculateMean(Array<float> values);

    float calculateBlockRMS(AudioSampleBuffer &block);
    
    float calculateZeroCrossRate(AudioSampleBuffer &block);
    
    float calculateSprectralFlux(Eigen::RowVectorXcf &blockFft);
    
    Eigen::RowVectorXf calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate);

};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
