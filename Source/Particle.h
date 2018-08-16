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
	Particle(double xVal, double yVal, double weight, bool startLocked = true, bool startEnabled = false);
	double getX();
	double getY();
	double getWeight();
	bool getLocked();
	void lock();
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
private:
	double x;
	double y;
	double prevX;
	double prevY;
	double w;
	bool locked;
    bool enabled;
};
