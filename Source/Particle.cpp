/*
  ==============================================================================

    Particle.cpp
    Created: 3 Aug 2018 3:44:24pm
    Author:  Theo

  ==============================================================================
*/

#include "Particle.h"
#include "../JuceLibraryCode/JuceHeader.h"

Particle::Particle(double xVal, double yVal, bool startLocked, bool startEnabled):
x(xVal),
y(yVal),
prevX(xVal),
prevY(yVal),
locked(startLocked),
enabled(startEnabled)
{

}

void Particle::setX(double xp)
{
    x = xp;
}

double Particle::getX()
{
	return x;
}

void Particle::setY(double yp)
{
    y = yp;
}

double Particle::getY()
{
	return y;
}

bool Particle::getLocked()
{
	return locked;
}

void Particle::lock()
{
	locked = true;
    
    prevX = x;
    prevY = y;
}

void Particle::unlock()
{
	locked = false;
}

void Particle::toggleLock()
{
    if (locked)
    {
        unlock();
    }
    else
    {
        lock();
    }
    
}

Particle* Particle::copy()
{
	return new Particle(x, y, locked, enabled);
	
}

bool Particle::compare(Particle* that)
{
	return (x == that->getX() && y == that->getY() && locked == that->getLocked());
}

void Particle::print()
{
	DBG("Position: (" + String(x) + ", " + String(y) + ")");
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
	if (!locked)
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
	}

	//Aatish's function:
	/*
	var newPos = diff.subVectors( this.position, this.previous );
	newPos.multiplyScalar( DRAG ).add( this.position );
	this.previous = this.position;
	this.position = newPos;
	*/
}
