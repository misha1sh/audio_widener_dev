#include "ProcessingParams.h"

#include <memory>

ProcessingParams::ProcessingParams(AudioProcessor& processor) :
    tree(processor, nullptr, juce::Identifier("Stereo_plugin"),
         {
            std::make_unique<juce::AudioParameterFloat>("leftCutoff", // parameterID
                                                        "Left cutoff", // parameter name
                                                        1,   // minimum value
                                                        15000,   // maximum value
                                                        1),
            std::make_unique<juce::AudioParameterFloat>("rightCutoff", // parameterID
                                                        "Right cutoff", // parameter name
                                                        1,   // minimum value
                                                        15000,   // maximum value
                                                        15000),
            std::make_unique<juce::AudioParameterFloat>("strength", // parameterID
                                                        "Strength", // parameter name
                                                        0,   // minimum value
                                                        2,   // maximum value
                                                        1),
            std::make_unique<juce::AudioParameterFloat>("frequencySpread", // parameterID
                                                        "Frequency spread", // parameter name
                                                        0.1,   // minimum value
                                                        0.999,   // maximum value
                                                        0.3),
            std::make_unique<juce::AudioParameterFloat>("attack", // parameterID
                                                        "Attack", // parameter name
                                                        0,   // minimum value
                                                        0.999,   // maximum value
                                                        0.95),
            std::make_unique<juce::AudioParameterFloat>("noise", // parameterID
                                                        "Noise", // parameter name
                                                        0,   // minimum value
                                                        1,   // maximum value
                                                        0),
            std::make_unique<juce::AudioParameterFloat>("dynamicSplitEnabled", // parameterID
                                                        "Dynamic split", // parameter name
                                                        0,   // minimum value
                                                        1,   // maximum value
                                                        1),
         })
{
    leftCutoff = tree.getRawParameterValue("leftCutoff");
    rightCutoff = tree.getRawParameterValue("rightCutoff");
    strength = tree.getRawParameterValue("strength");
    frequencySpread = tree.getRawParameterValue("frequencySpread");
    attack = tree.getRawParameterValue("attack");
    noise = tree.getRawParameterValue("noise");
    dynamicSplitEnabled = tree.getRawParameterValue("dynamicSplitEnabled");
}

