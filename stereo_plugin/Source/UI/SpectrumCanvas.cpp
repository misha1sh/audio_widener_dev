/*
  ==============================================================================

    SpectrumCanvas.cpp
    Created: 25 Apr 2021 7:37:03pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectrumCanvas.h"


//==============================================================================
SpectrumCanvas::SpectrumCanvas()
{
    setOpaque(true);
    renderer.reset(new DynamicTextureOpenGL::DynamicTextureRenderer(*this));
}

SpectrumCanvas::~SpectrumCanvas()
{
}

float x = 0;
void SpectrumCanvas::paint (juce::Graphics& g)
{
}

void SpectrumCanvas::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

