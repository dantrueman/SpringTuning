/*
  ==============================================================================

    Spring.h
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "PhysicsUtilities.h"

#include "Particle.h"

class Spring
{
public:
	Spring(Particle* firstPoint, Particle* secondPoint, double length, double str, double interval, int index);
	Particle* getA(void);
	Particle* getB(void);
	double getLength();
	double getStrength();
	double getBaseInterval();
	int getIntervalIndex();
	Spring copy();
	bool compare(Spring* that);
	void print();
	void setStrength(double newStrength);
	void adjustLength(double newLength);
	//String getStringBaseInterval();
	void satisfyConstraints(double distance);
    
    bool getEnabled(void) { return enabled; }
    void setEnabled(bool e) { enabled = e; }

private:
	Particle* a;
	Particle* b;
	double springLength;
	double strength;
	double baseInterval;
    bool enabled;
	int intervalIndex; //will probably replace base interval
};

#pragma once
