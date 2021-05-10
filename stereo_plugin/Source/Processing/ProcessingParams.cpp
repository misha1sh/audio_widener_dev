#include "ProcessingParams.h"

#include <memory>

ProcessingParams::ProcessingParams(AudioProcessor& processor) :
    tree(processor, nullptr, juce::Identifier("Stereo_plugin"),
         {
            std::make_unique<juce::AudioParameterInt>("leftCutoff", // parameterID
                                                        "leftCutoff", // parameter name
                                                        1,   // minimum value
                                                        22000,   // maximum value
                                                        1000),
            std::make_unique<juce::AudioParameterFloat>("rightCutoff", // parameterID
                                                        "rightCutoff", // parameter name
                                                        1,   // minimum value
                                                        22000,   // maximum value
                                                        3000),
            std::make_unique<juce::AudioParameterFloat>("sineStretch", // parameterID
                                                        "sineStretch", // parameter name
                                                        0,   // minimum value
                                                        3,   // maximum value
                                                        1),

         })
{
    leftCutoff = tree.getRawParameterValue("leftCutoff");
    rightCutoff = tree.getRawParameterValue("rightCutoff");
    sineStretch = tree.getRawParameterValue("sineStretch");
}

