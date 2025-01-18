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
const int TIMER_INTERVAL = 100; //TODO, choose a better value for this
const int BUTTON_SIZE = 30;
const juce::Colour MAIN_COLOUR = juce::Colours::rebeccapurple;
const juce::Colour SECONDARY_COLOUR = juce::Colours::steelblue;
const juce::Colour BUTTON_COLOUR_1 = juce::Colours::orange;
const juce::Colour BUTTON_COLOUR_2 = juce::Colours::mediumvioletred;
class CustomSliderLookNFeel : public juce::LookAndFeel_V4 {
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
            

            auto thumbWidth = getSliderThumbRadius(slider);

            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(maxPoint);
            g.setColour(slider.findColour(Slider::trackColourId));
            g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        
            g.setColour(slider.findColour(Slider::thumbColourId));
            g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre( maxPoint));
            
        
    }


};

class CustomSlider : public juce::Slider {
public:
    CustomSlider() {
        setLookAndFeel(&lnf);
    };
    ~CustomSlider() {
        setLookAndFeel(nullptr);
    };
private:
    CustomSliderLookNFeel lnf;
};

class CustomTextButton : public juce::TextButton {
    public:
        CustomTextButton() {};
        ~CustomTextButton() {};
    private:

};

