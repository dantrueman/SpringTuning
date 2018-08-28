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

class Physics : public ReferenceCountedObject
{
public:
	Physics();
	void simulate();
    
    float tetherWeight, springWeight;

	double noteToFreq(String whichNote);
	double posToFreq(double position);
	int noteToCents(String whichNote);
	int freqToCents(double whichFreq);
	double centsToFreq(int whichNote);
	int ratioToCents(double ratio);

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
    
    void setSpringWeight(int which, double weight);
    double getSpringWeight(int which);
    
    void setTetherSpringWeight(int which, double weight);
    double getTetherSpringWeight(int which);

	double getFrequency(int index);
	bool pitchEnabled(int index);

	void print();
	void printParticles();
	void printActiveParticles();
	void printActiveSprings();

	bool checkEnabledParticle(int index);

	double halfStepUp(double freq);
	double halfStepDown(double freq);
    
    Particle::PtrArr& getTetherParticles(void) { return tetherParticleArray;}
    Spring::PtrArr& getTetherSprings(void) { return tetherSpringArray;}
    
    Particle::PtrArr& getParticles(void) { return particleArray;}
    Spring::PtrArr& getSprings(void) { return springArray;}
    
    bool getTetherSpringEnabled(int which);
    bool getSpringEnabled(int which);
    
    String getTetherSpringName(int which);
    
    String getSpringName(int which);
    
    

private:
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
	String notesInAnOctave[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	const int octaves[1] = { 4 }; //will return to when adding more octaves
	const double cFreq = 261.6255653;
	const double halfStepRatio = 1.0595;
    
	const double tuningArray[13] = {1.0, //unison
		25.0 / 24.0,  //minor 2nd
		9.0 / 8.0, //major 2nd
		6.0 / 5.0, //minor 3rd
		5.0 / 4.0, //major 3rd
		4.0 / 3.0, //perfect 4th
		45.0 / 32.0, //diminished 5th
		3.0 / 2.0, //perfect 5th
		8.0 / 5.0, //minor 6th
		5.0 / 3.0, //major 6th
		9.0 / 5.0, //minor 7th
		15.0 / 8.0, //major 7th
		2.0}; //octave
     
    
    //const double tuningArray[13] = {1.0,  1.0595, 1.1125, 1.1893, 1.2601, 1.3351, 1.4144, 1.4986, 1.5877, 1.6822, 1.7823, 1.8883, 2.0 };

    Particle::PtrArr    particleArray;
    Spring::PtrArr      springArray; // efficiency fix: make this ordered by spring interval 
    
    Particle::PtrArr    tetherParticleArray;
    Spring::PtrArr      tetherSpringArray;
    
    
    
	int numNotes; // number of enabled notes
};
