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
	Particle(double xVal, int note);
    
    void setRestX(double);
    double getRestX();
    
    
    void setX(double);
	double getX();
    

	Particle* copy();
	bool compare(Particle* that);
	void print();
	void addX(double that);
	void subX(double that);
	void integrate(double drag);
    
    bool getEnabled(void)   { return enabled; }
    void setEnabled(bool e) { enabled = e; }

	void confirmEnabled();
    
    void setNote(int newNote) { note = newNote;}
    int getNote(void){return note;}
    
    bool getLocked(void) {return locked;}
    void setLocked(bool lock) { locked = lock;}
private:
	double x;
    double restX;
	double prevX;
    bool enabled;
    bool locked;
    int note;
};
