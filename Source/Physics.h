/*
  ==============================================================================

    Physics.h
    Created: 3 Aug 2018 3:43:46pm
    Author:  Theo

  ==============================================================================
*/

#pragma once
#include "PhysicsUtilities.h"

#include "Particle.h"
#include "Spring.h"

class Physics
{
public:
	Physics();
	void simulate();

	double noteToFreq(String whichNote);
	double posToFreq(double position);
	int noteToCents(String whichNote);
	int freqToCents(double whichFreq);
	double centsToFreq(int whichNote);
	int ratioToCents(double ratio);

	void toggleSpring();

	void addParticle(int noteIndex);
	void removeParticle(int removeIndex);
	void addNote(int noteIndex);
	void removeNote(int noteIndex);
	void toggleNote(int noteIndex);

	void updateNotes();
	void updateFreq();

	void addSpring(Spring* s);
	void removeSpring(Spring* s);
	void addSpringsByNote(int addIndex);
	void removeSpringsByNote(int removeIndex);
	void addSpringsByInterval(double interval);
	void removeSpringsByInterval(double interval);
	void adjustSpringsByInterval(double interval, double stiffness);

	double getFrequency(int index);
	bool pitchEnabled(int index);

	void print();

private:
	const String intervalLabels[12] = {"minor second",
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
	String notesInAnOctave[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	const int octaves[1] = { 4 }; //will return to when adding more octaves
	const double cFreq = 261.6255653;
	const double tuningArray[12] = {25.0 / 24.0, 9.0 / 8.0, 6.0 / 5.0, 5.0 / 4.0, 
		4.0 / 3.0, 45.0 / 32.0, 3.0 / 2.0, 8.0 / 5.0, 5.0 / 3.0, 9.0 / 5.0, 15.0 / 8.0, 2.0};

	OwnedArray<Particle> particleArray;
    OwnedArray<Spring> springArray;
};
