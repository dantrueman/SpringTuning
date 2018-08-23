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
    
    constexpr static const float pi = 3.14159265359f;
    constexpr static const float twopi = 6.28318530718f;
    
private:
    Utilities () {};
};

