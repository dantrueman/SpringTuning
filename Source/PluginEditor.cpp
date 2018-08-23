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

int SpringTuningAudioProcessorEditor::getNoteFromKeycode(int code)
{
    //keyboard setup is that keys a through j (2nd row on keyboard) represent white keys
    //keys w, e, t, y, u represent black keys

    if (code == 65) // key A, equals C
    {
        return 0;
    }
    else if (code == 87) // key W, equals C#
    {
        return 1;
    }
    else if (code == 83) // key S, equals D
    {
        return 2;
    }
    else if (code == 69) //key E, equals D#
    {
        return 3;
    }
    else if (code == 68) //key D, equals E
    {
        return 4;
    }
    else if (code == 70) //key F, equals F
    {
        return 5;
    }
    else if (code == 84) // key T, equals F#
    {
        return 6;
    }
    else if (code == 71) //key G, equals G
    {
        return 7;
    }
    else if (code == 89) //key Y, equals G#
    {
        return 8;
    }
    else if (code == 72) // key h, equals A
    {
        return 9;
    }
    else if (code == 85) // key u, equals A#
    {
        return 10;
    }
    else if (code == 74) // key j, equals B
    {
        return 11;
    }
}

bool SpringTuningAudioProcessorEditor::keyPressed(const KeyPress& e, Component*)
{
	int code = e.getKeyCode();
    
    DBG("key pressed: " + String(code));
    
    bool lock = e.getModifiers().isShiftDown();
    int note = getNoteFromKeycode(code);
    
    processor.notePressed(note, lock);

	return true;
}
