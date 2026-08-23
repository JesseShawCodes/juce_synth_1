# JUCE Synth

A learning project exploring synthesizer development with C++ and JUCE.

The goal of this project is to build a basic software synthesizer from the ground up, understand the fundamentals of digital synthesis and audio programming, and eventually package the synth as an AUv3 instrument that can be used in GarageBand and Logic Pro.

## Project Goals

The synth will eventually include:

- Multiple oscillator types
- ADSR amplitude envelope
- Filter and filter envelope
- LFO modulation
- MIDI input
- Polyphony
- Synth parameter controls
- Preset/state management
- AUv3 plugin support
- Compatibility with GarageBand / Logic Pro

## Current Status

### Phase 1 — Basic Sound Generation ✅

The first phase established the basic audio-generation pipeline.

- [x] JUCE application
- [x] Audio callback
- [x] Audio buffer output
- [x] Sample-rate handling
- [x] Sine oscillator
- [x] 440 Hz test tone

### Phase 1.5 — Basic Synth Voice ✅

The oscillator was combined with an amplitude envelope and organized into a reusable `SynthVoice` abstraction.

Current signal flow:

```text
              SynthVoice
                  │
        ┌─────────┴─────────┐
        │                   │
   SineOscillator        Envelope
        │                   │
        └─────────┬─────────┘
                  │
              Multiply
                  │
                  ▼
             Audio Output
