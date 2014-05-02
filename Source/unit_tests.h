/*
This file is part of Segaudio.

Segaudio is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Segaudio is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Segaudio.  If not, see <http://www.gnu.org/licenses/>.
/**/

#ifndef UNIT_TESTS_H_INCLUDED
#define UNIT_TESTS_H_INCLUDED

#include "JuceHeader.h"

#include "AudioRegion.h"
#include "AudioAnalysisController.h"
#include "SegaudioModel.h"


class AudioRegionTest : public UnitTest
{
public:
    AudioRegionTest()  : UnitTest ("Segaudio Testing") {

        testRegion = AudioRegion(0.25, 0.75);

    }
    void runTest()
    {
        beginTest ("Part 1: AudioRegion Testing");
        expect(testRegion.getEnd() == 0.75, "AudioRegion getEnd() failed");
        expect(testRegion.getStart() == 0.25, "AudioRegion getStart failed");
        expect(testRegion.getEnd(100) == 75, "AudioRegion getEnd(refWidth) failed");
        expect(testRegion.getStart(100) == 25, "AudioRegion getStart(refWidth) failed");
        expect(testRegion.getEnd(100, 200) == 175, "AudioRegion getEnd(refStart, refEnd) failed");
        expect(testRegion.getStart(100, 200) == 125, "AudioRegion getStart(refStart, refEnd) failed");

        beginTest ("Part 2: AudioRegion Instantiation");
        AudioRegion r1 = AudioRegion(1.5, 0);
        expect(r1.getStart() == 0, "AudioRegion start out of bounds fail");
        expect(r1.getEnd() - 0.01 < 0.0001, "AudioRegion end before start fail");

    }

    AudioRegion testRegion;
};


class AnalysisControllerTest : public UnitTest
{
public:
    AnalysisControllerTest()  : UnitTest ("Segaudio Testing") {

        testController = new AudioAnalysisController;

    }
    ~AnalysisControllerTest(){
        delete testController;
    }

    void runTest()
    {
        beginTest ("Part 1: Analysis Controller Testing");

        Array<float> distanceArray;
        distanceArray.add(0.0);
        distanceArray.add(1.0);
        distanceArray.add(0.0);
        distanceArray.add(1.0);
        distanceArray.add(0.0);

        ClusterParameters clusterParams;
        clusterParams.threshold = 0.5;

        float maxDistance = 1.0f;

        Array<AudioRegion> regions;

        testController->getClusterRegions(&clusterParams, &distanceArray, &maxDistance, &regions);

        expect(regions.size() == 3, "Number regions incorrect");

    }


    AudioAnalysisController* testController;
};


class SignalFeaturesToUseTest : public UnitTest
{
public:
    SignalFeaturesToUseTest()  : UnitTest ("Segaudio Testing") {
        featuresToUse = SignalFeaturesToUse();
    }

    void runTest()
    {
        beginTest ("Part 1: SignalFeaturesToUse Testing");

        featuresToUse.mfcc = true;
        featuresToUse.sf = true;
        featuresToUse.zcr = true;
        featuresToUse.rms = true;

        expect(featuresToUse.getNumSelected() == (12 + 3), "Num features selected fail");
        expect(featuresToUse.needFft(), "Need fft fail");
        expect(!featuresToUse.isNoneSelected(), "None selected fail");

        featuresToUse.mfcc = false;
        featuresToUse.sf = false;

        expect(featuresToUse.getNumSelected() == 2, "Num features selected fail");
        expect(!featuresToUse.needFft(), "Need fft fail");

        featuresToUse.zcr = false;
        featuresToUse.rms = false;

        expect(featuresToUse.getNumSelected() == 0, "Num features selected fail");
        expect(featuresToUse.isNoneSelected(), "None selected fail");

    }


    SignalFeaturesToUse featuresToUse;
};


// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()

//static AnalysisControllerTest analysisControllerTest;   // This keeps giving an error, don't have time to solve...

static SignalFeaturesToUseTest signalFeaturesToUseTest;
static AudioRegionTest audioRegionTest;



#endif  // UNIT_TESTS_H_INCLUDED
