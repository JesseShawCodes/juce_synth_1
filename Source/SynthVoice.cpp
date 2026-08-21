/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Aug 2026 11:02:13pm
    Author:  C9M7JF

  ==============================================================================
*/

#include "SynthVoice.h"

void SynthVoice::prepareToPlay(<#double sampleRate#>)
{
    oscillator.setSampleRate(sampleRate);
    oscillator.setFrequency(440.0);
    
    envelope.setSampleRate(sampleRate);
}
