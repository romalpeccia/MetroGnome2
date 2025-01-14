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

    
        void PolyRhythmMetronome::processBlock(juce::AudioBuffer<float>& buffer);
        void resetMetronome();
        int calculateSamplesPerDivision(int sampleRate, float bpm, int division, int beatsPerBar);

        int samplesElapsed = 0; //number of samples elapsed since the PolyRhythmMachine started
        int samplesPerDivision; //number of samples representating the time taken to complete one subdivision
    private:


};
