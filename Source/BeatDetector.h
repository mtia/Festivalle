/*
  ==============================================================================

    BeatDetector.h
    Created: 28 May 2019 10:57:10pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace juce;
//==============================================================================
/*
*/
class BeatDetector    : public Component,
                        public Thread,
                        public ChangeBroadcaster
{
public:
    BeatDetector(PluginProcessor&);
    ~BeatDetector();

    void paint (Graphics&) override;
    void resized() override;
    void run();

    
    //=============================
    //BPM DETECTION METHODS
    void beatDetection();
    float averageQueue(std::queue<std::vector<float>> temporalQueue, int index);
    float performEnergyFFT(int index);
    void thresholdCalculus();
    float varianceEnergyHistory(float average, std::queue<std::vector<float>> tempQueue, int index);
    //=============================
    
    int beatTime = 0; 

	bool beforeTransient = false;
	bool transient = false;
	bool reducedTransient = false; //per la velocity
	double transientStartTime = 0;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatDetector)
    
    PluginProcessor& processor;
    
    int dim = round(processor.getSampleRate() / PluginProcessor::fftSize);
    
    
    int oldCount=0;
    int energyIndex = 0;
    
    std::queue<std::vector<float>> energyHistory;
    
    std::priority_queue<float> bpmQueue;
    
    
    float BPMthreshold[2];
    
    double timeAverage = 0; //manual mode
    
    int kickmin = 0;
    int kickmax = 0;
    int snaremin = 0;
    int snaremax = 0;
    int bandKick = 0;
    int bandSnare = 0;
    
};
