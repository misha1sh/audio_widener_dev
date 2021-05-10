#pragma once

#include <JuceHeader.h>

class ProcessingParams {
public:
    ProcessingParams(AudioProcessor& processor);

    juce::AudioProcessorValueTreeState tree;

    std::atomic<float>* leftCutoff;
    std::atomic<float>* rightCutoff;
    std::atomic<float>* sineStretch;

    float sampleRate;
    int maxSamplesPerBlock;
};

