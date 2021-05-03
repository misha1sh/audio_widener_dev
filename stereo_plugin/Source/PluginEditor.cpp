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

    blockSize->setBounds (56, 104, 150, 24);

    blockSize2.reset (new juce::Label ("new label",
                                       TRANS("label text")));
    addAndMakeVisible (blockSize2.get());
    blockSize2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    blockSize2->setJustificationType (juce::Justification::centredLeft);
    blockSize2->setEditable (false, false, false);
    blockSize2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    blockSize2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    blockSize2->setBounds (56, 136, 150, 24);

    leftCutoffSlider.reset (new juce::Slider ("leftCutoffSlider"));
    addAndMakeVisible (leftCutoffSlider.get());
    leftCutoffSlider->setRange (0, 3, 0);
    leftCutoffSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    leftCutoffSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    leftCutoffSlider->addListener (this);

    leftCutoffSlider->setBounds (137, 200, 150, 24);

    rightCutoffSlider.reset (new juce::Slider ("rightCutoffSlider"));
    addAndMakeVisible (rightCutoffSlider.get());
    rightCutoffSlider->setRange (0, 3, 0);
    rightCutoffSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    rightCutoffSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    rightCutoffSlider->addListener (this);

    rightCutoffSlider->setBounds (136, 232, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 400);


    //[Constructor] You can add your own custom stuff here..
    setResizable(true, true);
    setResizeLimits(100, 100, 1000, 1000);
    audioProcessor.addChangeListener(this);

    leftCutoffSlider->setValue(audioProcessor.params.leftCutoff->get());
    leftCutoffSlider->setValue(audioProcessor.params.rightCutoff->get());
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
    blockSize2 = nullptr;
    leftCutoffSlider = nullptr;
    rightCutoffSlider = nullptr;


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

    {
        int x = -12, y = 196, width = 200, height = 30;
        juce::String text (TRANS("Left cutoff"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = -12, y = 228, width = 200, height = 30;
        juce::String text (TRANS("Right cutoff"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
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
    else if (sliderThatWasMoved == leftCutoffSlider.get())
    {
        //[UserSliderCode_leftCutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_leftCutoffSlider]
    }
    else if (sliderThatWasMoved == rightCutoffSlider.get())
    {
        //[UserSliderCode_rightCutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_rightCutoffSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    blockSize->setText(juce::String(audioProcessor.lastSamplesCount.get()), juce::sendNotificationAsync);
    blockSize2->setText(juce::String(audioProcessor.lastBypassedSamplesCount.get()), juce::sendNotificationAsync);
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
    <TEXT pos="-12 196 200 30" fill="solid: ff000000" hasStroke="0" text="Left cutoff"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="-12 228 200 30" fill="solid: ff000000" hasStroke="0" text="Right cutoff"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
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
         virtualName="" explicitFocusOrder="0" pos="56 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fd9332144ef16970" memberName="blockSize2"
         virtualName="" explicitFocusOrder="0" pos="56 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="leftCutoffSlider" id="110eb12e1151856" memberName="leftCutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="137 200 150 24" min="0.0"
          max="3.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="rightCutoffSlider" id="f5f11eb2404957fc" memberName="rightCutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="136 232 150 24" min="0.0"
          max="3.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

