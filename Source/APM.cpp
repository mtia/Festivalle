/*
  ==============================================================================

    APM.cpp
    Created: 04 Aug 2020
    Author:  Mattia Vassena

  ==============================================================================
*/



#include "../JuceLibraryCode/JuceHeader.h"
#include "APM.h"
#include "PluginProcessor.h"

//using namespace juce;

//==============================================================================
APM::APM(PluginProcessor& p)
    :Thread("APMThread"), processor(p)
{
    

}

APM::~APM()
{

}

void APM::run()
{
    if (processor.getNextAPMBlockReady())
    {
        float P[bs/2];
        float C[bs/2];
        zeromem(P, sizeof(P));
        zeromem(C, sizeof(C));
        int minlag = bs/2; // shift dx term for autocorrelation lags

        for (auto i = 0; i < (nbuff-1)*bs; i++) {
            for (auto j = 0; j < minlag; j++) { // only compute desired band in BPM
                // autocorrelation array
                P[j] = P[j] +
                    (processor.fifoBuffL[i] + processor.fifoBuffR[i])
                    * (processor.fifoBuffL[i + j + minlag] + processor.fifoBuffR[i + j + minlag]);
                // counter matrix for unbiasing
                C[j] = C[j] + 1;
            }
        }

        int maxj = 0; // to avoid zero division at BPM calculus

        for (auto j = 0; j < minlag; j++) {
            P[j] = P[j] / C[j];                             // unbiased autocorrelation lags
            if (P[j] > P[maxj])
                maxj = j;                                   // lag with max energy
        }

        BPM = (60 * (int)processor.getSampleRate() / ((maxj + minlag) * ds)); // shift dx with minlag
        

        processor.setNextAPMBlockReady(false);
    }
}
