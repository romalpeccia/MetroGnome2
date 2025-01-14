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
    int circleSkew = 1.2; //TODO adjust this using JUCE_LIVE_CONSTANT
    int radius = ((width > height) ? height : width) / circleSkew; //take the lesser of height and width of the bounds to be our circle diameter
    int X = bounds.getX(); //top left corner X
    int Y = bounds.getY();//top left corner Y


    //draw the circle
    juce::Path rhythmCircle;
    int rhythmRadius = radius / circleSkew; //TODO maybe change this number, make a param?
    int Xoffset = (width - rhythmRadius) / 2;
    int Yoffset = (height - rhythmRadius) / 2;
    rhythmCircle.addEllipse(X + Xoffset, Y + Yoffset, rhythmRadius, rhythmRadius);
    g.setColour(circleColour);
    g.strokePath(rhythmCircle, juce::PathStrokeType(2.0f));


    float rhythm1Length = rhythmCircle.getLength();
    for (int i = 0; i < numSubdivisions; i++)
    {
        //iterate through beats and draw toggle button on the edge of the main circle

        float distanceOnPath = (float(i) / numSubdivisions) * rhythm1Length;
        auto point = rhythmCircle.getPointAlongPath(distanceOnPath);
        juce::Rectangle<int> pointBounds(point.getX(), point.getY(), 22, 22); //TODO  why 22?
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
    float angle = 0;
    juce::Point<int> center;

    center.setXY(X + rhythmRadius / 2, Y + (height - Xoffset) / 2);
    angle = 0;//juce::degreesToRadians(360 * (float(audioProcessor.polyRhythmMetronome.getRhythm1Counter()) / float(numSubdivisions)) + 180);
    


    juce::Path clockHand;
    juce::Rectangle<float> r;
    r.setLeft(center.getX() - 2);
    r.setRight(center.getX() + 2);
    r.setTop(center.getY());
    r.setBottom(center.getY() + rhythmRadius / 2);
    clockHand.addRoundedRectangle(r, 2.f);
    clockHand.applyTransform(juce::AffineTransform().rotation(angle, center.getX(), center.getY()));
    g.fillPath(clockHand);
}

void PolyRhythmCircle::resized() {

}