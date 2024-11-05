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

const int MAX_LENGTH = 16;
const int PLUGIN_HEIGHT = 800;
const int PLUGIN_WIDTH = 800;

class CustomSlider : public juce::Slider {
    public:
        CustomSlider() {};
        CustomSlider(juce::RangedAudioParameter& rap) {};
        ~CustomSlider() {};
    private:

};

class CustomTextButton : public juce::TextButton {
public:
    CustomTextButton() {};
    CustomTextButton(juce::AudioParameterBool& apb) {};
    ~CustomTextButton() {};
private:

};