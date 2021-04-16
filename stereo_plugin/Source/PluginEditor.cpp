/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...



//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& processor)
    : juce::AudioProcessorEditor(processor), audioProcessor(processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider.get());
    juce__slider->setTooltip (TRANS("test"));
    juce__slider->setRange (0, 10, 0);
    juce__slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider->setTextBoxStyle (juce::Slider::TextBoxBelow, true, 80, 20);
    juce__slider->addListener (this);

    juce__slider->setBounds (144, 16, 80, 80);

    strengthLabel.reset (new juce::Label ("strengthLabel",
                                          TRANS("label text")));
    addAndMakeVisible (strengthLabel.get());
    strengthLabel->setTooltip (TRANS("strength"));
    strengthLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    strengthLabel->setJustificationType (juce::Justification::centredLeft);
    strengthLabel->setEditable (false, false, false);
    strengthLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    strengthLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    strengthLabel->setBounds (24, 40, 88, 24);

    juce__component.reset (new juce::Slider());
    addAndMakeVisible (juce__component.get());
    juce__component->setName ("ttets");

    juce__component->setBounds (184, 120, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__slider = nullptr;
    strengthLabel = nullptr;
    juce__component = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 0, y = 0, width = 300, height = 200;
        juce::Colour fillColour = juce::Colour (0x21ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == juce__slider.get())
    {
        //[UserSliderCode_juce__slider] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="PluginProcessor&amp; processor"
                 variableInitialisers="juce::AudioProcessorEditor(processor), audioProcessor(processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="300" initialHeight="200">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 300 200" fill="solid: 21ffffff" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="d357a1623f016aeb" memberName="juce__slider"
          virtualName="juce::Slider" explicitFocusOrder="0" pos="144 16 80 80"
          tooltip="test" min="0.0" max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="strengthLabel" id="9cfaa7758c78203f" memberName="strengthLabel"
         virtualName="" explicitFocusOrder="0" pos="24 40 88 24" tooltip="strength"
         edTextCol="ff000000" edBkgCol="0" labelText="label text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="ttets" id="7cc1dc834f04d7c1" memberName="juce__component"
                    virtualName="" explicitFocusOrder="0" pos="184 120 150 24" class="juce::Slider"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

