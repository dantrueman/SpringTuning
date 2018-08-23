/*
  ==============================================================================

    PhysicsUtilities.h
    Created: 10 Aug 2018 12:26:55pm
    Author:  airship

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define INV_440 0.00227272727f

class Utilities
{
public:
    static float ftom(float f)
    {
        return (69.0f + 12.0f * log2(f * INV_440));
    }
    
	static double noteToFreq(String whichNote)
	{
		int noteIndex = 60;
		//int noteIndex = Array::indexOf(notesInAnOctave, whichNote); // will eventually need to change
		return (double)(cFreq * pow(2.0, noteIndex / 12.0)); // will need to change when multiple octaves are added
	}

	//need to changec
	static double posToFreq(double position)
	{
		double noteValue = 60.0 + position;
		return (double)(cFreq * pow(2.0, noteValue / 12.0)) / 32; // will need to change when multiple octaves are added
	}

	static int noteToCents(String whichNote)
	{
		return (int)(freqToCents(noteToFreq(whichNote)));
	}
	static int freqToCents(double whichFreq)
	{
		return (int)(ratioToCents(whichFreq / cFreq));
	}
	static double centsToFreq(int centsFromC)
	{
		return cFreq * pow(2, centsFromC / 1200.0);
	}
	static int ratioToCents(double ratio)
	{
		return 1200 * log(ratio) / log(2);
	}
	static double halfStepUp(double freq)
	{
		return freq * halfStepRatio;
	}
	static double halfStepDown(double freq)
	{
		return freq / halfStepRatio;
	}

    constexpr static const float pi = 3.14159265359f;
    constexpr static const float twopi = 6.28318530718f;
	constexpr static const double cFreq = 261.6255653;
	constexpr static const double halfStepRatio = 1.0595;
	constexpr static const int octaves[1] = { 4 }; //will return to when adding more octaves

	const String notesInAnOctave[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

	const String intervalLabels[13] = {
		"unison",
		"minor second",
		"major second",
		"minor third",
		"major third",
		"perfect fourth",
		"dimished fifth",
		"perfect fifth",
		"minor sixth",
		"major sixth",
		"minor seventh",
		"major seventh",
		"octave"
	};

	constexpr static const double tunings[6][13] = {
		{1 / 1, 16 / 15, 9 / 8, 6 / 5, 5 / 4, 4 / 3, 45 / 32, 3 / 2, 8 / 5, 5 / 3, 9 / 5, 15 / 8, 2 / 1}, // common just
		{1.0,  1.0595, 1.1125, 1.1893, 1.2601, 1.3351, 1.4144, 1.4986, 1.5877, 1.6822, 1.7823, 1.8883, 2.0 }, // equal tempered
		{1 / 1, 16 / 15, 9 / 8, 6 / 5, 5 / 4, 4 / 3, 1.41421356237, 3 / 2, 8 / 5, 5 / 3, 16 / 9, 15 / 8, 2 / 1}, // symmetric
		{1 / 1, 17 / 16, 9 / 8, 19 / 16, 5 / 4, 21 / 16, 11 / 8, 3 / 2, 13 / 8, 27 / 16, 7 / 4, 15 / 8, 2 / 1}, // overtone
		{1 / 1, 567 / 512, 9 / 8, 147 / 128, 21 / 16, 1323 / 1024, 189 / 128, 3 / 2, 49 / 32, 7 / 4, 441 / 256, 63 / 32, 2 / 1}, // well tuned piano
		{1 / 1, 256 / 243, 9 / 8, 32 / 27, 81 / 64, 4 / 3, 729 / 512, 3 / 2, 128 / 81, 27 / 16, 16 / 9, 243 / 128, 2 / 1} }; //pythagorean
    
private:
    Utilities () {};
};

