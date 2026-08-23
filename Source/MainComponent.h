#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include <juce_audio_devices/juce_audio_devices.h>

class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    void handleMidiMessage(const juce::MidiMessage& message);
    
    void handleIncomingMidiMessage(
        juce::MidiInput* source,
        const juce::MidiMessage& message);
    
    SynthVoice voice;
    
    std::unique_ptr<juce::MidiInput> midiInput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
