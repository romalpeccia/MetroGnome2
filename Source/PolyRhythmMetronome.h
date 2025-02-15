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


        void setBpm(float _bpm) {
            if (bpm <= 0) {
                throw std::invalid_argument("received invalid value");
            }
            bpm = _bpm;
        }
        float getBpm() { return bpm; }

        void setNumSubdivisions(int _numSubdivisions) { 
            if (numSubdivisions < 1) {
                throw std::invalid_argument("received invalid value");
            }
            numSubdivisions = _numSubdivisions;
        }
        int getNumSubdivisions() { return numSubdivisions; }

        //void setTotalSamplesSinceReset(int _totalSamplesSinceReset) { totalSamplesSinceReset = _totalSamplesSinceReset; }
        int getTotalSamplesSinceReset() { return totalSamplesSinceReset; }

        void setSamplesPerSubdivision(int _samplesPerSubdivision) { samplesPerSubdivision = _samplesPerSubdivision; }
        int getSamplesPerSubdivision() { return samplesPerSubdivision; }

        void setSubdivisionCounter(int _subdivisionCounter) { subdivisionCounter = _subdivisionCounter; }
        int getSubdivisionCounter() { return subdivisionCounter; }



    private:
        float bpm = 120;
        int numSubdivisions = 4; //number of subdivisions the cycle is being split into
        int totalSamplesSinceReset = 0; //number of samples elapsed since the PolyRhythmMachine started
        int samplesPerSubdivision; //number of samples representating the time taken to complete one subdivision
        int subdivisionCounter = 0; //counts which beat of the sequence has most recently played
};
