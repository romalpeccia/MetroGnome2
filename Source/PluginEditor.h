/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utilities.h"
#include "PolyRhythmCircle.h"
//==============================================================================
/**
*/
class MetroGnome2AudioProcessorEditor : public juce::AudioProcessorEditor, juce::Slider::Listener
{
public:
    MetroGnome2AudioProcessorEditor(MetroGnome2AudioProcessor&, juce::AudioProcessorValueTreeState &);
    ~MetroGnome2AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *) override;

    std::vector<juce::Component*> getVisibleComps();



private:
    MetroGnome2AudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& apvts;

    CustomSlider bpmSlider, subdivision1Slider, subdivision2Slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bpmAttachment, subdivision1Attachment, subdivision2Attachment;

    PolyRhythmCircle prc;

    //CustomTextButton playButton;
    //juce::AudioProcessorValueTreeState::ButtonAttachment playAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessorEditor)
};
