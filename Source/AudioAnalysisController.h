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
    
    Array<float> medianFilter(Array<float> distanceArray, int width);
    
    int signum(float value);
    
private:
    
    AudioFormatManager* formatManager;
    
    Eigen::MatrixXf refFeatureMat;
    Eigen::MatrixXf targetFeatureMat;
    
    float maxDistance;
    
    int windowSize;
    
//    float calculateMean(Array<float> values);

    float calculateBlockRMS(AudioSampleBuffer &block);
    
    float calculateZeroCrossRate(AudioSampleBuffer &block);

};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
