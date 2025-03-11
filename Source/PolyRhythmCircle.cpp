/*
  ==============================================================================

    PolyRhythmCircle.cpp
    Created: 23 Dec 2024 4:16:50pm
    Author:  romal

  ==============================================================================
*/

#include "PolyRhythmCircle.h"


PolyRhythmCircle::PolyRhythmCircle(juce::AudioProcessorValueTreeState& _apvts, juce::String _id, int _handWidth, int _buttonSize, bool _drawPolygons, juce::Colour _circleColour, juce::Colour _handColour, juce::Colour _buttonColour) : apvts(_apvts), id(_id)
{
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
}

void PolyRhythmCircle::paint(juce::Graphics& g) //
{
    //draws a circle or polygon with toggleable buttons for each beat, and an arm which points to which beat the polyrhythmcircle is currently playing

    auto bounds = getLocalBounds().reduced(buttonSize/2); //adjust the bounds to take into account the button size
    int width = bounds.getWidth();
    int height = bounds.getHeight();
    int diameter = ((width > height) ? height : width); //take the lesser of height and width of the bounds to be our circle diameter
    int X = bounds.getX(); //top left corner X
    int Y = bounds.getY(); //top left corner Y

    //draw the circle or polygon
    juce::Path rhythmCircle;
    rhythmCircle.addEllipse(X , Y, diameter, diameter);
    float circlePerimeter = rhythmCircle.getLength();
    g.setColour(circleColour);

    if (numSubdivisions > 3 && drawAsPolygons == true){
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

    //draw the toggle buttons on the shape
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
    
    //draw the clock arm
    g.setColour(handColour);
    juce::Path clockHand;
    int centerX = X + diameter / 2;
    int centerY = Y + diameter / 2;
    juce::Rectangle<int> handBounds(centerX , centerY, handWidth, diameter / 2);
    clockHand.addRoundedRectangle(handBounds, 2.f);
    clockHand.applyTransform(juce::AffineTransform().rotation(handAngle, centerX, centerY));
    g.fillPath(clockHand);
}

void PolyRhythmCircle::setNumSubdivisions(int num) {
    if (num < 1) {
        throw std::invalid_argument("received invalid value");
    }
    numSubdivisions = num;
    repaint();
}

int PolyRhythmCircle::getNumSubdivisions() {
    return numSubdivisions;
};

void PolyRhythmCircle::setHandAngleBySubdivision(int currentSubdivision) {
    //Set the hand angle based on a specific division of points on the circle
    handAngle = juce::degreesToRadians(360.f * (float(currentSubdivision) / float(numSubdivisions)) + 180.f);
    repaint();
};

void PolyRhythmCircle::setHandAngleByFraction(float cycleFraction) {
    // Set the clock hand angle using a fraction of 360 degrees, where 0 represents starting position and 1 represents a full rotation back to start
    handAngle = juce::degreesToRadians(360.f * cycleFraction + 180.f);
    repaint();
}

void PolyRhythmCircle::setHandAngle(float angle) {
    handAngle = juce::degreesToRadians(angle);
    repaint();
};

void PolyRhythmCircle::setButtonSize(int _buttonSize) {
    if (_buttonSize < 1) {
        throw std::invalid_argument("received invalid value");
    }
    if (_buttonSize % 2 != 0) {
        _buttonSize += 1;
    }
    buttonSize = _buttonSize;
    repaint();
};

void PolyRhythmCircle::setHandWidth(int _handWidth) {
    if (_handWidth < 1) {
        throw std::invalid_argument("received invalid value");
    }
    if (_handWidth % 2 != 0) {
        _handWidth += 1;
    }
    handWidth = _handWidth;
    repaint();
};

void PolyRhythmCircle::setDrawAsPolygons(bool _drawAsPolygons) {
    drawAsPolygons = _drawAsPolygons;
}

void PolyRhythmCircle::setColour(PolyRhythmCircle::ColourIds id, juce::Colour colour) {
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