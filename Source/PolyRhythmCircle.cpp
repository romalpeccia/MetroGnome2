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
    auto bounds = getLocalBounds();
    int width = bounds.getWidth();
    int height = bounds.getHeight();
    int diameter = ((width > height) ? height : width) ; //take the lesser of height and width of the bounds to be our circle diameter
    int X = bounds.getX(); //top left corner X
    int Y = bounds.getY();//top left corner Y


    //draw the circle
    juce::Path rhythmCircle;
    rhythmCircle.addEllipse(X , Y , diameter, diameter);
    g.setColour(circleColour);
    g.strokePath(rhythmCircle, juce::PathStrokeType(2.0f));


    float circlePerimeter = rhythmCircle.getLength(); 
    for (int i = 0; i < numSubdivisions; i++)
    {
        //iterate through beats and draw toggle button on the edge of the main circle

        float distanceOnPath = (float(i) / numSubdivisions) * circlePerimeter;
        auto point = rhythmCircle.getPointAlongPath(distanceOnPath);
        juce::Rectangle<int> pointBounds(point.getX(), point.getY(), 22, 22); 
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


    //draw the clock hand
    g.setColour(handColour);
    float angle = juce::degreesToRadians(180.f);
    //angle = juce::degreesToRadians(360 * (float(audioProcessor.polyRhythmMetronome.getRhythm1Counter()) / float(numSubdivisions)) + 180);
    int centerX = X + diameter / 2;
    int centerY = Y + diameter / 2; 
    int handWidth = 2;
    juce::Path clockHand;
    juce::Rectangle<float> handBounds(centerX , centerY, handWidth, diameter / 2);

    clockHand.addRoundedRectangle(handBounds, 2.f);
    clockHand.applyTransform(juce::AffineTransform().rotation(angle, centerX, centerY));
    g.fillPath(clockHand);
}

void PolyRhythmCircle::resized() {

}