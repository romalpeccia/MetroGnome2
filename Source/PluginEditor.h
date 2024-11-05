/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utilities.h"

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
    MetroGnome2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessorEditor)
};
