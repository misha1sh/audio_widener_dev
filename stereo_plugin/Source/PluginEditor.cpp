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

    spectrum_canvas.reset (new SpectrumCanvas());
    addAndMakeVisible (spectrum_canvas.get());
    spectrum_canvas->setName ("spectrum_canvas");

    spectrum_canvas->setBounds (248, 96, 368, 256);

    blockSize.reset (new juce::Label ("new label",
                                      TRANS("label text")));
    addAndMakeVisible (blockSize.get());
    blockSize->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    blockSize->setJustificationType (juce::Justification::centredLeft);
    blockSize->setEditable (false, false, false);
    blockSize->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    blockSize->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    blockSize->setBounds (56, 160, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 400);


    //[Constructor] You can add your own custom stuff here..
    setResizable(true, true);
    setResizeLimits(100, 100, 1000, 1000);
    audioProcessor.addChangeListener(this);
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__slider = nullptr;
    strengthLabel = nullptr;
    spectrum_canvas = nullptr;
    blockSize = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    audioProcessor.removeChangeListener(this);
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 0, y = 0, width = 700, height = 400;
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
void PluginEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    blockSize->setText(juce::String(audioProcessor.lastSamplesCount.get()), juce::sendNotificationAsync);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor, public juce::ChangeListener"
                 constructorParams="PluginProcessor&amp; processor" variableInitialisers="juce::AudioProcessorEditor(processor), audioProcessor(processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="700" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 700 400" fill="solid: 21ffffff" hasStroke="0"/>
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
  <GENERICCOMPONENT name="spectrum_canvas" id="c28ba59d3075a746" memberName="spectrum_canvas"
                    virtualName="" explicitFocusOrder="0" pos="248 96 368 256" class="SpectrumCanvas"
                    params=""/>
  <LABEL name="new label" id="41486794b98566e2" memberName="blockSize"
         virtualName="" explicitFocusOrder="0" pos="56 160 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

