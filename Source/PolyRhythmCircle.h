/*
  ==============================================================================

    PolyRhythmCircle.h
    Created: 23 Dec 2024 4:16:50pm
    Author:  romal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Utilities.h"

class BeatButton : public juce::TextButton {
public:
    BeatButton() {};
    ~BeatButton() {};
private:


};
class PolyRhythmCircle : public juce::Component {
    public:
        PolyRhythmCircle();
        PolyRhythmCircle(juce::AudioProcessorValueTreeState& _apvts, juce::String _id, int _handWidth, int _buttonSize, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour): apvts(_apvts), id(_id) {
            handWidth = _handWidth;
            buttonSize = _buttonSize;
            circleColour = _circleColour;
            handColour = _handColour;
            buttonColour = _buttonColour;
            for (int i = 0; i < MAX_LENGTH; i++) {
                beatButtonAttachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, _id + to_string(i), beatButtons[i]);
                beatButtons[i].setClickingTogglesState(true);
                addChildComponent(beatButtons[i]);
                beatButtons[i].setColour(juce::TextButton::ColourIds::buttonColourId, BUTTON_COLOUR_OFF);
                beatButtons[i].setColour(juce::TextButton::ColourIds::buttonOnColourId, buttonColour);
            }
        };
        ~PolyRhythmCircle(){};

        void paint(juce::Graphics & g) override;
        void resized() override;  
        void setNumSubdivisions(int num) {
            numSubdivisions = num;
            repaint();
        }
        void setHandAngle(int currentSubdivision) {
            handAngle = juce::degreesToRadians(360.f * (float(currentSubdivision) / float(numSubdivisions)) + 180.f);
            repaint();
        }

        juce::Colour circleColour;
        juce::Colour handColour;
        juce::Colour buttonColour;
        int numSubdivisions; // temporary value, should be set by slider
        int handWidth;
        float handAngle = juce::degreesToRadians(180.f);
        int buttonSize; // should be divisible by 2 to avoid rounding issues caused by decimals 

        juce::AudioProcessorValueTreeState& apvts;
        juce::String id;
        BeatButton beatButtons[MAX_LENGTH];
        std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> beatButtonAttachments[MAX_LENGTH]; //TODO: having the class depend on an external variable seems bad practice
};

