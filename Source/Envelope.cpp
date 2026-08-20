#include "Envelope.h"

void Envelope::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}

void Envelope::noteOn()
{
    state = State::Attack;
}

void Envelope::noteOff()
{
    state = State::Release;
}

float Envelope::getNextSample()
{
    switch (state)
    {
        case State::Off:
            return 0.0f;
        
        case State::Attack:
        {
            const float attackIncrement =
                1.0f / (attackTime * sampleRate);
            
            level += attackIncrement;
            
            if (level >= 1.0f)
            {
                level = 1.0f;
                state = State::Sustain;
            }
            
            return level;
        }
            
        case State::Sustain:
            return level;
        
        case State::Release:
        {
            const float releaseDecrement =
            1.0f / (releaseTime * sampleRate);
            
            level -= releaseDecrement;
            
            if (level <= 0.0f)
            {
                level = 0.0f;
                state = State::Off;
            }
            
            return level;
        }
    }
}
