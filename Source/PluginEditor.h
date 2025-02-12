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
class MetroGnome2AudioProcessorEditor : public juce::AudioProcessorEditor, juce::Slider::Listener, /*juce::Timer,*/ juce::ActionListener
{
public:
    MetroGnome2AudioProcessorEditor(MetroGnome2AudioProcessor&, juce::AudioProcessorValueTreeState &); 
    ~MetroGnome2AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *) override;

    //void timerCallback() override;

    std::vector<juce::Component*> getVisibleComps();
    void actionListenerCallback(const juce::String&) override;


private:
    MetroGnome2AudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& apvts;

    CustomSlider bpmSlider, subdivision1Slider{ MAIN_COLOUR, BUTTON_COLOUR_1 }, subdivision2Slider{ SECONDARY_COLOUR, BUTTON_COLOUR_2 };
    juce::Label bpmLabel{ "bpmSlider" , "BPM"}, subdivision1Label{"subdivision1Slider", "Outer Subdivisions"}, subdivision2Label{"subdivision2Slider", "Inner Subdivisions"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bpmAttachment, subdivision1Attachment, subdivision2Attachment;

    PolyRhythmCircle prc1{apvts, "CIRCLE_1_BEAT_", 4, BUTTON_SIZE, MAIN_COLOUR, SECONDARY_COLOUR , BUTTON_COLOUR_1}; 
    PolyRhythmCircle prc2{ apvts, "CIRCLE_2_BEAT_", 4, BUTTON_SIZE/2, SECONDARY_COLOUR, MAIN_COLOUR, BUTTON_COLOUR_2 };
    CustomTextButton playButton{ "PLAY", MAIN_COLOUR };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> playAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetroGnome2AudioProcessorEditor)
};
