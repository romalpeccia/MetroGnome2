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
    if (sampleRate < 0 || _bpm <= 0 ||_numSubdivisions < 1) {
        throw std::invalid_argument("received invalid value");
    }
    numSubdivisions = _numSubdivisions;
    bpm = _bpm;
    totalSamplesSinceReset = 0;
    subdivisionCounter = 0;
    samplesPerSubdivision = calculateSamplesPerSubdivision(sampleRate);
}

int PolyRhythmMetronome::calculateSamplesPerSubdivision(int sampleRate, int beatsPerBar) {
    //returns the number of samples representing the amount of time taken for a subdivision of the cycle
    if (sampleRate < 0 || beatsPerBar < 1){
        throw std::invalid_argument("received invalid value");
    }
    int samplesPerCycle = beatsPerBar * ((60.0 / bpm) * sampleRate); 
    return samplesPerCycle / numSubdivisions;
}

void PolyRhythmMetronome::processBlock(juce::AudioBuffer<float>& buffer) {
    //process the incoming audio block, using the total number of samples in the audio block to calculate time elapsed
    int bufferSize = buffer.getNumSamples();
    totalSamplesSinceReset += bufferSize;
    int samplesSinceSubdivisionStart = totalSamplesSinceReset % samplesPerSubdivision; 
    if (samplesSinceSubdivisionStart + bufferSize >= samplesPerSubdivision) { 
        subdivisionCounter += 1;
        if (subdivisionCounter >= numSubdivisions) {
            subdivisionCounter = 0;
        }
    }
}

void PolyRhythmMetronome::setBpm(float _bpm) {
    if (bpm <= 0) {
        throw std::invalid_argument("received invalid value");
    }
    bpm = _bpm;
}
float PolyRhythmMetronome::getBpm() { 
    return bpm; 
}

void PolyRhythmMetronome::setNumSubdivisions(int _numSubdivisions) {
    if (numSubdivisions < 1) {
        throw std::invalid_argument("received invalid value");
    }
    numSubdivisions = _numSubdivisions;
}
int PolyRhythmMetronome::getNumSubdivisions() { 
    return numSubdivisions; 
}

int PolyRhythmMetronome::getTotalSamplesSinceReset() {
    return totalSamplesSinceReset; 
}

void PolyRhythmMetronome::setSamplesPerSubdivision(int _samplesPerSubdivision) { 
    samplesPerSubdivision = _samplesPerSubdivision; 
}
int PolyRhythmMetronome::getSamplesPerSubdivision() {
    return samplesPerSubdivision;
}

void PolyRhythmMetronome::setSubdivisionCounter(int _subdivisionCounter) { 
    subdivisionCounter = _subdivisionCounter; 
}

int PolyRhythmMetronome::getSubdivisionCounter() { 
    return subdivisionCounter; 
}