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
    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, BPM_STRING, bpmSlider);
    subdivision1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, SUBDIVISION_1_STRING, subdivision1Slider);
    subdivision2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, SUBDIVISION_2_STRING, subdivision2Slider);
    subdivision1Slider.addListener(this);
    subdivision2Slider.addListener(this);

    playAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, PLAY_STRING, playButton);
    playButton.setClickingTogglesState(true);
      
    for (auto* comp : getVisibleComps())
    {
        addAndMakeVisible(comp);
    }

    prc1.setNumSubdivisions(*audioProcessor.subdivision1Param);
    prc2.setNumSubdivisions(*audioProcessor.subdivision2Param);
    audioProcessor.addActionListener(this);
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
    //layout the top 2/3rds of the UI to contain the PolyRhythmCircles, and split the bottom 1/3rd of the UI into 1/3rds, for the 3 sliders
    int margin = 5;
    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<int> topBounds = bounds.withTrimmedBottom(bounds.getHeight() * 0.33 + margin).withTrimmedTop(margin);
    juce::Rectangle<int> bottomBounds = bounds.withTrimmedTop(bounds.getHeight() * 0.66 + margin);
    juce::Rectangle<int> bottomLeftBounds = bottomBounds.withTrimmedRight(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomRightBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.66 + margin);
    juce::Rectangle<int> bottomMiddleBounds = bottomBounds.withTrimmedLeft(bounds.getWidth() * 0.33 + margin).withTrimmedRight(bounds.getWidth() * 0.33 + margin);

    //set the bounds of the PolyRhythmCircles
    float prc1SizeFactor = 0.15;
    juce::Rectangle<int> prc1Bounds = topBounds.withTrimmedLeft(bounds.getWidth() * prc1SizeFactor + margin).withTrimmedRight(bounds.getWidth() * prc1SizeFactor + margin);
    float prc2SizeFactor = 0.3;
    prc1.setBounds(prc1Bounds); 
    prc2.setBounds(prc1Bounds.reduced(prc1Bounds.getWidth()*prc2SizeFactor / 2)); 

    //set the bounds of the controls
    bpmSlider.setBounds(bottomLeftBounds);
    subdivision1Slider.setBounds(bottomMiddleBounds);
    subdivision2Slider.setBounds(bottomRightBounds);
    playButton.setBounds(topBounds.withTrimmedBottom(topBounds.getHeight() * 0.9).withTrimmedRight(topBounds.getWidth() * 0.9));
}

std::vector<juce::Component*> MetroGnome2AudioProcessorEditor::getVisibleComps() {
    //returns a vector of juce visible components, for easy access such as altering all components
    std::vector<juce::Component*> comps;

    comps.push_back(&playButton);
    comps.push_back(&bpmSlider);
    comps.push_back(&subdivision1Slider);
    comps.push_back(&subdivision2Slider);
    comps.push_back(&prc1);
    comps.push_back(&prc2);

    return comps;
}

void MetroGnome2AudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    //called when a slider value changes and adjusts the UI accordingly
    if (slider == &subdivision1Slider) {
        prc1.setNumSubdivisions(subdivision1Slider.getValue());
    }
    if (slider == &subdivision2Slider) {
        prc2.setNumSubdivisions(subdivision2Slider.getValue());
    }
}

void MetroGnome2AudioProcessorEditor::actionListenerCallback(const juce::String& message) {
    //called when a the audioprocessor calls sendActionMessage
    
    if (message == "subdivisionCounter1") {
       prc1.setHandAngleBySubdivision(audioProcessor.metronome1.getSubdivisionCounter());
   }
    if (message == "subdivisionCounter2") {
       prc2.setHandAngleBySubdivision(audioProcessor.metronome2.getSubdivisionCounter());
    }
}