/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpringTuningAudioProcessorEditor::SpringTuningAudioProcessorEditor (SpringTuningAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
}

SpringTuningAudioProcessorEditor::~SpringTuningAudioProcessorEditor()
{
}

//==============================================================================
void SpringTuningAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::antiquewhite);

    g.setColour (Colours::black);
    g.setFont (40.0f);
    g.drawFittedText ("Spring Tuning", getLocalBounds(), Justification::centred, 1);
}

void SpringTuningAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

bool SpringTuningAudioProcessorEditor::keyPressed(const KeyPress& e, Component*)
{
	int code = e.getKeyCode();
    
    DBG("key pressed: " + String(code));

	processor.adjustNoteFromKeycode(code);

	return true;
}
