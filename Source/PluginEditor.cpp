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
    
    addAndMakeVisible(springWeightSlider);
    springWeightSlider.addListener(this);
    springWeightSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    springWeightSlider.setName("Spring Weight");
    springWeightSlider.setRange(0.0, 1.0);
    
    addAndMakeVisible(tetherWeightSlider);
    tetherWeightSlider.addListener(this);
    tetherWeightSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    tetherWeightSlider.setName("Tether Weight");
    tetherWeightSlider.setRange(0.0, 1.0);
    
    startTimerHz(30);
}


SpringTuningAudioProcessorEditor::~SpringTuningAudioProcessorEditor()
{
}


void SpringTuningAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    double value = slider->getValue();
    
    if (slider == &tetherWeightSlider)
    {
        processor.physics.tetherWeight = value;
    }
    else if (slider == &springWeightSlider)
    {
        processor.physics.springWeight = value;
        
        
    }
}

void SpringTuningAudioProcessorEditor::timerCallback(void)
{
    repaint();
}

//==============================================================================
void SpringTuningAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::antiquewhite);

    g.setColour (Colours::black);
    g.setFont (40.0f);
    g.drawFittedText ("Spring Tuning", getLocalBounds(), Justification::centredTop, 1);
    
    float midi,scalex,posx,radians,cx,cy;
    float centerx = getWidth() * 0.5f, centery = getHeight() * 0.5f, radius = jmin(getHeight() * 0.25, getWidth() * 0.25);
    float dimc = jmin(getHeight() * 0.05, getWidth() * 0.05);
    int x_offset = 0.075 * getWidth();
    
    for (auto s : processor.physics.getSprings())
    {
        if (s->getEnabled())
        {
            Particle* a = s->getA();
            midi = Utilities::ftom(a->getX());
            scalex = ((midi - 60.0f) / 12.0f);
            
            radians = scalex * Utilities::twopi - Utilities::pi * 0.5;
            
            float cxa = centerx + cosf(radians) * radius;
            float cya = centery + sinf(radians) * radius;
            
            
            Particle* b = s->getB();
            midi = Utilities::ftom(b->getX());
            scalex = ((midi - 60.0f) / 12.0f);
            
            radians = scalex * Utilities::twopi - Utilities::pi * 0.5;
            
            float cxb = centerx + cosf(radians) * radius;
            float cyb = centery + sinf(radians) * radius;
            
            g.setColour(Colours::dimgrey);
            g.drawLine(cxa, cya, cxb, cyb);
        }
    }
    
    for (auto p : processor.physics.getParticles())
    {
        if (p->getEnabled())
        {
            // DRAW REST PARTICLE
            midi = Utilities::ftom(p->getRestX());
            scalex = ((midi - 60.0f) / 12.0f);
            posx = scalex *  (getWidth() - 2*x_offset);
            
            radians = scalex * Utilities::twopi - Utilities::pi * 0.5;
            
            cx = centerx + cosf(radians) * radius - dimc * 0.5f;
            cy = centery + sinf(radians) * radius - dimc * 0.5f;
            
            g.setColour (Colours::grey);
            g.fillEllipse(cx, cy, dimc, dimc);
            
            // DRAW PARTICLE IN MOTION
            midi = Utilities::ftom(p->getX());
            scalex = ((midi - 60.0f) / 12.0f);
            posx = scalex *  (getWidth() - 2*x_offset);
            
            radians = scalex * Utilities::twopi - Utilities::pi * 0.5;
            
            cx = centerx + cosf(radians) * radius - dimc * 0.5f;
            cy = centery + sinf(radians) * radius - dimc * 0.5f;
            
            g.setColour (Colours::black);
            g.fillEllipse(cx, cy, dimc, dimc);
            
            g.setColour (Colours::black);
            g.fillEllipse(x_offset + posx, getHeight() * 0.9, dimc, dimc);
   
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
    tetherWeightSlider.setBounds(10, 50, 200, 50);
    springWeightSlider.setBounds(10, 105, 200, 50);
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

    int note = getNoteFromKeycode(code);
    
    if (note >= 0) processor.notePressed(note);

	return true;
}
