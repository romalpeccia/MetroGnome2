/*
  ==============================================================================

    Utilities.h
    Created: 31 Oct 2024 2:37:21pm
    Author:  romal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace std;
using namespace juce;

const int MAX_LENGTH = 16;
const int PLUGIN_WIDTH = 800;
const int PLUGIN_HEIGHT = 800;
const int TIMER_INTERVAL = 60; 
const int BUTTON_SIZE = 30;
const juce::Colour MAIN_COLOUR = juce::Colours::mediumpurple;
const juce::Colour SECONDARY_COLOUR = juce::Colours::deepskyblue;
const juce::Colour BUTTON_COLOUR_1 = juce::Colours::orange;
const juce::Colour BUTTON_COLOUR_2 = juce::Colours::hotpink;
const juce::Colour COMPONENT_COLOUR_OFF = juce::Colours::dimgrey;
const juce::String PLAY_STRING = "PLAY";
const juce::String BPM_STRING = "BPM";
const juce::String SUBDIVISION_1_STRING = "SUBDIVISION_1";
const juce::String SUBDIVISION_2_STRING = "SUBDIVISION_2";
const juce::String CIRCLE_1_BEAT_STRING = "CIRCLE_1_BEAT_";
const juce::String CIRCLE_2_BEAT_STRING = "CIRCLE_2_BEAT_";

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
    public:
    
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style,
        Slider& slider) override
    {
        //g.fillRect(x, y, width, height); //for debugging
        auto trackWidth = jmin(6.0f,  (float)height * 0.25f);

        Point<float> startPoint( (float)x ,(float)y + (float)height * 0.5f );
        Point<float> endPoint((float)(width + x), startPoint.y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath(startPoint);
        backgroundTrack.lineTo(endPoint);
        g.setColour(slider.findColour(Slider::ColourIds::backgroundColourId));
        g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;
        auto kx = sliderPos;
        auto ky =  (float)y + (float)height * 0.5f;
        minPoint = startPoint;
        maxPoint = { kx, ky };
        valueTrack.startNewSubPath(minPoint);
        valueTrack.lineTo(maxPoint);
        g.setColour(slider.findColour(Slider::trackColourId));
        g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });
            
        auto thumbWidth = getSliderThumbRadius(slider);
        g.setColour(slider.findColour(Slider::ColourIds::thumbColourId));
        g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(maxPoint));

        g.setColour(slider.findColour(Slider::ColourIds::textBoxTextColourId));
        int fontHeight = height * 0.05f;
        g.setFont(fontHeight);
        g.drawText(slider.getName(), x, ky + fontHeight, width, fontHeight, juce::Justification::centredLeft);
    }

};

class CustomSlider : public juce::Slider {
    public:
        CustomSlider(juce::String sliderName) {
            setColour(juce::Slider::ColourIds::backgroundColourId, COMPONENT_COLOUR_OFF);
            setName(sliderName);
            setLookAndFeel(&lnf); 
        };
        CustomSlider(const juce::Colour mainColour, const juce::Colour secondaryColour, juce::String sliderName) {
            setColour(juce::Slider::ColourIds::textBoxOutlineColourId, mainColour);
            setColour(juce::Slider::ColourIds::textBoxTextColourId, secondaryColour.brighter(0.5f));
            setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, mainColour.darker(0.5f));
            setColour(juce::Slider::ColourIds::trackColourId, mainColour);
            setColour(juce::Slider::ColourIds::thumbColourId, secondaryColour);
            setColour(juce::Slider::ColourIds::backgroundColourId, COMPONENT_COLOUR_OFF);
            setName(sliderName);
            setLookAndFeel(&lnf);
        };
        ~CustomSlider() {
            setLookAndFeel(nullptr);
        };

    private:
        CustomLookAndFeel lnf;
};


class CustomTextButton : public juce::TextButton {
    public:
        CustomTextButton() {
            setLookAndFeel(&lnf);
        };
        CustomTextButton(const juce::String &buttonName, const juce::Colour buttonColour) {
            setLookAndFeel(&lnf);
            setColour(juce::TextButton::ColourIds::buttonOnColourId, buttonColour); 
            setColour(juce::TextButton::ColourIds::buttonColourId, COMPONENT_COLOUR_OFF);
            setButtonText(buttonName);
        };
        ~CustomTextButton(){
            setLookAndFeel(nullptr);
        };
        void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            lnf.drawButtonBackground(g, *this,
                findColour(getToggleState() ? juce::TextButton::ColourIds::buttonOnColourId : juce::TextButton::ColourIds::buttonColourId),
                shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
            lnf.drawButtonText(g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
        } 

    private:
        CustomLookAndFeel lnf;
};

