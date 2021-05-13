#pragma once

#include <JuceHeader.h>

class ProcessingParams {
public:
    ProcessingParams(AudioProcessor& processor);

    juce::AudioProcessorValueTreeState tree;

    std::atomic<float>* leftCutoff;
    std::atomic<float>* rightCutoff;
    std::atomic<float>* sineStretch;
    std::atomic<float>* attack;

    float sampleRate;
    int maxSamplesPerBlock;
};

