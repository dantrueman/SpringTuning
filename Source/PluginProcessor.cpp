/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpringTuningAudioProcessor::SpringTuningAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

SpringTuningAudioProcessor::~SpringTuningAudioProcessor()
{
}

//==============================================================================
void SpringTuningAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < 12; i++)
    {
        osc[i].setSampleRate(sampleRate);
        osc[i].setHarmonics(15);
        osc[i].setFrequency(stk::Midi2Pitch[48 + i]);
    }
}

// Get data from Spring tuning model and set frequencies / amplitudes of osc
void SpringTuningAudioProcessor::block(void)
{
    // Run physics simulation
    physics.simulate();
    
    // GET FREQUENCIES FROM SPRING TUNING
    for (int i = 0; i < 12; ++i)
    {
        osc[i].setFrequency(physics.getFrequency(i));
    }
}

float SpringTuningAudioProcessor::tick(float sample)
{
    sample = 0.0f;
    
    for (int i = 0; i < 12; i++)
    {
        // if osc is on, tick here, if not dont
		if (physics.pitchEnabled(i)) sample += osc[i].tick();
    }
    
    sample /= 12.0f;

	//physics.print();
    
    return sample;
}

void SpringTuningAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    // Clear left and right channels
    buffer.clear (0, 0, buffer.getNumSamples());
    buffer.clear (1, 0, buffer.getNumSamples());

    float sample = 0.0f;
    
    auto* left = buffer.getWritePointer (0);
    auto* right = buffer.getWritePointer (1);
    
    for (auto i = 0; i < buffer.getNumSamples(); ++i)
    {
        sample = tick((left[i] + right[i]) * 0.5);
        left[i] = sample;
        right[i] = left[i];
    }
    

	MidiMessage m;
	int time;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		int noteNumber = (m.getNoteNumber() % 12) + 60;
		DBG("message at " + String(noteNumber));
		if (m.isNoteOn())
		{
			DBG("note on, toggling note");
			physics.toggleNote(noteNumber);
			physics.print();
		}
		else DBG("note off, doing nothing");
	}
    
}

bool SpringTuningAudioProcessor::keyPressed(const KeyPress& e, Component*)
{
	DBG("key has been pressed");

	int code = e.getKeyCode();

	//keyboard setup is that keys a through j (2nd row on keyboard) represent white keys
	//keys w, e, t, y, u represent black keys

	if (code == 65) // key A, equals C
	{
		physics.toggleNote(0);
	}
	else if (code == 87) // key W, equals C#
	{
		physics.toggleNote(1);
	}
	else if (code == 83) // key S, equals D
	{
		physics.toggleNote(2);
	}
	else if (code == 69) //key E, equals D#
	{
		physics.toggleNote(3);
	}
	else if (code == 68) //key D, equals E
	{
		physics.toggleNote(4);
	}
	else if (code == 70) //key F, equals F
	{
		physics.toggleNote(5);
	}
	else if (code == 84) // key T, equals F#
	{
		physics.toggleNote(6);
	}
	else if (code == 71) //key G, equals G
	{
		physics.toggleNote(7);
	}
	else if (code == 89) //key Y, equals G#
	{
		physics.toggleNote(8);
	}
	else if (code == 72) // key h, equals A
	{
		physics.toggleNote(9);
	}
	else if (code == 85) // key u, equals A#
	{
		physics.toggleNote(10);
	}
	else if (code == 74) // key j, equals B
	{
		physics.toggleNote(11);
	}

	return true;
}


//==============================================================================
bool SpringTuningAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpringTuningAudioProcessor::createEditor()
{
    return new SpringTuningAudioProcessorEditor (*this);
}

//==============================================================================
void SpringTuningAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SpringTuningAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpringTuningAudioProcessor();
}

void SpringTuningAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpringTuningAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

//==============================================================================
const String SpringTuningAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpringTuningAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SpringTuningAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SpringTuningAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SpringTuningAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpringTuningAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SpringTuningAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpringTuningAudioProcessor::setCurrentProgram (int index)
{
}

const String SpringTuningAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpringTuningAudioProcessor::changeProgramName (int index, const String& newName)
{
}


