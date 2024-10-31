/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MetroGnome2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MetroGnome2AudioProcessorEditor (MetroGnome2AudioProcessor&);
    ~MetroGnome2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MetroGnome2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessorEditor)
};
