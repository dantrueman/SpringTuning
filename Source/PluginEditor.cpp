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
}

SpringTuningAudioProcessorEditor::~SpringTuningAudioProcessorEditor()
{
}

//==============================================================================
void SpringTuningAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void SpringTuningAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

bool SpringTuningAudioProcessorEditor::keyPressed(const KeyPress& e, Component*)
{
	DBG("key has been pressed");

	int code = e.getKeyCode();

	processor.adjustNoteFromKeycode(code);

	return true;
}