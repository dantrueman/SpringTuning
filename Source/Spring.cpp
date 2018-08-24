/*
  ==============================================================================

    Spring.cpp
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "Spring.h"
#include "../JuceLibraryCode/JuceHeader.h"

Spring::Spring(Particle* firstPoint, Particle* secondPoint, double length, double str, double interval, int index) :
	a(firstPoint),
	b(secondPoint),
	springLength(length),
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

double Spring::getLength()
{
	return springLength;
}

double Spring::getStrength()
{
	return strength;
}

double Spring::getBaseInterval()
{
	return baseInterval;
}

int Spring::getIntervalIndex()
{
	return intervalIndex;
}

Spring Spring::copy()
{
	Spring copySpring(a, b, springLength, strength, baseInterval, intervalIndex);
	return copySpring;
}

bool Spring::compare(Spring* that)
{
	return (a->compare(that->getA()) &&
		b->compare(that->getB()) &&
		springLength == that->getLength() &&
		strength == that->getStrength() &&
		baseInterval == that->getBaseInterval());
}

void Spring::print()
{
	DBG("Point A:");
	a->print();
	DBG("\nPoint B:");
	b->print();
	DBG("\nLength: " + String(springLength));
	DBG("Strength: " + String(strength));
	DBG("Base Interval: " + String(baseInterval));
}

void Spring::setStrength(double newStrength)
{
	strength = newStrength;
}

void Spring::adjustLength(double newLength)
{
	springLength = newLength;
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

	diff *= ((diff - distance) / diff) * strength;
    
    if (a->getNote() > 0)
    {
        a->addX(diff);
        a->integrate(1.0);
    }

    if (b->getNote() > 0)
    {
        b->subX(diff);
        b->integrate(1.0);
    }

	//double dist = b->getX() - a->getX();

    //springLength = dist;
	
    
    
	/*
	Aatish's spring function
	function satisfyconstraints( p1, p2, distance) {
	diff.subVectors( p2.position, p1.position );
	var currentDist = diff.length();
	if ( currentDist == 0 ) return; // prevents division by 0
	var correction = diff.multiplyScalar( (currentDist - distance) / currentDist);
	var correctionHalf = correction.multiplyScalar( 0.5 );
	p1.position.add( correctionHalf );
	p2.position.sub( correctionHalf );
	}
	*/
}
