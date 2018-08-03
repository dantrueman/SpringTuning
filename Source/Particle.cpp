/*
  ==============================================================================

    Particle.cpp
    Created: 3 Aug 2018 3:44:24pm
    Author:  Theo

  ==============================================================================
*/

#include "Particle.h"

Particle::Particle(double xVal, double yVal, double weight, bool startLocked = true) :
	x(xVal),
	y(yVal),
	w(weight),
	locked(startLocked)