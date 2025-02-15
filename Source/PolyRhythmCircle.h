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
class PolyRhythmCircle : public juce::Component, public juce::Button::Listener { //TODO: remove external constants like COMPONENT_COLOUR_OFF or MAX_LENGTH?, set them in constructor? or is that overkill? I have this in other classes too
    public:
        PolyRhythmCircle();
        PolyRhythmCircle(juce::AudioProcessorValueTreeState& _apvts, juce::String _id, int _handWidth, int _buttonSize, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour): apvts(_apvts), id(_id) { //TODO: move this to cpp ?
            handWidth = _handWidth;
            setButtonSize(_buttonSize);
            circleColour = _circleColour;
            handColour = _handColour;
            buttonColour = _buttonColour;
            for (int i = 0; i < MAX_LENGTH; i++) {
                beatButtonAttachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, _id + to_string(i), beatButtons[i]);
                beatButtons[i].setClickingTogglesState(true);
                addChildComponent(beatButtons[i]);
                beatButtons[i].setColour(juce::TextButton::ColourIds::buttonColourId, COMPONENT_COLOUR_OFF);
                beatButtons[i].setColour(juce::TextButton::ColourIds::buttonOnColourId, buttonColour);
                beatButtons[i].addListener(this);
            }
        };
        ~PolyRhythmCircle(){};


        void buttonClicked(juce::Button* b) override{ //for debugging
        };

        void mouseDown(const juce::MouseEvent& e) override { //for debugging
        };

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
        void setButtonSize(int _buttonSize) {
            //to prevent errors caused by rounding issues
            if (_buttonSize % 2 != 0) {
                _buttonSize += 1;
            }
            buttonSize = _buttonSize;
        };

        juce::Colour circleColour;
        juce::Colour handColour;
        juce::Colour buttonColour;

        int numSubdivisions = 4; 
        int handWidth;
        float handAngle = juce::degreesToRadians(180.f);
        int buttonSize = 4; //length/width of the buttons, should be divisible by 2 to avoid rounding issues caused by decimals 

        juce::AudioProcessorValueTreeState& apvts;
        juce::String id;// string associated with the apvts parameters for the beatButtons
        BeatButton beatButtons[MAX_LENGTH];
        std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> beatButtonAttachments[MAX_LENGTH];
};

