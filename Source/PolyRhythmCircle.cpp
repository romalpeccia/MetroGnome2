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
    auto bounds = getLocalBounds().reduced(buttonSize/2);
    int width = bounds.getWidth();
    int height = bounds.getHeight();
    int diameter = ((width > height) ? height : width) ; //take the lesser of height and width of the bounds to be our circle diameter
    int X = bounds.getX(); //top left corner X
    int Y = bounds.getY(); //top left corner Y

    juce::Path rhythmCircle;
    rhythmCircle.addEllipse(X , Y, diameter, diameter);
    float circlePerimeter = rhythmCircle.getLength();
    g.setColour(circleColour);

    if (numSubdivisions > 3){
        for (int i = 0; i <= numSubdivisions - 1; i++) {
            float startPointOnPath = (float(i) / numSubdivisions) * circlePerimeter;
            float endPointOnPath = (float(i + 1) / numSubdivisions) * circlePerimeter;
            auto startPoint = rhythmCircle.getPointAlongPath(startPointOnPath);
            auto endPoint = rhythmCircle.getPointAlongPath(endPointOnPath);
            juce::Line<float> line(startPoint, endPoint);
            g.drawLine(line, 2.0f);
        }
    }
    else {
        g.strokePath(rhythmCircle, juce::PathStrokeType(2.0f));
    }

    g.setColour(buttonColour);
    
    for (int i = 0; i < numSubdivisions; i++)
    {
        float distanceOnPath = (float(i) / numSubdivisions) * circlePerimeter;
        juce::Point point = rhythmCircle.getPointAlongPath(distanceOnPath);
        juce::Rectangle<int> buttonBounds(point.getX() - buttonSize / 2, point.getY() - buttonSize / 2, buttonSize, buttonSize);
        beatButtons[i].setBounds(buttonBounds);    
    }
    
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (i < numSubdivisions) {
            beatButtons[i].setVisible(true);
        }
        else {
            beatButtons[i].setVisible(false);
        }
    }
    
    g.setColour(handColour);
    juce::Path clockHand;
    int centerX = X + diameter / 2;
    int centerY = Y + diameter / 2;
    juce::Rectangle<int> handBounds(centerX , centerY, handWidth, diameter / 2);
    clockHand.addRoundedRectangle(handBounds, 2.f);
    clockHand.applyTransform(juce::AffineTransform().rotation(handAngle, centerX, centerY));
    g.fillPath(clockHand);
}

void PolyRhythmCircle::resized() {

}