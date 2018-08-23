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
    setSize (800, 600);
    
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    startTimerHz(30);
    
}



SpringTuningAudioProcessorEditor::~SpringTuningAudioProcessorEditor()
{
}

void SpringTuningAudioProcessorEditor::timerCallback(void)
{
    repaint();
}

//==============================================================================
#define X_OFFSET 50
#define SPACING 2.0f
void SpringTuningAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::antiquewhite);

    g.setColour (Colours::black);
    g.setFont (40.0f);
    g.drawFittedText ("Spring Tuning", getLocalBounds(), Justification::centredTop, 1);
    
    for (int i = 0; i < 12; i++)
    {
        Particle* p = processor.physics.getParticle(i);
        
        if (p->getEnabled())
        {
            float midi = Utilities::ftom(p->getX());
            float scalex = ((midi - 60.0f) / 12.0f);
            float posx = scalex *  (getWidth() - 2*X_OFFSET);
            
            float radians = scalex * Utilities::twopi;
            float radius = 175;
            float centerx = getWidth() * 0.5f, centery = getHeight() * 0.5f;
            
            float cx = centerx + cosf(radians) * radius - 18;
            float cy = centery + sinf(radians) * radius - 18;
            
            if (p->getLocked())
            {
                g.setColour (Colours::black);
                g.fillEllipse(cx, cy, 36, 36);
                
                g.setColour (Colours::dimgrey);
                g.fillEllipse(X_OFFSET + posx - 3, getHeight() * 0.9 - 3, 36, 36);
            }
            else
            {
                g.setColour (Colours::black);
                g.drawEllipse(cx, cy, 30, 30, 6);
                
                g.setColour (Colours::dimgrey);
                g.drawEllipse(X_OFFSET + posx, getHeight() * 0.9, 30, 30, 6);
            }
            
            if (++counter > 100)
            {
                counter = 0;
                DBG("midi: " + String(midi));
                DBG("scalex: " + String(scalex));
                DBG("posx: " + String(posx));
            }
        }
    }
    
    
    
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
    
    return -1;
}

bool SpringTuningAudioProcessorEditor::keyPressed(const KeyPress& e, Component*)
{
	int code = e.getKeyCode();
    
    DBG("key pressed: " + String(code));
    
    if (code == KeyPress::spaceKey)
    {
        processor.clear();
        return true;
    }
    
    bool lock = e.getModifiers().isShiftDown();
    int note = getNoteFromKeycode(code);
    
    if (note >= 0) processor.notePressed(note, lock);

	return true;
}
