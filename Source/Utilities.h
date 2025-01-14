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
        ~CustomSlider() {};
    private:

};

class CustomTextButton : public juce::TextButton {
public:
    CustomTextButton() {};
    ~CustomTextButton() {};
private:

};


class ParameterChangeListener : public juce::AudioProcessorValueTreeState::Listener
{
public:

    ParameterChangeListener();
    ~ParameterChangeListener() {}

    // This function is called whenever a parameter changes
    void parameterChanged(const juce::String& parameterID, float newValue) override
    {

        //if (param 1, param 2, etc)


        DBG("Parameter " << parameterID << " has changed to " << newValue);

    }
};