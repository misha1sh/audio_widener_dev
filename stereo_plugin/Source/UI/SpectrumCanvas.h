#pragma once

#include <JuceHeader.h>

#include "DynamicTextureRenderer/DynamicTextureRenderer.h"
#include "../Processing/ProcessingRendering.h"

class SpectrumCanvas : public juce::Component, private juce::Timer
{
public:
    SpectrumCanvas(ProcessingRendering& _rendering);
    ~SpectrumCanvas() override;

    void timerCallback() override;
	
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ProcessingRendering& rendering;

    Path maskPath[2];
    Path soundPath;
    std::vector<float> mask;
    std::vector<float> sound;

    void createMaskPath();
    void createSoundPath();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumCanvas)
};
