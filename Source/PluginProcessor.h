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

    std::atomic<float>* onOffParam;
    std::atomic<float>* subdivision1Param;
    std::atomic<float>* subdivision2Param;
    std::atomic<float>* bpmParam;
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    int beatCounter1 = 0;
    int beatCounter2 = 0;

    PolyRhythmMetronome metronome1, metronome2;

    void addAudioToBuffer(juce::AudioBuffer<float>& buffer, juce::AudioFormatReaderSource& sample, PolyRhythmMetronome metronome);
    std::unique_ptr <juce::AudioFormatReaderSource> drumHighSample = nullptr;
    std::unique_ptr <juce::AudioFormatReaderSource> drumLowSample = nullptr;
    std::unique_ptr <juce::AudioFormatReaderSource> drumSubSample = nullptr;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessor)
};
