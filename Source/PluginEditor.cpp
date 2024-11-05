/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetroGnome2AudioProcessorEditor::MetroGnome2AudioProcessorEditor (MetroGnome2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
    

    //NOTE: how to initialize parameters "properly"??
    //bpmSlider(*audioProcessor.apvts.getParameter("BPM")),
//subdivision1Slider(*audioProcessor.apvts.getParameter("SUBDIVISION_1")),
   // subdivision2Slider(*audioProcessor.apvts.getParameter("SUBDIVISION_2")),
    
    //bpmAttachment(audioProcessor.apvts, "BPM", bpmSlider)
    //subdivision1Attachment(audioProcessor.apvts, "SUBDIVISION_1", subdivision1Slider),
   // subdivision2Attachment(audioProcessor.apvts, "SUBDIVISION_2", subdivision2Slider)


{
    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "BPM", bpmSlider);
    subdivision1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUBDIVISION_1", subdivision1Slider);
    subdivision2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUBDIVISION_2", subdivision2Slider);
    
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
    juce::Rectangle<int> topBounds = bounds.withTrimmedBottom(bounds.getHeight() * 0.33 + margin);
    juce::Rectangle<int> bottomBounds = bounds.withTrimmedTop(bounds.getHeight() * 0.66 + margin);
    juce::Rectangle<int> bottomLeftBounds = bottomBounds.withTrimmedRight(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomRightBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomMiddleBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.33 + margin).withTrimmedRight(bounds.getWidth() * 0.33 + margin);

    bpmSlider.setBounds(bottomMiddleBounds);
    subdivision1Slider.setBounds(bottomRightBounds);
    subdivision2Slider.setBounds(bottomLeftBounds);
}

std::vector<juce::Component*> MetroGnome2AudioProcessorEditor::getVisibleComps() {
    //returns a vector of juce visible components, for easy access such as altering all components

    std::vector<juce::Component*> comps;

    comps.push_back(&bpmSlider);
    comps.push_back(&subdivision1Slider);
    comps.push_back(&subdivision2Slider);

    return comps;
}