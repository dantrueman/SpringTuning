/*
  ==============================================================================

    Particle.h
    Created: 3 Aug 2018 3:44:24pm
    Author:  Theo

  ==============================================================================
*/

#pragma once

class Particle
{
public:
	Particle(double xVal, double yVal, double weight, bool startLocked = true);
	double getX();
	double getY();
	double getWeight();
	bool locked();
	void lock();
	Particle copy();
	bool compare();
	void print();
private:
	double x;
	double y;
	double w;
	bool locked;
};