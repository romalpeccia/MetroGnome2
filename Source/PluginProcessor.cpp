/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetroGnome2AudioProcessor::MetroGnome2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{   
    bpmParam = apvts.getRawParameterValue("BPM");
    onOffParam = apvts.getRawParameterValue("ON/OFF");
    subdivision1Param = apvts.getRawParameterValue("SUBDIVISION_1");
    subdivision2Param = apvts.getRawParameterValue("SUBDIVISION_2");
    apvts.addParameterListener("BPM", this);
    apvts.addParameterListener("ON/OFF", this);
    apvts.addParameterListener("SUBDIVISION_1", this);
    apvts.addParameterListener("SUBDIVISION_2", this);

    juce::MemoryInputStream* inputStream = new juce::MemoryInputStream(BinaryData::drum_low_wav, BinaryData::drum_low_wavSize, false);
    juce::WavAudioFormat wavFormat;
    juce::AudioFormatReader* formatReader = wavFormat.createReaderFor(inputStream, false);
    drumMidSample.reset(new juce::AudioFormatReaderSource(formatReader, true));

    juce::MemoryInputStream* inputStream2 = new juce::MemoryInputStream(BinaryData::drum_high_wav, BinaryData::drum_high_wavSize, false);
    juce::WavAudioFormat wavFormat2;
    juce::AudioFormatReader* formatReader2 = wavFormat2.createReaderFor(inputStream2, false);
    drumHighSample.reset(new juce::AudioFormatReaderSource(formatReader2, true));

    juce::MemoryInputStream* inputStream3 = new juce::MemoryInputStream(BinaryData::drum_sub_wav, BinaryData::drum_sub_wavSize, false);
    juce::WavAudioFormat wavFormat3;
    juce::AudioFormatReader* formatReader3 = wavFormat3.createReaderFor(inputStream3, false);
    drumLowSample.reset(new juce::AudioFormatReaderSource(formatReader3, true));
}

MetroGnome2AudioProcessor::~MetroGnome2AudioProcessor()
{  
}


juce::AudioProcessorValueTreeState::ParameterLayout MetroGnome2AudioProcessor::createParameterLayout() {
    //Creates all the parameters that change based on the user input and returns them in a AudioProcessorValueTreeState::ParameterLayout object

    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterBool>("ON/OFF", "On/Off", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>("BPM", "bpm", juce::NormalisableRange<float>(1.f, 300.f, 0.1f, 0.5f), 120.f));
    layout.add(std::make_unique<juce::AudioParameterInt>("SUBDIVISION_1", "Subdivision 1", 1, MAX_LENGTH, 1));
    layout.add(std::make_unique<juce::AudioParameterInt>("SUBDIVISION_2", "Subdivision 2", 1, MAX_LENGTH, 1));


    for (int i = 0; i < MAX_LENGTH; i++) {
        layout.add(std::make_unique<juce::AudioParameterBool>("CIRCLE_1_BEAT_" + to_string(i), "Circle 1 Beat " + to_string(i), true));
        layout.add(std::make_unique<juce::AudioParameterBool>("CIRCLE_2_BEAT_" + to_string(i), "Circle 2 Beat " + to_string(i), true));
    }
    return layout;

}

void MetroGnome2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    if (drumMidSample != nullptr)
    {
        drumMidSample->prepareToPlay(samplesPerBlock, sampleRate);
    }
    if (drumHighSample != nullptr)
    {
        drumHighSample->prepareToPlay(samplesPerBlock, sampleRate);
    }
    if (drumLowSample != nullptr)
    {
        drumLowSample->prepareToPlay(samplesPerBlock, sampleRate);
    }
}

void MetroGnome2AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    metronome1.processBlock(buffer);
    metronome2.processBlock(buffer);
    if (metronome1.beatCounter != beatCounter1 && metronome2.beatCounter != beatCounter2 ) {

        beatCounter1 = metronome1.beatCounter;
        beatCounter2 = metronome2.beatCounter;
        if (apvts.getRawParameterValue("CIRCLE_1_BEAT_" + to_string(beatCounter1))->load() == true && apvts.getRawParameterValue("CIRCLE_2_BEAT_" + to_string(beatCounter2))->load() == true) { //TODO: use params instead of loading like this
            addAudioToBuffer(buffer, *drumLowSample, metronome1);
        }
        sendActionMessage("beatCounter1");
        sendActionMessage("beatCounter2");
    }
    else if (metronome1.beatCounter != beatCounter1) {

        beatCounter1 = metronome1.beatCounter;
        if (apvts.getRawParameterValue("CIRCLE_1_BEAT_" + to_string(beatCounter1))->load() == true) {
            addAudioToBuffer(buffer, *drumMidSample, metronome1);
        }
        sendActionMessage("beatCounter1");
    }
    else if (metronome2.beatCounter != beatCounter2) {

        beatCounter2 = metronome2.beatCounter;
        if (apvts.getRawParameterValue("CIRCLE_2_BEAT_" + to_string(beatCounter2))->load() == true) {
            addAudioToBuffer(buffer, *drumHighSample, metronome2);
        }
        sendActionMessage("beatCounter2");
    }
}

void MetroGnome2AudioProcessor::addAudioToBuffer(juce::AudioBuffer<float>& buffer, juce::AudioFormatReaderSource& sample, PolyRhythmMetronome metronome)
{
    if (&sample != nullptr)
    {
        sample.setNextReadPosition(0);
        juce::AudioSourceChannelInfo audioSourceChannelInfo = juce::AudioSourceChannelInfo(buffer);
        int bufferSize = buffer.getNumSamples();
        int timeToStartPlaying = int(metronome.samplesPerDivision - metronome.samplesElapsed % metronome.samplesPerDivision);

        for (int samplenum = 0; samplenum < bufferSize + 1; samplenum++) //TODO : I have no idea what this loop does or how it is affecting the getNextAudioBlock call in any way but it does something
        {
            if (samplenum == timeToStartPlaying)
            {
                sample.getNextAudioBlock(audioSourceChannelInfo);
                break;
            }
        }
    }
}

void MetroGnome2AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    metronome1.resetMetronome(getSampleRate(), *bpmParam, *subdivision1Param);
    metronome2.resetMetronome(getSampleRate(), *bpmParam, *subdivision2Param);
    DBG("Parameter " << parameterID << " has changed to " << newValue);
}







juce::AudioProcessorEditor* MetroGnome2AudioProcessor::createEditor()
{
    //return GenericAudioProcessorEditor for generic sliders magically linked to APVTS (used for debugging/prototyping)
    return new MetroGnome2AudioProcessorEditor (*this, apvts);
}

//==============================================================================
void MetroGnome2AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void MetroGnome2AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        apvts.replaceState(tree);
    }

}


//==============================================================================
const juce::String MetroGnome2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MetroGnome2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MetroGnome2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MetroGnome2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MetroGnome2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MetroGnome2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MetroGnome2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void MetroGnome2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MetroGnome2AudioProcessor::getProgramName (int index)
{
    return {};
}

void MetroGnome2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void MetroGnome2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MetroGnome2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool MetroGnome2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MetroGnome2AudioProcessor();
}
