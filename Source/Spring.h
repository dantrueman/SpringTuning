/*
  ==============================================================================

    Spring.h
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "Particle.h"

class Spring
{
public:
	Spring(Particle firstPoint, Particle secondPoint, double length, double str, double interval);
	Particle getA();
	Particle getB();
	double getLength();
	double getStrength();
	double getBaseInterval();
	Spring copy();
	bool compare(Spring that);
	void print();
	void lockA();
	void lockB();
	void setStrength(double newStrength);
	void adjustLength(double newLength);
	//String getStringBaseInterval();
	void satisfyConstraints(double distance);
private:
	Particle a;
	Particle b;
	double springLength;
	double strength;
	double baseInterval;
};

#pragma once
