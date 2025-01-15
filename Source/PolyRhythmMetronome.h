/*
  ==============================================================================

    PolyRhythmMetronome.h
    Created: 5 Nov 2024 1:37:20am
    Author:  romal

  ==============================================================================
*/

#pragma once
#include "Utilities.h"

class PolyRhythmMetronome  {

    public:
        PolyRhythmMetronome() {};
        ~PolyRhythmMetronome() {};

    
        void processBlock(juce::AudioBuffer<float>& buffer);
        void resetMetronome(int sampleRate, float bpm, int numDivisions); 
        int calculateSamplesPerDivision(int sampleRate);

        float bpm = 120;
        int numSubdivisions = 4;
        int samplesElapsed = 0; //number of samples elapsed since the PolyRhythmMachine started
        int samplesPerDivision; //number of samples representating the time taken to complete one subdivision
        int beatCounter = 0; //counts which beat of the sequence has most recently played
    private:


};
