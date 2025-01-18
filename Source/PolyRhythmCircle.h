/*
  ==============================================================================

    PolyRhythmCircle.h
    Created: 23 Dec 2024 4:16:50pm
    Author:  romal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class PolyRhythmCircle : public juce::Component {
    public:
        PolyRhythmCircle() {};
        PolyRhythmCircle(int _handWidth, int _buttonSize, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour) {
            handWidth = _handWidth;
            buttonSize = _buttonSize;
            circleColour = _circleColour;
            handColour = _handColour;
            buttonColour = _buttonColour;
        };
        ~PolyRhythmCircle(){};

        void paint(juce::Graphics & g) override;
        void resized() override;  
        void setNumSubdivisions(int num) {
            numSubdivisions = num;
            DBG(numSubdivisions);
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
};