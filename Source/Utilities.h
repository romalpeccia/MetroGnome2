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
//const int TIMER_INTERVAL = 100; //TODO, choose a better value for this
const int BUTTON_SIZE = 30;
const juce::Colour MAIN_COLOUR = juce::Colours::mediumpurple;
const juce::Colour SECONDARY_COLOUR = juce::Colours::deepskyblue;
const juce::Colour BUTTON_COLOUR_1 = juce::Colours::orange;
const juce::Colour BUTTON_COLOUR_2 = juce::Colours::hotpink;
const juce::Colour COMPONENT_COLOUR_OFF = juce::Colours::dimgrey;

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
    public:
    
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style,
        Slider& slider) override
    {
        //TODO: add label, remove ishorizontal calls?
            auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

            Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));
            Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                slider.isHorizontal() ? startPoint.y : (float)y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;
            auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;
            minPoint = startPoint;
            maxPoint = { kx, ky };
            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(maxPoint);
            g.setColour(slider.findColour(Slider::trackColourId));
            g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });
            
            auto thumbWidth = getSliderThumbRadius(slider);
            g.setColour(slider.findColour(Slider::thumbColourId));
            g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre( maxPoint));
    }


    void drawButtonText(Graphics& g, TextButton& button,
        bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/) override
    {
        Font font(getTextButtonFont(button, button.getHeight()));
        g.setFont(font);
        g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
            : TextButton::textColourOffId)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        const int yIndent = jmin(4, button.proportionOfHeight(0.3f));
        const int cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;

        const int fontHeight = roundToInt(font.getHeight() * 0.6f);
        const int leftIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        const int rightIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        const int textWidth = button.getWidth() - leftIndent - rightIndent;

        if (textWidth > 0)
            g.drawFittedText(button.getButtonText(),
                leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                Justification::centred, 2);
    }

};

class CustomSlider : public juce::Slider {
    public:
        CustomSlider() {
            setColour(juce::Slider::ColourIds::backgroundColourId, COMPONENT_COLOUR_OFF);
            setLookAndFeel(&lnf); 
        };
        CustomSlider(const juce::Colour mainColour, const juce::Colour secondaryColour) {
            setColour(juce::Slider::ColourIds::textBoxOutlineColourId, mainColour);
            setColour(juce::Slider::ColourIds::textBoxTextColourId, secondaryColour.brighter(0.5f));
            setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, mainColour.darker(0.5f));
            setColour(juce::Slider::ColourIds::trackColourId, mainColour);
            setColour(juce::Slider::ColourIds::thumbColourId, secondaryColour);
            setColour(juce::Slider::ColourIds::backgroundColourId, COMPONENT_COLOUR_OFF);
            setLookAndFeel(&lnf);
        };
        ~CustomSlider() {
            setLookAndFeel(nullptr);
        };
    private:
        CustomLookAndFeel lnf;
        //juce::Label label;

        //override resized function?
        //or do something within LNF
        //or lazy approach - just declare labels in the editor?
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
                findColour(getToggleState() ? buttonOnColourId : buttonColourId),
                shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
            lnf.drawButtonText(g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
        } 

    private:
        CustomLookAndFeel lnf;
};

