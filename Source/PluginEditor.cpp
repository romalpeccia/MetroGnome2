/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetroGnome2AudioProcessorEditor::MetroGnome2AudioProcessorEditor (MetroGnome2AudioProcessor& p, juce::AudioProcessorValueTreeState& _apvts)
    : AudioProcessorEditor (&p), audioProcessor (p), apvts(_apvts)
{


    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "BPM", bpmSlider);
    subdivision1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUBDIVISION_1", subdivision1Slider);
    subdivision2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUBDIVISION_2", subdivision2Slider);
    subdivision1Slider.addListener(this);
    subdivision2Slider.addListener(this);

    for (auto* comp : getVisibleComps())
    {
        addAndMakeVisible(comp);
    }

    setResizable(true, true);
    setSize (PLUGIN_WIDTH, PLUGIN_HEIGHT);
}

MetroGnome2AudioProcessorEditor::~MetroGnome2AudioProcessorEditor()
{
}

//==============================================================================
void MetroGnome2AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void MetroGnome2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int margin = 5;
    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<int> topBounds = bounds.withTrimmedBottom(bounds.getHeight() * 0.33 + margin); //TODO add top margin
    juce::Rectangle<int> bottomBounds = bounds.withTrimmedTop(bounds.getHeight() * 0.66 + margin);
    juce::Rectangle<int> bottomLeftBounds = bottomBounds.withTrimmedRight(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomRightBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomMiddleBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.33 + margin).withTrimmedRight(bounds.getWidth() * 0.33 + margin);

    prc.setBounds(topBounds);
    bpmSlider.setBounds(bottomRightBounds);
    subdivision1Slider.setBounds(bottomMiddleBounds);
    subdivision2Slider.setBounds(bottomLeftBounds);
}

std::vector<juce::Component*> MetroGnome2AudioProcessorEditor::getVisibleComps() {
    //returns a vector of juce visible components, for easy access such as altering all components

    std::vector<juce::Component*> comps;

    comps.push_back(&bpmSlider);
    comps.push_back(&subdivision1Slider);
    comps.push_back(&subdivision2Slider);
    comps.push_back(&prc);
    return comps;
}

void MetroGnome2AudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {

    //TODO: update polyrhythmcircle class when slider changes
    if (slider = &subdivision1Slider) {
        prc.setNumSubdivisions(subdivision1Slider.getValue());

    }
    else if (slider = &subdivision2Slider) {


    }
    DBG("slider changed");
}