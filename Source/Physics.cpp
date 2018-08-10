/*
  ==============================================================================

    Physics.cpp
    Created: 3 Aug 2018 3:43:46pm
    Author:  Theo

  ==============================================================================
*/

#include "Physics.h"

using namespace std;

Physics::Physics() :
{

	double defaultStrength = 0.2;

	for (int i = 0; i < 12; i++)
	{
		Particle p(i, 0.0, 1.0);
		particleArray[i] = p;
		particleEnabled[i] = false;
	}

	int index = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < i; j++)
		{
			//will add in a better length calculation method once mapping is figured out
			Spring s(particleArray[i], particleArray[j], i - j, defaultStrength);
			springArray[index] = s;
			springEnabled[index] = false;
			index++;
		}
	}
};
void Physics::simulate()
{
	for (int i = 0; i < 12; i++)
	{
		if (particleEnabled[i]) particleArray[i].integrate();
	}
	//something about distance, integrating particles


	//Aatish's function
	/*
	function simulate() {
  for ( particles = cloth.particles, i = 0, il = particles.length ; i < il; i ++ )
  {
    particle = particles[ i ];
    particle.integrate( TIMESTEP_SQ ); // performs verlet integration
  }
  // Start constraints
  constraints = cloth.constraints,
  il = constraints.length;
  for ( i = 0; i < il; i ++ ) {
    constraint = constraints[ i ];
    satisfyconstraints( constraint[ 0 ], constraint[ 1 ], constraint[ 2 ], constraint[ 3] );
 }
	*/
}

double Physics::noteToFreq(String whichNote)
{
	int lowestNote = 60; //need to check my math
	int noteIndex = Array::IndexOf(notesInAnOctave, whichNote); // will eventually need to change
	return (double)(cFreq * pow(2.0, noteIndex / 12.0)); // will need to change when multiple octaves are added
}
int Physics::noteToCents(String whichNote)
{
	return (int)(freqToCents(noteToFreq(whichNote)));
}
int Physics::freqToCents(double whichFreq)
{
	return (int)(ratioToCents(whichFreq / cFreq));
}
double Physics::centsToFreq(int centsFromC)
{
	return cFreq * pow(2, centsFromC / 1200.0);
}
int Physics::ratioToCents(double ratio)
{
	return 1200 * log(ratio) / log(2);
}

void Physics::toggleSpring()
{
	//tbd
}

void Physics::addParticle(int noteIndex)
{
	if (!particleEnabled[noteIndex]) particleEnabled[noteIndex] = true;
}
void Physics::removeParticle(int removeIndex)
{
	if (particleEnabled[removeIndex]) particleEnabled[removeIndex] = false;
}
void Physics::addNote(int noteIndex)
{
	addParticle(noteIndex);
	addSpringsByNote(noteIndex);
}
void Physics::removeNote(int noteIndex)
{
	removeParticle(noteIndex);
	removeSpringsByNote(noteIndex);
}

void Physics::updateNotes()
{
	//tbd
}

void Physics::updateFreq()
{
	//tbd
}

void Physics::addSpring(Spring s)
{
	int index = Array::IndexOf(springArray, s);
	if (!springEnabled[index]) springEnabled[index] = true;
}

void Physics::removeSpring(Spring s)
{
	int index = Array::IndexOf(springArray, s);
	if (springEnabled[index]) springEnabled[index] = false;
}
void Physics::addSpringsByNote(int addIndex)
{
	Particle p = particleArray[addIndex];
	for (int i = 0; i < 65; i++) //I need to set a variable for number of springs
	{
		Spring s = springArray[i];
		if ((s.getA().compare(p) || s.getB().compare(p)) && !springEnabled[i]) springEnabled[i] = true;
	}
}
void Physics::removeSpringsByNote(int removeIndex)
{
	Particle p = particleArray[removeIndex];
	for (int i = 0; i < 65; i++) //I need to set a variable for number of springs
	{
		Spring s = springArray[i];
		if ((s.getA().compare(p) || s.getB().compare(p)) && springEnabled[i]) springEnabled[i] = false;
	}
}
void Physics::addSpringsByInterval(double interval)
{
	for (int i = 0; i < 65; i++) //I need to set a variable for number of springs
	{
		Spring s = springArray[i];
		if ((abs(s.getBaseInterval() - interval) <= 0.001) && !springEnabled[i]) springEnabled[i] = true;
	}
}
void Physics::removeSpringsByInterval(double interval)
{
	for (int i = 0; i < 65; i++) //I need to set a variable for number of springs
	{
		Spring s = springArray[i];
		if ((abs(s.getBaseInterval() - interval) <= 0.001) && springEnabled[i]) springEnabled[i] = false;
	}
}
void Physics::adjustSpringsByInterval(double interval, double stiffness)
{
	for (int i = 0; i < 65; i++) //I need to set a variable for number of springs
	{
		Spring s = springArray[i];
		if (((abs(s.getBaseInterval() - interval)) <= 0.001)) s.setStrength(stiffness);
	}
}