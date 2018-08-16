/*
  ==============================================================================

    Particle.cpp
    Created: 3 Aug 2018 3:44:24pm
    Author:  Theo

  ==============================================================================
*/

#include "Particle.h"
#include "../JuceLibraryCode/JuceHeader.h"

Particle::Particle(double xVal, double yVal, double weight, bool startLocked, bool startEnabled):
x(xVal),
y(yVal),
prevX(xVal),
prevY(yVal),
w(weight),
locked(startLocked),
enabled(startEnabled)
{

}

double Particle::getX()
{
	return x;
}

double Particle::getY()
{
	return y;
}

double Particle::getWeight()
{
	return w;
}

bool Particle::getLocked()
{
	return locked;
}

void Particle::lock()
{
	if (locked)
	{
		prevX = x;
		prevY = y;
	}
}

void Particle::changeLock()
{
	locked = !locked;
}

Particle* Particle::copy()
{
	return new Particle(x, y, w, locked);
	
}

bool Particle::compare(Particle* that)
{
	return (x == that->getX() && y == that->getY() && w == that->getWeight() && locked == that->getLocked());
}

void Particle::print()
{
	DBG("Position: (" + String(x) + ", " + String(y) + ")");
	DBG("Weight: " + String(w));
	DBG("Locked: " + String(int(locked)));
	if (enabled) DBG("Currently enabled");
	else DBG("Currently disabled");
}

void Particle::confirmEnabled()
{
	if (enabled) DBG("Currently enabled");
	else DBG("Currently disabled");
}

void Particle::addX(double that)
{
	x += that;
}

void Particle::addY(double that)
{
	y += that;
}

void Particle::subX(double that)
{
	x -= that;
}

void Particle::subY(double that)
{
	y -= that;
}

void Particle::integrate()
{
	double drag = 1.0; //still need to figure this one out
	double newX = x - prevX;
	double newY = y - prevY;

	newX *= drag;
	newY *= drag;

	newX += x;
	newY += y;

	prevX = x;
	prevY = y;
	x = newX;
	y = newY;

	//Aatish's function:
	/*
	var newPos = diff.subVectors( this.position, this.previous );
	newPos.multiplyScalar( DRAG ).add( this.position );
	this.previous = this.position;
	this.position = newPos;
	*/
}
