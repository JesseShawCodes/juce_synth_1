/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Aug 2026 11:01:52pm
    Author:  C9M7JF

  ==============================================================================
*/

#pragma once

#include "SineOscillator.h"
#include "Envelope.h"

class SynthVoice
{
public:
    void prepareToPlay(double sampleRate);
    
    void noteOn();
    void noteOff();
    
    float getNextSample();
    
private:
    SineOscillator oscillator;
    Envelope envelope;
};
