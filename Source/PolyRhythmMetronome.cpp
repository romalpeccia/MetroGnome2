/*
  ==============================================================================

    PolyRhythmMetronome.cpp
    Created: 5 Nov 2024 1:37:20am
    Author:  romal

  ==============================================================================
*/

#include "PolyRhythmMetronome.h"

void PolyRhythmMetronome::resetMetronome(int sampleRate, float _bpm, int _numSubdivisions) {
    //resets the class variables of the metronome, to be called when the metronome is stopped or has parameters changed
    numSubdivisions = _numSubdivisions;
    bpm = _bpm;
    samplesElapsed = 0;
    beatCounter = 0;
    samplesPerDivision = calculateSamplesPerDivision(sampleRate);
}

int PolyRhythmMetronome::calculateSamplesPerDivision(int sampleRate) {
    //returns the number of samples representing the amount of time taken for a subdivision of the bar
    int beatsPerBar = 4;
    int samplesPerBar = beatsPerBar * ((60.0 / bpm) * sampleRate); // TODO: beatsPerBar, samplesPerBar are not clear in what that means (per Cycle) ?
    return samplesPerBar / numSubdivisions;
}

void PolyRhythmMetronome::processBlock(juce::AudioBuffer<float>& buffer) {
    //process the incoming audio block, using the total number of samples in the audio block to calculate time elapsed

    int bufferSize = buffer.getNumSamples();
    samplesElapsed += bufferSize;
    int subdvisionSamplesElapsed = samplesElapsed % samplesPerDivision;
    if (subdvisionSamplesElapsed + bufferSize >= samplesPerDivision) {
        beatCounter += 1;
        if (beatCounter >= numSubdivisions) {
            beatCounter = 0;
        }
    }
}