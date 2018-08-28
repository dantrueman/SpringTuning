/*
  ==============================================================================

    Spring.cpp
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "Spring.h"
#include "../JuceLibraryCode/JuceHeader.h"

Spring::Spring(Particle* firstPoint, Particle* secondPoint, double str, double interval, int index) :
	a(firstPoint),
	b(secondPoint),
	strength(str),
	baseInterval(interval),
	intervalIndex(index)
{

}

Particle* Spring::getA()
{
	return a;
}

Particle* Spring::getB()
{
	return b;
}

double Spring::getStrength()
{
	return strength;
}

double Spring::getBaseInterval()
{
	return baseInterval;
}

void Spring::setBaseInterval(double interval)
{
    baseInterval = interval;
}

int Spring::getIntervalIndex()
{
	return intervalIndex;
}

Spring Spring::copy()
{
	Spring copySpring(a, b, strength, baseInterval, intervalIndex);
	return copySpring;
}

bool Spring::compare(Spring* that)
{
	return (a->compare(that->getA()) &&
		b->compare(that->getB()) &&
		strength == that->getStrength() &&
		baseInterval == that->getBaseInterval());
}

void Spring::print()
{
	DBG("Point A:");
	a->print();
	DBG("\nPoint B:");
	b->print();
	DBG("Strength: " + String(strength));
	DBG("Base Interval: " + String(baseInterval));
}

void Spring::setStrength(double newStrength)
{
	strength = newStrength;
}

/*
String Spring::getStringBaseInterval()
{
	String result = "";
	switch (baseInterval) 
	{
	case (double)(25.0 / 24.0) :
		result = "Minor 2nd";
		break;

	case 9.0/8.0:
		result = "Major 2nd";
		break;

	case 6.0/5.0:
		result = "Minor 3rd";
		break;

	case 5.0/4.0:
		result = "Major 3rd";
		break;

	case 4.0/3.0:
		result = "Perfect 4th";
		break;

	case 45.0/32.0:
		result = "Diminished 5th";
		break;

	case 3.0/2.0:
		result = "Perfect 5th";
		break;
	
	case 8.0/5.0:
		result = "Minor 6th";
		break;

	case 5.0/3.0:
		result = "Major 6th";
		break;

	case 9.0/5.0:
		result = "Minor 7th";
		break;

	case 15.0/8.0:
		result = "Major 7th";
		break;

	case 2.0:
		result = "Octave";
		break;
	}
	return result;
}
*/

//still needs tweaking
void Spring::satisfyConstraints(double distance)
{
	//DBG("Satisfying constraints for " + String(distance) + " distance \n Printing points:");
	double diff = b->getX() - a->getX();
	if (diff == 0.0) return;
    
    const double maxStiffness = 0.5;
    const double meanStiffness = 0.05;

    diff *= ((diff - distance) / diff) * Utilities::clip(0.0, (meanStiffness * strength) / (1.0 - strength), maxStiffness);
    
    if (!a->getLocked())
    {
        a->addX(diff);
    }

    if (!b->getLocked())
    {
        b->subX(diff);
    }

}

void Spring::update()
{
	/*
	Verlet function
	protected void update(boolean applyConstraints) {
        Vec2D delta = b.sub(a);
        // add minute offset to avoid div-by-zero errors
        float dist = delta.magnitude() + EPS;
        float normDistStrength = (dist - restLength)
                / (dist * (a.invWeight + b.invWeight)) * strength;
        if (!a.isLocked && !isALocked) {
            a.addSelf(delta.scale(normDistStrength * a.invWeight));
            if (applyConstraints) {
                a.applyConstraints();
            }
        }
        if (!b.isLocked && !isBLocked) {
            b.addSelf(delta.scale(-normDistStrength * b.invWeight));
            if (applyConstraints) {
                b.applyConstraints();
            }
        }
    }

	*/
}
