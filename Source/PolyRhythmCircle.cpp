/*
  ==============================================================================

    PolyRhythmCircle.cpp
    Created: 23 Dec 2024 4:16:50pm
    Author:  romal

  ==============================================================================
*/

#include "PolyRhythmCircle.h"

void PolyRhythmCircle::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(buttonSize);
    int width = bounds.getWidth();
    int height = bounds.getHeight();
    int diameter = ((width > height) ? height : width) ; //take the lesser of height and width of the bounds to be our circle diameter
    int X = bounds.getX(); //top left corner X
    int Y = bounds.getY(); //top left corner Y

    juce::Path rhythmCircle;
    rhythmCircle.addEllipse(X , Y, diameter, diameter);
    g.setColour(circleColour);
    g.strokePath(rhythmCircle, juce::PathStrokeType(2.0f));

    g.setColour(buttonColour);
    float circlePerimeter = rhythmCircle.getLength(); 
    for (int i = 0; i < numSubdivisions; i++)
    {
        //iterate through beats and draw toggle button on the edge of the main circle
        float distanceOnPath = (float(i) / numSubdivisions) * circlePerimeter;
        auto point = rhythmCircle.getPointAlongPath(distanceOnPath);
        g.drawEllipse(point.getX() - buttonSize/2, point.getY() - buttonSize / 2, buttonSize, buttonSize, 3); 
        /*
        Rhythm1Buttons[i].setBounds(pointBounds);
        Rhythm1Buttons[i].setVisible(true);
        if ((audioProcessor.apvts.getRawParameterValue("RHYTHM1." + to_string(i) + "_TOGGLE")->load() == true) && audioProcessor.polyRhythmMetronome.getRhythm1Counter() == i) {
            Rhythm1Buttons[i].setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::green);
        }
        else {
            Rhythm1Buttons[i].setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::grey);
        }
        */
  

    }
    g.setColour(handColour);
    juce::Path clockHand;
    int centerX = X + diameter / 2;
    int centerY = Y + diameter / 2;
    juce::Rectangle<float> handBounds(centerX , centerY, handWidth, diameter / 2);
    clockHand.addRoundedRectangle(handBounds, 2.f);
    clockHand.applyTransform(juce::AffineTransform().rotation(handAngle, centerX, centerY));
    g.fillPath(clockHand);
}

void PolyRhythmCircle::resized() {

}