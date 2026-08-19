//
//  SineOscillator.cpp
//  NewProject - App
//
//  Created by C9M7JF on 8/18/26.
//

#include "SineOscillator.h"
#include <cmath>

void SineOscillator::setFrequency (double newFrequency)
{
    frequency = newFrequency;
}

void SineOscillator::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}

float SineOscillator::getNextSample() {
    const float sample =
        std::sin(phase * 2.0 * M_PI);
    
    phase += frequency / sampleRate;
    
    if (phase >= 1.0)
        phase -= 1.0;
    
    return sample;
}
