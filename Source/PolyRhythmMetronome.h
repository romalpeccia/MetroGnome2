/*
  ==============================================================================

    PolyRhythmMetronome.h
    Created: 5 Nov 2024 1:37:20am
    Author:  romal

  ==============================================================================
*/

#pragma once
#include "Utilities.h"

class PolyRhythmMetronome {

    public:
        PolyRhythmMetronome() {};
        ~PolyRhythmMetronome() {};

    
        void PolyRhythmMetronome::processBlock(juce::AudioBuffer<float>& buffer);
        void resetMetronome();
        int calculateSamplesPerDivision(int sampleRate, float bpm, int division, int beatsPerBar);

        int samplesElapsed = 0; //number of samples elapsed since the PolyRhythmMachine started
        int samplesPerDivision; //number of samples representating the time taken to complete one subdivision
    private:


};

void PolyRhythmMetronome::resetMetronome() {
    //resets the class variables of the metronome, to be called when the metronome is stopped or has parameters changed

    samplesElapsed = 0;
    //samplesPerDivision = calculateSamplesPerDivision(); TODO: where to put the calling of APVTS params? we could make it the callers responsibility to supply these variables?
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
        DBG("TEST");

    }


}