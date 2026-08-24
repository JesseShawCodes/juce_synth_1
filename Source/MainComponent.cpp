#include "MainComponent.h"
#include <cstdint>

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (600, 400);
    
    setAudioChannels(0, 2);
    
    auto midiDevices =
        juce::MidiInput::getAvailableDevices();
    
    if (!midiDevices.isEmpty())
    {
        const auto& device = midiDevices.getFirst();
        
        DBG("Opening MIDI device: " + device.name);
        
        midiInput = juce::MidiInput::openDevice(
            device.identifier,
            this
        );
        
        if (midiInput != nullptr)
        {
            midiInput->start();
            
            DBG("MIDI device opened successfully.");
        }
        else
        {
            DBG("FAILED to open MIDI device.");
        }
    }
    else
    {
        DBG("No MIDI input devices available.");
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    if (midiInput != nullptr)
        midiInput->stop();

    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    voice.prepareToPlay(sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    // bufferToFill.clearActiveBufferRegion();
    
    auto* buffer = bufferToFill.buffer;

    for (int sample = 0;
         sample < bufferToFill.numSamples;
         ++sample)
    {
        const float outputSample =
        voice.getNextSample();
        
        for (int channel = 0;
             channel < buffer->getNumChannels();
             ++channel)
        {
            buffer->setSample(
                  channel,
                  bufferToFill.startSample + sample,
                  outputSample
          );
        }


    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::handleMidiMessage(
    const juce::MidiMessage& message)
{
    if (message.isNoteOn())
    {
        const int midiNote = message.getNoteNumber();
        
        voice.noteOn(midiNote);
    }
    else if (message.isNoteOff())
    {
        voice.noteOff();
    }
}

void MainComponent::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    handleMidiMessage(message);
}
