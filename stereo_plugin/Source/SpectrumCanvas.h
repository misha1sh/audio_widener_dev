/*
  ==============================================================================

    SpectrumCanvas.h
    Created: 25 Apr 2021 7:37:03pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Builds/VisualStudio2019/SpectrumRenderer.h"


class SpectrumCanvas : public juce::Component
{
public:
    SpectrumCanvas();
    ~SpectrumCanvas() override;

	
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    int redrawFrequency = 60;
    std::unique_ptr<SpectrumOpenGL::SpectrumRenderer> renderer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumCanvas)
};
