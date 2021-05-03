#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

class ProcessingParams {
public:
    ProcessingParams(AudioProcessor& processor);

    juce::AudioParameterFloat* leftCutoff;
    juce::AudioParameterFloat* rightCutoff;
};

