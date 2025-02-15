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
    //note: think about how much i should be abstracting things as much as possible, for example UI being as independant as possible from the processor, so that things can in one class can be swapped in and out without causing problems for
    //other class implementations, think about MVC, think about classes having single responsibilities
    //for example a loader interface for the audio filess, where the interface abstractly expects some input and there can be multiple different classes that go into that interface that are
    // able to load files in different ways (liskovs principle)
    
    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "BPM", bpmSlider);
    subdivision1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUBDIVISION_1", subdivision1Slider);
    subdivision2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUBDIVISION_2", subdivision2Slider);
    subdivision1Slider.addListener(this);
    subdivision2Slider.addListener(this);

    playAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "PLAY", playButton);
    playButton.setClickingTogglesState(true);
    //playButton.addListener(this); //TODO: why doesn't this work? janky fix: just check PLAY in processor
      
    
    //TODO delete these label colourings and initialization of the labels, do it in slider class somehow? 
    bpmLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    bpmLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    subdivision1Label.setColour(juce::Label::ColourIds::textColourId, MAIN_COLOUR);
    subdivision1Label.setFont(juce::Font(16.0f, juce::Font::bold));
    subdivision2Label.setColour(juce::Label::ColourIds::textColourId, SECONDARY_COLOUR);
    subdivision2Label.setFont(juce::Font(16.0f, juce::Font::bold));

    for (auto* comp : getVisibleComps())
    {
        addAndMakeVisible(comp);
    }

    prc1.setNumSubdivisions(*audioProcessor.subdivision1Param);
    prc2.setNumSubdivisions(*audioProcessor.subdivision2Param); 
    audioProcessor.addActionListener(this);
    setResizable(true, true);
    setSize (PLUGIN_WIDTH, PLUGIN_HEIGHT);
    //startTimer(TIMER_INTERVAL);
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
    float prc2SizeFactor = 0.3;
    prc1.setBounds(prc1Bounds); 
    prc2.setBounds(prc1Bounds.reduced(prc1Bounds.getWidth()*prc2SizeFactor / 2)); 
    bpmSlider.setBounds(bottomLeftBounds);
    subdivision1Slider.setBounds(bottomMiddleBounds);
    subdivision2Slider.setBounds(bottomRightBounds);

    //TODO; put these in slider 
    bpmLabel.setBounds(bottomLeftBounds.withTrimmedTop(bottomLeftBounds.getHeight() * 0.5));
    subdivision1Label.setBounds(bottomMiddleBounds.withTrimmedTop(bottomMiddleBounds.getHeight() * 0.5));
    subdivision2Label.setBounds(bottomRightBounds.withTrimmedTop(bottomRightBounds.getHeight() * 0.5));

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
    comps.push_back(&bpmLabel);
    comps.push_back(&subdivision1Label);
    comps.push_back(&subdivision2Label);

    return comps;
}

void MetroGnome2AudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    //called when a slider value changes and adjusts the UI accordingly
    if (slider = &subdivision1Slider) {
        prc1.setNumSubdivisions(subdivision1Slider.getValue());
    }
    if (slider = &subdivision2Slider) {
        prc2.setNumSubdivisions(subdivision2Slider.getValue());
    }
  
}

/*
void MetroGnome2AudioProcessorEditor::timerCallback() {
    prc1.setHandAngle(audioProcessor.metronome1.beatCounter);
    prc2.setHandAngle(audioProcessor.metronome2.beatCounter);
}
*/
void MetroGnome2AudioProcessorEditor::actionListenerCallback(const juce::String& message) {
    //called when a the audioprocessor calls sendActionMessage
    if (message == "beatCounter1") {
       prc1.setHandAngle(audioProcessor.metronome1.beatCounter);
   }
    if (message == "beatCounter2") {
       prc2.setHandAngle(audioProcessor.metronome2.beatCounter);
    }
}