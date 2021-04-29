#pragma once

#include <JuceHeader.h>

#include "SpectrumCanvas/DynamicTextureRenderer.h"


class SpectrumCanvas : public juce::Component
{
public:
    SpectrumCanvas();
    ~SpectrumCanvas() override;

	
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    int redrawFrequency = 60;
    std::unique_ptr<DynamicTextureOpenGL::DynamicTextureRenderer> renderer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumCanvas)
};
