/*
  ==============================================================================

    Particle.h
    Created: 3 Aug 2018 3:44:24pm
    Author:  Theo

  ==============================================================================
*/

#pragma once

#include "PhysicsUtilities.h"

class Particle
{
public:
	Particle(double xVal, double yVal, bool startLocked = true, bool startEnabled = false);
	double getX();
	double getY();
	bool getLocked();
	void useLock();
	void lock();
	void unlock();
	void changeLock();
	Particle* copy();
	bool compare(Particle* that);
	void print();
	void addX(double that);
	void addY(double that);
	void subX(double that);
	void subY(double that);
	void integrate();
    
    bool getEnabled(void)   { return enabled; }
    void setEnabled(bool e) { enabled = e; }

	void confirmEnabled();
private:
	double x;
	double y;
	double prevX;
	double prevY;
	bool locked;
    bool enabled;
};
