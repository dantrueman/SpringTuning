/*
  ==============================================================================

    Spring.h
    Created: 3 Aug 2018 3:44:01pm
    Author:  Theo

  ==============================================================================
*/

#include "PhysicsUtilities.h"

#include "Particle.h"

class Spring : public ReferenceCountedObject
{
public:
    typedef ReferenceCountedObjectPtr<Spring> Ptr;
    typedef Array<Spring::Ptr> PtrArr;
    
	Spring(Particle* firstPoint, Particle* secondPoint, double str, double interval, int index);
	Particle* getA(void);
	Particle* getB(void);
	double getLength();
    
	double getBaseInterval();
    void setBaseInterval(double interval);
    
	int getIntervalIndex();
	Spring copy();
	bool compare(Spring* that);
	void print();
    
    void setStrength(double newStrength);
    double getStrength();
	void adjustLength(double newLength);
	//String getStringBaseInterval();
	void satisfyConstraints(double distance);
	void update();
    
    bool getEnabled(void) { return enabled; }
    void setEnabled(bool e) { enabled = e; }

    void setName(String s) { name = s;}
    String getName(void) { return name;}

private:
	Particle* a;
	Particle* b;
	double strength;
	double baseInterval;
    bool enabled;
	int intervalIndex; //will probably replace base interval
    String name;
};

#pragma once
