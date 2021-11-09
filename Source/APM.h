/*
  ==============================================================================

    APM.h
    Created: 04 Aug 2020
    Author:  Mattia Vassena

  ==============================================================================
*/

#pragma once

using namespace juce;

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class APM : public Component,
    public Thread,
    public ChangeBroadcaster
{
public:
    APM(PluginProcessor&);
    ~APM();
    void run();
    int BPM;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APM)
    PluginProcessor& processor;
};