/*
  ==============================================================================

    Physics.cpp
    Created: 3 Aug 2018 3:43:46pm
    Author:  Theo

  ==============================================================================
*/

#include "Physics.h"
#include "PhysicsUtilities.h"

using namespace std;

Physics::Physics(void)
{
	double defaultStrength = 0.2;
    
    particleArray.ensureStorageAllocated(12);

	double xValue = Utilities::cFreq;

	for (int i = 0; i < 12; i++)
	{
        Particle* particle = new Particle(xValue, 0.0, 1.0);
        particle->setEnabled(false);
        particleArray.add(particle);
		xValue *= Utilities::halfStepRatio;
	}

	//DBG("xValue: " + String(xValue) + ", cFreq: " + String(cFreq));

    springArray.ensureStorageAllocated(100);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < i; j++)
		{
			//will add in a better length calculation method once mapping is figured out
            Spring* spring = new Spring(particleArray[j],
                                        particleArray[i],
                                        particleArray[i]->getX() - particleArray[j]->getX(),
                                        defaultStrength, Utilities::tunings[0][i - j], i - j);
            spring->setEnabled(false);
            springArray.add(spring);
		}
	}

	numNotes = 0;
};
void Physics::simulate()
{
    for (auto particle : particleArray)
    {
		if (particle->getEnabled()) particle->integrate();
	}

	for (auto spring : springArray)
	{
		if (spring->getEnabled())
		{
			bool a = spring->isALocked();
			bool b = spring->isBLocked();
			double distance;

			// if both are locked do not integrate
			if (!(a && b))
			{
				// if neither are locked or just a is locked base the distance off of a
				if (!b) distance = spring->getA()->getX() * Utilities::tunings[0][spring->getIntervalIndex()] - spring->getA()->getX();
				// if b is locked and a is unlocked base the distance off of b
				else distance = spring->getB()->getX() - spring->getB()->getX() / Utilities::tunings[0][spring->getIntervalIndex()];

				spring->satisfyConstraints(distance);
			}

			
		}
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

void Physics::toggleSpring()
{
	//tbd
}

void Physics::addParticle(int index)
{
    particleArray[index]->setEnabled(true);
	numNotes++;
}
void Physics::removeParticle(int index)
{
    particleArray[index]->setEnabled(false);
	numNotes--;
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

void Physics::removeAllNotes(void)
{
    for (int i = 0; i < 12; i++) removeNote(i);
}
void Physics::toggleNote(int noteIndex)
{
	int convertedIndex = noteIndex % 12; // just in case a midi value is passed accidentally
	//DBG("calling " + String(convertedIndex) + " in toggleNote()");
	if (particleArray[convertedIndex]->getEnabled())
	{
		//DBG("Removing " + notesInAnOctave[convertedIndex] + " from list.");
		removeNote(convertedIndex);
	}
	else
	{
		//DBG("Adding " + notesInAnOctave[convertedIndex] + " to list.");
		addNote(convertedIndex);
	}
}



void Physics::toggleTetherForNote(int note)
{
    Particle* p = particleArray[note];
    
    if (p->getLocked())
    {
        p->unlock();
    }
    else
    {
        p->lock();
        p->setX(Utilities::cFreq * Utilities::tunings[0][note]);
        
    }
}

//probably not necessary until UI?
void Physics::updateNotes()
{
	//tbd
}

//probably not necessary until UI?
void Physics::updateFreq()
{
	//tbd
}

void Physics::addSpring(Spring* s)
{
    s->setEnabled(true);
}

void Physics::removeSpring(Spring* s)
{
    s->setEnabled(false);
    
}
void Physics::addSpringsByNote(int addIndex)
{
    Particle* p = particleArray[addIndex];
    for (auto spring : springArray)
    {
        Particle* particleA = spring->getA();
        Particle* particleB = spring->getB();
        
		if (!spring->getEnabled())
        {
			// sets the spring to enabled if one spring matches the index and the other is enabled
			if (particleA->compare(p))
			{
				if (particleB->getEnabled()) spring->setEnabled(true);
			}
			else if (particleB->compare(p))
			{
				if (particleA->getEnabled()) spring->setEnabled(true);
			}
        }
	}
}
void Physics::removeSpringsByNote(int removeIndex)
{
	Particle* p = particleArray[removeIndex];
	for (auto spring : springArray)
	{
        Particle* particleA = spring->getA();
        Particle* particleB = spring->getB();
        
		if (spring->getEnabled() && (particleA->compare(p) || particleB->compare(p)))
        {
            spring->setEnabled(false);
        }
	}
}
void Physics::addSpringsByInterval(double interval)
{
	for (auto spring : springArray)
	{
        if (!spring->getEnabled() && (abs(spring->getBaseInterval() - interval) <= 0.001))
        {
            spring->setEnabled(true);
        }
	}
}
void Physics::removeSpringsByInterval(double interval)
{
    for (auto spring : springArray)
	{
        if (spring->getEnabled() && (abs(spring->getBaseInterval() - interval) <= 0.001))
        {
            spring->setEnabled(false);
        }
	}
}
void Physics::adjustSpringsByInterval(double interval, double stiffness)
{
	for (auto spring : springArray)
	{
		if (((abs(spring->getBaseInterval() - interval)) <= 0.001))
        {
            spring->setStrength(stiffness);
        }
	}
}

double Physics::getFrequency(int index)
{
	return particleArray[index]->getX();
}

bool Physics::pitchEnabled(int index)
{
	return particleArray[index]->getEnabled();
}

void Physics::print()
{
	for (int i = 0; i < 12; i++)
	{
		String printStatus = "";
		if (particleArray[i]->getEnabled()) printStatus = " (enabled)";
		else printStatus = " (disabled)";
		//DBG(notesInAnOctave[i] + " = " + String(getFrequency(i)) + printStatus);
	}
}

void Physics::printParticles()
{
	for (int i = 0; i < 12; i++)
	{
		particleArray[i]->print();
	}
}

void Physics::printActiveParticles()
{
	for (int i = 0; i < 12; i++)
	{
		if (particleArray[i]->getEnabled()) particleArray[i]->print();
	}
}

void Physics::printActiveSprings()
{
	for (auto spring : springArray)
	{
		if (spring->getEnabled()) spring->print();
	}
}

bool Physics::checkEnabledParticle(int index)
{
	return particleArray[index]->getEnabled();
}
