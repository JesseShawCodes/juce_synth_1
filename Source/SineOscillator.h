//
//  SineOscillator.h
//  NewProject - App
//
//  Created by C9M7JF on 8/18/26.
//

#pragma once

class SineOscillator
{
public:
    void setFrequency(double newFrequency);
    void setSampleRate(double newSampleRate);
    
    float getNextSample();
    
private:
    double frequency = 440.0;
    double sampleRate = 44100.0;
    double phase = 0.0;
};
