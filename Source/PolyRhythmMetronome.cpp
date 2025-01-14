/*
  ==============================================================================

    PolyRhythmMetronome.cpp
    Created: 5 Nov 2024 1:37:20am
    Author:  romal

  ==============================================================================
*/

#include "PolyRhythmMetronome.h"

void PolyRhythmMetronome::resetMetronome() {
    //resets the class variables of the metronome, to be called when the metronome is stopped or has parameters changed

    samplesElapsed = 0;
    //samplesPerDivision = calculateSamplesPerDivision(); 
}

int PolyRhythmMetronome::calculateSamplesPerDivision(int sampleRate, float bpm, int numDivisions, int beatsPerBar = 4) {
    //returns the number of samples representing the amount of time taken for a subdivision of the bar

    int samplesPerBar = beatsPerBar * ((60.0 / bpm) * sampleRate);
    return samplesPerBar / numDivisions;
}

void PolyRhythmMetronome::processBlock(juce::AudioBuffer<float>& buffer) {
    //process the incoming audio block, using the total number of samples in the audio block to calculate time elapsed

    int bufferSize = buffer.getNumSamples();
    samplesElapsed += bufferSize;
    int subdvisionSamplesElapsed = samplesElapsed % samplesPerDivision;

    if (subdvisionSamplesElapsed + bufferSize >= samplesPerDivision) {
        //do something
        //DBG("TEST");

    }
}