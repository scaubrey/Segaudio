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
    
    void setReferenceAudioReader(AudioFormatReader* incomingReader);
    void setTargetAudioReader(AudioFormatReader* incomingReader);
    bool isReady();
    
    void calculateDistances(Array<float>* distanceArray, float* maxDistance, AudioSampleBuffer* refRegionBuffer, AudioSampleBuffer* targetBuffer, Array<AudioRegion>* refRegions, SignalFeaturesToUse* featuresToUse);
    
    Eigen::MatrixXf calculateFeatureMatrix(AudioSampleBuffer* buffer, SignalFeaturesToUse* featuresToUse, AudioRegion region);


    virtual void actionListenerCallback(const String &message);
    
    void getClusterRegions(ClusterParameters* clusterParams, Array<float>* distanceArray, float* maxDistance,  Array<AudioRegion>* regions);
    
    bool isRegionWithinWidth(float regionFracWidth, ClusterParameters* clusterParams);
    
    int signum(float value);
    
    void invertClusterRegions(Array<AudioRegion>* regions);
    
    void findRegionsGridSearch(SearchParameters* searchParams, Array<float>* distanceArray, float* maxDistance, ClusterParameters* bestParams, Array<AudioRegion>* regions);
    
    void findRegionsBinarySearch(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams, Array<AudioRegion>* regions);
    
    void findRegionsGradientDescent(SearchParameters* searchParams, Array<float>* distanceArray, ClusterParameters* bestParams);
    
    float getRegionCost(Array<AudioRegion>* regions, SearchParameters* searchParams);
        
    bool saveRegionsToAudioFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile, bool useSingleFile);
    
    bool saveRegionsToTxtFile(Array<AudioRegion>* regions, SegaudioFile* sourceFile, File &destinationFile);
    
private:
    
    AudioFormatManager* formatManager;
    
    Eigen::MatrixXf refFeatureMat;
    Eigen::MatrixXf targetFeatureMat;

    int windowSize;
    
    float calculateBlockRMS(AudioSampleBuffer &block);
    
    float calculateZeroCrossRate(AudioSampleBuffer &block);
    
    float calculateSprectralFlux(Eigen::RowVectorXcf &blockFft);
    
    float calculateSpectralCentroid(Eigen::RowVectorXcf &blockFft);
    
    Eigen::RowVectorXf calculateMFCC(Eigen::RowVectorXcf &blockFft, int sampleRate);

    void run();

};



#endif  // AUDIOANALYSISCONTROLLER_H_INCLUDED
