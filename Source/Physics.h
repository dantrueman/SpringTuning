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

	void toggleSpring();

	void addParticle(int noteIndex);
	void removeParticle(int removeIndex);
    
    Particle* getParticle(int note) { return particleArray[note];}
    
	void addNote(int noteIndex);
	void removeNote(int noteIndex);
    void removeAllNotes(void);
	void toggleNote(int noteIndex);
    
    void toggleTetherForNote(int note);

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
	void printParticles();
	void printActiveParticles();
	void printActiveSprings();

	bool checkEnabledParticle(int index);

private:

	OwnedArray<Particle> particleArray;
    OwnedArray<Spring> springArray;
	int numNotes; // number of enabled notes
};
