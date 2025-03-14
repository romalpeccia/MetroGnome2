/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PolyRhythmMetronome.h"
#include "Utilities.h"

//==============================================================================
/**
*/
class MetroGnome2AudioProcessor  : public juce::AudioProcessor,  juce::AudioProcessorValueTreeState::Listener, public juce::ActionBroadcaster
{
public:
    //==============================================================================
    MetroGnome2AudioProcessor();
    ~MetroGnome2AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

    std::atomic<float>* playParam;
    std::atomic<float>* subdivision1Param;
    std::atomic<float>* subdivision2Param;
    std::atomic<float>* bpmParam;
    std::atomic<float>* beatButtonParams1[MAX_LENGTH]; 
    std::atomic<float>* beatButtonParams2[MAX_LENGTH];

    void parameterChanged(const juce::String& parameterID, float newValue) override;

    PolyRhythmMetronome metronome1, metronome2;
    //cache the subdivisionCounters from the metronomes so we can keep track of when they change
    int subdivisionCounter1 = 0; 
    int subdivisionCounter2 = 0;

    void addAudioToBuffer(juce::AudioBuffer<float>& buffer, juce::AudioFormatReaderSource& sample, PolyRhythmMetronome metronome);
    std::unique_ptr <juce::AudioFormatReaderSource> drumHighSample = nullptr;
    std::unique_ptr <juce::AudioFormatReaderSource> drumMidSample = nullptr;
    std::unique_ptr <juce::AudioFormatReaderSource> drumLowSample = nullptr;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessor)
};
