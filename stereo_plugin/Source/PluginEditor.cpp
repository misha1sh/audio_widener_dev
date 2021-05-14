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

    spectrum_canvas.reset (new SpectrumCanvas());
    addAndMakeVisible (spectrum_canvas.get());
    spectrum_canvas->setName ("spectrum_canvas");

    spectrum_canvas->setBounds (144, 24, 288, 200);

    blockSize.reset (new juce::Label ("new label",
                                      TRANS("label text")));
    addAndMakeVisible (blockSize.get());
    blockSize->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    blockSize->setJustificationType (juce::Justification::centredLeft);
    blockSize->setEditable (false, false, false);
    blockSize->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    blockSize->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    blockSize->setBounds (280, 0, 150, 24);

    blockSize2.reset (new juce::Label ("new label",
                                       TRANS("label text")));
    addAndMakeVisible (blockSize2.get());
    blockSize2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    blockSize2->setJustificationType (juce::Justification::centredLeft);
    blockSize2->setEditable (false, false, false);
    blockSize2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    blockSize2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    blockSize2->setBounds (384, 0, 150, 24);

    leftCutoffSlider.reset (new juce::Slider ("leftCutoffSlider"));
    addAndMakeVisible (leftCutoffSlider.get());
    leftCutoffSlider->setRange (1, 20000, 0);
    leftCutoffSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    leftCutoffSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    leftCutoffSlider->addListener (this);

    leftCutoffSlider->setBounds (224, 240, 128, 88);

    rightCutoffSlider.reset (new juce::Slider ("rightCutoffSlider"));
    addAndMakeVisible (rightCutoffSlider.get());
    rightCutoffSlider->setRange (1, 20000, 0);
    rightCutoffSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    rightCutoffSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    rightCutoffSlider->addListener (this);

    rightCutoffSlider->setBounds (336, 240, 128, 88);

    sineStretchSlider.reset (new juce::Slider ("sineStretchSlider"));
    addAndMakeVisible (sineStretchSlider.get());
    sineStretchSlider->setRange (0.01, 10, 0);
    sineStretchSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    sineStretchSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    sineStretchSlider->addListener (this);

    sineStretchSlider->setBounds (0, 8, 128, 88);

    attackSlider.reset (new juce::Slider ("sineStretchSlider"));
    addAndMakeVisible (attackSlider.get());
    attackSlider->setRange (0, 0.999, 0);
    attackSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    attackSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    attackSlider->addListener (this);

    attackSlider->setBounds (0, 104, 128, 88);

    juce__toggleButton.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (juce__toggleButton.get());
    juce__toggleButton->setButtonText (TRANS("Dynamic filter"));
    juce__toggleButton->addListener (this);
    juce__toggleButton->setToggleState (true, juce::dontSendNotification);

    juce__toggleButton->setBounds (8, 216, 120, 24);

    sineStretchSlider2.reset (new juce::Slider ("sineStretchSlider"));
    addAndMakeVisible (sineStretchSlider2.get());
    sineStretchSlider2->setTooltip (TRANS("few ew few few few fwe fewf wef ewf ew"));
    sineStretchSlider2->setRange (0.01, 10, 0);
    sineStretchSlider2->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    sineStretchSlider2->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    sineStretchSlider2->addListener (this);

    sineStretchSlider2->setBounds (0, 240, 128, 88);

    juce__label.reset (new juce::Label ("Left cutoff",
                                        TRANS("Left cutoff")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centred);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (216, 320, 150, 24);

    juce__label2.reset (new juce::Label ("Right cutoff",
                                         TRANS("Right cutoff")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centred);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (328, 320, 150, 24);

    juce__label3.reset (new juce::Label ("Filter strength",
                                         TRANS("Filter strength")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centred);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (0, 80, 128, 32);

    juce__label4.reset (new juce::Label ("Split strength",
                                         TRANS("Split strength")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label4->setBounds (16, 184, 104, 24);

    juce__label5.reset (new juce::Label ("Attack",
                                         TRANS("Attack")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centred);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (16, 320, 96, 24);

    sineStretchSlider3.reset (new juce::Slider ("sineStretchSlider"));
    addAndMakeVisible (sineStretchSlider3.get());
    sineStretchSlider3->setTooltip (TRANS("few ew few few few fwe fewf wef ewf ew"));
    sineStretchSlider3->setRange (0.01, 10, 0);
    sineStretchSlider3->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    sineStretchSlider3->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    sineStretchSlider3->addListener (this);

    sineStretchSlider3->setBounds (112, 240, 128, 88);

    juce__label6.reset (new juce::Label ("Random",
                                         TRANS("Random")));
    addAndMakeVisible (juce__label6.get());
    juce__label6->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label6->setJustificationType (juce::Justification::centred);
    juce__label6->setEditable (false, false, false);
    juce__label6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label6->setBounds (128, 320, 96, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (444, 348);


    //[Constructor] You can add your own custom stuff here..
    setResizable(true, true);
    setResizeLimits(100, 100, 1000, 1000);
    audioProcessor.addChangeListener(this);

    leftCutoffAttachment = std::make_unique<SliderAttachment>(audioProcessor.params.tree, "leftCutoff", *leftCutoffSlider);
    rightCutoffAttachment = std::make_unique<SliderAttachment>(audioProcessor.params.tree, "rightCutoff", *rightCutoffSlider);
    sineStretchAttachment = std::make_unique<SliderAttachment>(audioProcessor.params.tree, "sineStretch", *sineStretchSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.params.tree, "attack", *attackSlider);
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    leftCutoffAttachment = nullptr;
    rightCutoffAttachment = nullptr;
    sineStretchAttachment = nullptr;
    attackAttachment = nullptr;
    //[/Destructor_pre]

    spectrum_canvas = nullptr;
    blockSize = nullptr;
    blockSize2 = nullptr;
    leftCutoffSlider = nullptr;
    rightCutoffSlider = nullptr;
    sineStretchSlider = nullptr;
    attackSlider = nullptr;
    juce__toggleButton = nullptr;
    sineStretchSlider2 = nullptr;
    juce__label = nullptr;
    juce__label2 = nullptr;
    juce__label3 = nullptr;
    juce__label4 = nullptr;
    juce__label5 = nullptr;
    sineStretchSlider3 = nullptr;
    juce__label6 = nullptr;


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
        int x = 4, y = 4, width = 444, height = 348;
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

    if (sliderThatWasMoved == leftCutoffSlider.get())
    {
        //[UserSliderCode_leftCutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_leftCutoffSlider]
    }
    else if (sliderThatWasMoved == rightCutoffSlider.get())
    {
        //[UserSliderCode_rightCutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_rightCutoffSlider]
    }
    else if (sliderThatWasMoved == sineStretchSlider.get())
    {
        //[UserSliderCode_sineStretchSlider] -- add your slider handling code here..
        //[/UserSliderCode_sineStretchSlider]
    }
    else if (sliderThatWasMoved == attackSlider.get())
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == sineStretchSlider2.get())
    {
        //[UserSliderCode_sineStretchSlider2] -- add your slider handling code here..
        //[/UserSliderCode_sineStretchSlider2]
    }
    else if (sliderThatWasMoved == sineStretchSlider3.get())
    {
        //[UserSliderCode_sineStretchSlider3] -- add your slider handling code here..
        //[/UserSliderCode_sineStretchSlider3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == juce__toggleButton.get())
    {
        //[UserButtonCode_juce__toggleButton] -- add your button handler code here..
        //[/UserButtonCode_juce__toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    blockSize->setText(juce::String(audioProcessor.rendering.lastSampleRate.get()), juce::sendNotificationAsync);
    blockSize2->setText(juce::String(audioProcessor.rendering.lastMaskDiff.get()), juce::sendNotificationAsync);
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
                 fixedSize="0" initialWidth="444" initialHeight="348">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="4 4 444 348" fill="solid: 21ffffff" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="spectrum_canvas" id="c28ba59d3075a746" memberName="spectrum_canvas"
                    virtualName="" explicitFocusOrder="0" pos="144 24 288 200" class="SpectrumCanvas"
                    params=""/>
  <LABEL name="new label" id="41486794b98566e2" memberName="blockSize"
         virtualName="" explicitFocusOrder="0" pos="280 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fd9332144ef16970" memberName="blockSize2"
         virtualName="" explicitFocusOrder="0" pos="384 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="leftCutoffSlider" id="110eb12e1151856" memberName="leftCutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="224 240 128 88" min="1.0"
          max="20000.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="rightCutoffSlider" id="f5f11eb2404957fc" memberName="rightCutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="336 240 128 88" min="1.0"
          max="20000.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="sineStretchSlider" id="f56ba4a089565a1e" memberName="sineStretchSlider"
          virtualName="" explicitFocusOrder="0" pos="0 8 128 88" min="0.01"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="sineStretchSlider" id="ab103c844f994ea3" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="0 104 128 88" min="0.0"
          max="0.999" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="1d2e5d0b4ed829bd" memberName="juce__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="8 216 120 24" buttonText="Dynamic filter"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <SLIDER name="sineStretchSlider" id="8781b1d7d0cf8163" memberName="sineStretchSlider2"
          virtualName="" explicitFocusOrder="0" pos="0 240 128 88" tooltip="few ew few few few fwe fewf wef ewf ew"
          min="0.01" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Left cutoff" id="8620c0632c450024" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="216 320 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Left cutoff" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Right cutoff" id="40b2fd643a5430b4" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="328 320 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Right cutoff" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Filter strength" id="f0af7ab8cc3ea80f" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="0 80 128 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Filter strength" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Split strength" id="692de3b7b1d976e" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="16 184 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Split strength" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Attack" id="2459ebcb1b75d0a3" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="16 320 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="sineStretchSlider" id="cdc302d03b5071d1" memberName="sineStretchSlider3"
          virtualName="" explicitFocusOrder="0" pos="112 240 128 88" tooltip="few ew few few few fwe fewf wef ewf ew"
          min="0.01" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Random" id="8052689b5ca1ad00" memberName="juce__label6"
         virtualName="" explicitFocusOrder="0" pos="128 320 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Random" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

