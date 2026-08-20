#pragma once

class Envelope
{
public:
    void setSampleRate (double newSampleRate);

    void noteOn();
    void noteOff();

    float getNextSample();

private:
    enum class State
    {
        Off,
        Attack,
        Sustain,
        Release
    };

    State state = State::Off;

    double sampleRate = 44100.0;

    float level = 0.0f;

    float attackTime = 0.1f;
    float releaseTime = 0.5f;
};
