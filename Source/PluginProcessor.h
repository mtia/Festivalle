/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#define ds 16 // downsampling
#define bs 2400 // fs/ds/fmin -> 48000/ds/1.25 (75 bpm)
#define nbuff 4 // number of buffers of bs samples to analyze in APM.cpp
using namespace juce;

//==============================================================================
/**
*/
class PluginProcessor : public AudioProcessor,
	public ChangeBroadcaster
{
public:
	//==============================================================================
	PluginProcessor();
	~PluginProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	//==============================================================================
	double setThreshold(double value);
    
    void setThreadBoolean(bool setup);
	int prova = 10;

	enum
	{
		fftOrder = 10,           // [1]
		fftSize = 1 << fftOrder  // [2]
	};

	void pushNextSampleIntoFifo(float sample, int channel) noexcept;

	/*float* getFFTData();
	float getFFTDataIndex(int index);*/

	bool getNextFFTBlockReady();
	void setNextFFTBlockReady(bool setup);
	bool getNextAPMBlockReady();
	void setNextAPMBlockReady(bool setup);

	int numSample = 0;

	float fifoL[fftSize];           // [4]
	float fifoR[fftSize];
	int fifoIndexL = 0;              // [6]
	int fifoIndexR = 0;
	float fftDataL[fftSize*2];    // [5]
	float fftDataR[fftSize*2];

	int APMfifoIndexL = 0;
	int APMfifoIndexR = 0;
	
	int APMbuffsize = bs;
	float fifoAPML[bs*nbuff];
	float fifoAPMR[bs*nbuff];
	float fifoBuffL[bs*nbuff];
	float fifoBuffR[bs*nbuff];
    
private:
	double rawVolume = 1;
	double threshold;
	int count = 0;

	bool nextFFTBlockReady = false; // [7]
	bool nextAPMBlockReady = false;

    float leftChannel[1024];
    float rightChannel[1024];
    float totChannel[1024];
    
    bool threadFlag=true;
    
//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
