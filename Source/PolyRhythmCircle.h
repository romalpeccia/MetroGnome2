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
        ~PolyRhythmCircle(){};

        void paint(juce::Graphics & g) override;
        void resized() override;  
        void setNumSubdivisions(int num) {
            numSubdivisions = num;
            repaint();
        }


        juce::Colour circleColour = juce::Colours::red;
        juce::Colour handColour = juce::Colours::green;
        int numSubdivisions;

};