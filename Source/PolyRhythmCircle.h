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
    //TODO: remove external constants like COMPONENT_COLOUR_OFF or MAX_LENGTH?, set them in constructor? or is that overkill? the constructor is already huge I have this in other classes too
    public:
        PolyRhythmCircle();
        PolyRhythmCircle(juce::AudioProcessorValueTreeState& _apvts, juce::String _id, int _handWidth, int _buttonSize, bool _drawPolygons, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour);
        ~PolyRhythmCircle(){};
        void paint(juce::Graphics & g) override;
        void resized() override;  

        void buttonClicked(juce::Button* b) override { //for debugging
        };

        void mouseDown(const juce::MouseEvent& e) override { //for debugging
        };

        void setNumSubdivisions(int num) {
            if (num < 1) {
                throw std::invalid_argument("received invalid value");
            }
            numSubdivisions = num;
            repaint();
        }
        int getNumSubdivisions() {
            return numSubdivisions;
        };
        void setHandAngleBySubdivision(int currentSubdivision) {
            //Set the hand angle based on a specific division of points on the circle
            handAngle = juce::degreesToRadians(360.f * (float(currentSubdivision) / float(numSubdivisions)) + 180.f);
            repaint();
        };
        void setHandAngleByFraction(float cycleFraction) {
            // Set the clock hand angle using a fraction of 360 degrees, where 0 represents starting position and 1 represents a full rotation back to start
            handAngle = juce::degreesToRadians(360.f * cycleFraction + 180.f);
            repaint();
        };
        void setHandAngle(float angle) {
            handAngle = juce::degreesToRadians(angle);
            repaint();
        };
        void setButtonSize(int _buttonSize) {
            if (_buttonSize < 1){
                throw std::invalid_argument("received invalid value");
            }
            if (_buttonSize % 2 != 0) {
                _buttonSize += 1;
            }
            buttonSize = _buttonSize;
            repaint();
        };
        void setHandWidth(int _handWidth) {
            if (_handWidth < 1) {
                throw std::invalid_argument("received invalid value");
            }
            if (_handWidth % 2 != 0) {
                _handWidth += 1;
            }
            handWidth = _handWidth;
            repaint();
        };
        void setDrawAsPolygons(bool _drawAsPolygons) {
            drawAsPolygons = _drawAsPolygons;
        }

        enum class ColourIds {
            //for choosing which Colour variable to access, tried to follow JUCE convention
            CircleColourId,
            HandColourId,
            ButtonColourId
        };

        void setColour(ColourIds id, juce::Colour colour) {
            switch (id) {
            case ColourIds::CircleColourId:
                circleColour = colour;
                break;
            case ColourIds::HandColourId:
                handColour = colour;
                break;
            case ColourIds::ButtonColourId:
                buttonColour = colour;
                break;
            }
            repaint(); 
        }

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

