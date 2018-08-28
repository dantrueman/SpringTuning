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
    
    for (int i = 0; i < 12; i++)
    {
        Slider* s = new Slider("t" + String(i));
    
        s->addListener(this);
        s->setSliderStyle(Slider::SliderStyle::LinearBar);
        s->setRange(0.0, 1.0);
        s->setValue(processor.physics.getTetherSpringWeight(i), dontSendNotification);
        tetherSliders.add(s);
        
        s = new Slider("s" + String(i));
        
        s->addListener(this);
        s->setSliderStyle(Slider::SliderStyle::LinearBar);
        s->setRange(0.0, 1.0);
        s->setValue(processor.physics.getSpringWeight(i), dontSendNotification);
        
        springSliders.add(s);
    }
    
    
    
    startTimerHz(30);
}


SpringTuningAudioProcessorEditor::~SpringTuningAudioProcessorEditor()
{
}


void SpringTuningAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    double value = slider->getValue();
    
    String name = slider->getName();
    
    for (int i = 0; i < 12; i++)
    {
        if (name == ("t"+String(i)))
        {
            processor.physics.setTetherSpringWeight(i, value);
            break;
        }
        else if (name == ("s"+String(i)))
        {
            processor.physics.setSpringWeight(i, 1.0 - value);
            break;
        }
    }
    

}


void SpringTuningAudioProcessorEditor::timerCallback(void)
{
    const int x_offset = 10;
    const int y_offset = 75;
    const int w = 150;
    const int h = 25;
    const int yspacing = 5;
    const int xspacing = 5;
    
    repaint();
    
    int sx = 0, tx = 0;
    DBG("~ ~ ~ ~ ~ ~ ~");
    for (int i = 0; i < 12; i++)
    {
        if (processor.physics.getTetherSpringEnabled(i))
        {
            addAndMakeVisible(tetherSliders[i]);
            tetherSliders[i]->setBounds(x_offset, y_offset + (h + yspacing) * tx++, w, h);
            //DBG("tspring: " + s->getName());
        }
        else
        {
            removeChildComponent(tetherSliders[i]);
        }
        
        if (processor.physics.getSpringEnabled(i))
        {
            addAndMakeVisible(springSliders[i]);
            springSliders[i]->setBounds(x_offset + w + xspacing, y_offset + (h + yspacing) * sx++, w, h);
            DBG("sspring" + String(i) + " : " + processor.physics.getSpringName(i));
        }
        else
        {
            removeChildComponent(springSliders[i]);
        }
    }
}

//==============================================================================
void SpringTuningAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::antiquewhite);

    g.setColour (Colours::black);
    g.setFont (40.0f);
    g.drawFittedText ("Spring Tuning", getLocalBounds(), Justification::centredTop, 1);
    
    g.setFont(20.0f);
    g.drawFittedText("Tethers", 10, 50, 150, 40, Justification::centredTop, 1);
    g.drawFittedText("Springs", 170, 50, 150, 40, Justification::centredTop, 1);
    
    g.setFont(12.0f);
    
    float midi,scalex,posx,radians,cx,cy;
    float centerx = getWidth() * 0.65f, centery = getHeight() * 0.5f, radius = jmin(getHeight() * 0.25, getWidth() * 0.25);
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
    
    for (auto p : processor.physics.getTetherParticles())
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
        }
    }
    
    for (auto p : processor.physics.getParticles())
    {
        if (p->getEnabled())
        {
            // DRAW PARTICLE IN MOTION
            midi = Utilities::clip(0, Utilities::ftom(p->getX()), 128);
            scalex = ((midi - 60.0f) / 12.0f);
            posx = scalex *  (getWidth() - 2*x_offset);
            
            radians = scalex * Utilities::twopi - Utilities::pi * 0.5;
            
            cx = centerx + cosf(radians) * radius - dimc * 0.5f;
            cy = centery + sinf(radians) * radius - dimc * 0.5f;
            
            g.setColour (Colours::black);
            g.fillEllipse(cx, cy, dimc, dimc);
            
            g.setColour (Colours::black);
            g.fillEllipse(x_offset + posx, getHeight() * 0.9, dimc, dimc);
        }
    }
}

void SpringTuningAudioProcessorEditor::resized()
{
    
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
    
    if (code == KeyPress::spaceKey)
    {
        processor.clear();
        return true;
    }

    int note = getNoteFromKeycode(code);
    
    if (note >= 0) processor.notePressed(note);

	return true;
}
