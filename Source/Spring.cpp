/*
  ==============================================================================

    Spring.cpp
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "Spring.h"
#include "../JuceLibraryCode/JuceHeader.h"

Spring::Spring(Particle firstPoint, Particle secondPoint, double length, double str) :
	a(firstPoint),
	b(secondPoint),
	springLength(length),
	strength(str)
{

}

Particle Spring::getA()
{
	return a;
}

Particle Spring::getB()
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

Spring Spring::copy()
{
	Spring copySpring(a, b, springLength, strength);
	return copySpring;
}

bool Spring::compare(Spring that)
{
	return (a.compare(that.getA()) &&
		b.compare(that.getB()) &&
		springLength == that.getLength() &&
		strength == that.getStrength());
}

void Spring::print()
{
	DBG("Point A:");
	a.print();
	DBG("\nPoint B:");
	b.print();
	DBG("\nLength: " + String(springLength));
	DBG("Strength: " + String(strength));
}

void Spring::lockA()
{
	a.changeLock();
}

void Spring::lockB()
{
	b.changeLock();
}

void Spring::satisfyConstraints(double distance)
{
	double diffX = b.getX() - a.getX();
	double diffY = b.getY() - a.getY();
	double currentDist = sqrt(diffX * diffX + diffY * diffY);
	if (currentDist == 0.0) return;
	
	diffX *= ((currentDist - distance) / currentDist) * 0.5;
	diffY *= ((currentDist - distance) / currentDist) * 0.5;
	
	a.addX(diffX);
	a.addY(diffY);
	b.subX(diffX);
	b.subY(diffY);
	
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