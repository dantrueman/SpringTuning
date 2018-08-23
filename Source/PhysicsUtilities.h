/*
  ==============================================================================

    PhysicsUtilities.h
    Created: 10 Aug 2018 12:26:55pm
    Author:  airship

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define INV_440 0.00227272727f

class Utilities
{
public:
    static float ftom(float f)
    {
        return (69.0f + 12.0f * log2(f * INV_440));
    }
private:
    Utilities () {};
};

