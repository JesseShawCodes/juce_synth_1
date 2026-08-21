/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Aug 2026 11:02:13pm
    Author:  C9M7JF

  ==============================================================================
*/

#include "SynthVoice.h"

void SynthVoice::prepareToPlay(double sampleRate)
{
    oscillator.setSampleRate(sampleRate);
    oscillator.setFrequency(440.0);
    
    envelope.setSampleRate(sampleRate);
}

void SynthVoice::noteOn()
{
    envelope.noteOn();
}

void SynthVoice::noteOff()
{
    envelope.noteOff();
}

float SynthVoice::getNextSample()
{
    const float oscillatorSample =
    oscillator.getNextSample();
    
    const float envelopeSample =
    envelope.getNextSample();
    
    return oscillatorSample * envelopeSample;
}
