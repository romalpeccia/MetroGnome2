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
    prc1.setNumSubdivisions(apvts.getRawParameterValue("SUBDIVISION_1")->load()); // TODO load the audioprocessor param?
    prc2.setNumSubdivisions(apvts.getRawParameterValue("SUBDIVISION_2")->load()); // TODO load the audioprocessor param?
    setResizable(true, true);
    setSize (PLUGIN_WIDTH, PLUGIN_HEIGHT);
    startTimer(TIMER_INTERVAL);
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
    juce::Rectangle<int> topBounds = bounds.withTrimmedBottom(bounds.getHeight() * 0.33 + margin).withTrimmedTop(margin);
    juce::Rectangle<int> bottomBounds = bounds.withTrimmedTop(bounds.getHeight() * 0.66 + margin);
    juce::Rectangle<int> bottomLeftBounds = bottomBounds.withTrimmedRight(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomRightBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomMiddleBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.33 + margin).withTrimmedRight(bounds.getWidth() * 0.33 + margin);
    float prc1SizeFactor = 0.15;
    juce::Rectangle<int> prc1Bounds = topBounds.withTrimmedLeft(bounds.getWidth() * prc1SizeFactor + margin).withTrimmedRight(bounds.getWidth() * prc1SizeFactor + margin);
    prc1.setBounds(prc1Bounds);
    float prc2SizeFactor = 0.90;
    int prc2Width = prc1Bounds.getWidth() * prc2SizeFactor / 2;
    int prc2Height = prc1Bounds.getHeight() * prc2SizeFactor / 2;
    juce::Rectangle<int> prc2Bounds(prc1Bounds.getCentreX() - prc2Width/2 - margin - 3, prc1Bounds.getCentreY() - prc2Height/2, prc2Width, prc2Height ); //TODO this is sus
    prc2.setBounds(prc2Bounds);
    bpmSlider.setBounds(bottomLeftBounds);
    subdivision1Slider.setBounds(bottomMiddleBounds);
    subdivision2Slider.setBounds(bottomRightBounds);
}

std::vector<juce::Component*> MetroGnome2AudioProcessorEditor::getVisibleComps() {
    //returns a vector of juce visible components, for easy access such as altering all components
    std::vector<juce::Component*> comps;

    comps.push_back(&bpmSlider);
    comps.push_back(&subdivision1Slider);
    comps.push_back(&subdivision2Slider);
    comps.push_back(&prc1);
    comps.push_back(&prc2);
    return comps;
}

void MetroGnome2AudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {

    if (slider = &subdivision1Slider) {
        prc1.setNumSubdivisions(subdivision1Slider.getValue());
    }
    if (slider = &subdivision2Slider) {

        DBG("slider changed");
        prc2.setNumSubdivisions(subdivision2Slider.getValue());
    }
  
}

void MetroGnome2AudioProcessorEditor::timerCallback() {
    prc1.setHandAngle(audioProcessor.metronome1.beatCounter);
    prc2.setHandAngle(audioProcessor.metronome2.beatCounter);
}