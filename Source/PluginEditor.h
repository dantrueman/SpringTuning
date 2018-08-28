/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SpringTuningAudioProcessorEditor  : public KeyListener, public AudioProcessorEditor, private Timer, private Slider::Listener
{
public:
    SpringTuningAudioProcessorEditor (SpringTuningAudioProcessor&);
    ~SpringTuningAudioProcessorEditor();

    //==============================================================================
    
    void drawParticle(Graphics& g);
    
    void paint (Graphics&) override;
    void resized() override;
	bool keyPressed(const KeyPress& e, Component*) override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpringTuningAudioProcessor& processor;
    
    int counter;
    void timerCallback(void) override;
    
    int getNoteFromKeycode(int keycode);
    
    OwnedArray<Slider> springSliders;
    OwnedArray<Slider> tetherSliders;
    OwnedArray<Label>  springLabels;
    OwnedArray<Label>  tetherLabels;
    
    int springIndices[12];
    int tetherIndices[12];
    
    
    void sliderValueChanged (Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpringTuningAudioProcessorEditor)
};
