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
class PolyRhythmCircle : public juce::Component, public juce::Button::Listener { 
    public:
        PolyRhythmCircle();
        PolyRhythmCircle(juce::AudioProcessorValueTreeState& _apvts, juce::String _id, int _handWidth, int _buttonSize, bool _drawPolygons, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour);
        ~PolyRhythmCircle(){};
        void paint(juce::Graphics & g) override;
        void resized() override {};

        void buttonClicked(juce::Button* b) override { //for debugging
        };

        void mouseDown(const juce::MouseEvent& e) override { //for debugging
        };

        void setNumSubdivisions(int num);
        int getNumSubdivisions();
        void setHandAngleBySubdivision(int currentSubdivision);
        void setHandAngleByFraction(float cycleFraction);
        void setHandAngle(float angle);
        void setButtonSize(int _buttonSize);
        void setHandWidth(int _handWidth);
        void setDrawAsPolygons(bool _drawAsPolygons);

        enum class ColourIds {
            //for choosing which Colour variable to access, tried to follow JUCE convention
            CircleColourId,
            HandColourId,
            ButtonColourId
        };

        void setColour(PolyRhythmCircle::ColourIds id, juce::Colour colour);

        private:
        juce::AudioProcessorValueTreeState& apvts;
        juce::String id;// string associated with the apvts parameters for the beatButtons
        BeatButton beatButtons[MAX_LENGTH];
        std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> beatButtonAttachments[MAX_LENGTH];
       
        bool drawAsPolygons = true;
        int numSubdivisions = 4;
        int handWidth = 2; //should be divisible by 2 to avoid rounding issues caused by decimals 
        float handAngle = juce::degreesToRadians(180.f);
        int buttonSize = 4; //length/width of the buttons, should be divisible by 2 to avoid rounding issues caused by decimals 
        juce::Colour circleColour;
        juce::Colour handColour;
        juce::Colour buttonColour;
};