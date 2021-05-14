/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "kfr/all.hpp"

#include "PluginProcessor.h"

#include <comcat.h>

#include "PluginEditor.h"

//==============================================================================
PluginProcessor::PluginProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                       params(*this),
                       mainProcessor(params, rendering)
{
    setLatencySamples(mainProcessor.getLatencyInSamples());
}

PluginProcessor::~PluginProcessor()
{
}

//==============================================================================
const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int index)
{
}

const juce::String PluginProcessor::getProgramName (int index)
{
    return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
}
std::vector<std::queue<float>> lastValues;

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastValues.resize(0);
    params.sampleRate = sampleRate;
    params.maxSamplesPerBlock = samplesPerBlock;
    mainProcessor.reset();
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    lastValues.resize(buffer.getNumChannels());
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
 /*   for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    	for (int j = 0; j < buffer.getNumSamples(); j++)
    	{
            lastValues[channel].push(channelData[j]);
    		if (lastValues[channel].size() >= latency)
    		{
                channelData[j] = lastValues[channel].front();
                lastValues[channel].pop();
    		} else
    		{
                channelData[j] = 0;
    		}
    	}
    }*/
    kfr::univector<kfr::univector<kfr::f32, 0>, 2> data({
            kfr::make_array_ref(buffer.getWritePointer(0),
                                buffer.getNumSamples()),
            kfr::make_array_ref(buffer.getWritePointer(1),
                                buffer.getNumSamples())
    });

   /* for (int i = 0; i < data[0].size(); i++) {
        data[0][i] = 0;
        data[1][i] = 0;
        if (0 <= i && i <= data[0].size()) {
            float f = rand() % 100 / 100.f;
            data[0][i] = f;
            data[1][i] = f;
        }
    }

    kfr::univector<kfr::f32> dataCopy(data[0]);*/



    mainProcessor.process(data);
  /*  kfr::univector<kfr::f32> processedDataCopy(data[0]);

    for (int i = 0; i + FFT_SZ < data[0].size(); i++) {
        if (fabs(data[0][i + FFT_SZ] - dataCopy[i]) > 0.0001) {
            DBG("kek" + std::to_string(data[0][i + FFT_SZ]) + " " + std::to_string(dataCopy[i]));
            jassertfalse;
        }
    }
*/
    rendering.lastSampleRate = buffer.getNumSamples();
   // sendChangeMessage();
}

void PluginProcessor::processBlockBypassed(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
   // sendChangeMessage();

}

bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = params.tree.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (params.tree.state.getType()))
            params.tree.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
