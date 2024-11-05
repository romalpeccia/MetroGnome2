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
class MetroGnome2AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MetroGnome2AudioProcessorEditor(MetroGnome2AudioProcessor&);
    ~MetroGnome2AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


    std::vector<juce::Component*> getVisibleComps();


    CustomSlider bpmSlider, subdivision1Slider, subdivision2Slider;
    //juce::AudioProcessorValueTreeState::SliderAttachment bpmAttachment;// , subdivision1Attachment, subdivision2Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bpmAttachment, subdivision1Attachment, subdivision2Attachment;
private:
    MetroGnome2AudioProcessor& audioProcessor;


    //CustomTextButton playButton;


    //juce::AudioProcessorValueTreeState::ButtonAttachment playAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessorEditor)
};
