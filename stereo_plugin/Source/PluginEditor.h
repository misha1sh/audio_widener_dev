/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>


#include "UI/SpectrumCanvas.h"
#include "TestComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::ChangeListener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor& processor);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor& audioProcessor;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    std::unique_ptr<SliderAttachment> leftCutoffAttachment, rightCutoffAttachment, sineStretchAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<SpectrumCanvas> spectrum_canvas;
    std::unique_ptr<juce::Label> blockSize;
    std::unique_ptr<juce::Label> blockSize2;
    std::unique_ptr<juce::Slider> leftCutoffSlider;
    std::unique_ptr<juce::Slider> rightCutoffSlider;
    std::unique_ptr<juce::Slider> sineStretchSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

