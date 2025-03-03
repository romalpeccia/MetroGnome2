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
        void resetMetronome(int sampleRate, float bpm, int _numSubdivisions); 
        int calculateSamplesPerSubdivision(int sampleRate, int beatsPerBar = 4); //


        void setBpm(float _bpm);
        float getBpm();

        void setNumSubdivisions(int _numSubdivisions);
        int getNumSubdivisions();

        //void setTotalSamplesSinceReset(int _totalSamplesSinceReset) { totalSamplesSinceReset = _totalSamplesSinceReset; }
        int getTotalSamplesSinceReset();

        void setSamplesPerSubdivision(int _samplesPerSubdivision);
        int getSamplesPerSubdivision();

        void setSubdivisionCounter(int _subdivisionCounter);
        int getSubdivisionCounter();



    private:
        float bpm = 120;
        int numSubdivisions = 4; //number of subdivisions the cycle is being split into
        int totalSamplesSinceReset = 0; //number of samples elapsed since the PolyRhythmMachine started
        int samplesPerSubdivision; //number of samples representating the time taken to complete one subdivision
        int subdivisionCounter = 0; //counts which beat of the sequence has most recently played
};
