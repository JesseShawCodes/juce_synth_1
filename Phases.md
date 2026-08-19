# Step breakdowns

The biggest distinction is:

* AU (Audio Unit v2) → traditional macOS plugin architecture
* AUv3 (Audio Unit Extension) → Apple’s newer plugin architecture, designed especially for iOS/iPadOS and also usable on macOS

If your goal is “I want to build my own synth and eventually use it inside GarageBand on my iPad/iPhone”, then AUv3 is actually the direction I’d recommend.

The architecture is basically the same

Your synth’s DSP doesn’t fundamentally care whether it’s AU or AUv3:

MIDI
  ↓
Note → Frequency
  ↓
Oscillator
  ↓
ADSR
  ↓
Filter
  ↓
Output

You’d still implement:

* oscillator(s)
* MIDI note handling
* polyphony
* ADSR
* filters
* LFOs
* parameters
* audio rendering
* UI

The big change is how your synth is packaged and communicated with the host.

With AUv3, think of it like this

                    Your App
                       │
             ┌─────────┴─────────┐
             │                   │
        Standalone App       AUv3 Extension
             │                   │
             │                   ▼
             │              GarageBand
             │                   │
             └───────┐     MIDI/audio
                     │
                     ▼
                Synth Engine

Your actual synthesizer engine should ideally be independent of the AUv3 wrapper.

For example:

```
SynthEngine
├── Oscillator
├── Voice
├── VoiceManager
├── Envelope
├── Filter
└── LFO
```

Then:

```
AUv3 Adapter
      ↓
SynthEngine
```

That architecture is useful because you can make a standalone synth app and an AUv3 plugin that share the exact same synthesis code.

JUCE can still be used

This is where my previous answer needs a small correction.

JUCE can absolutely be used to build an AUv3. You’d configure the project for the appropriate Audio Unit format rather than simply building an old-style .component Audio Unit.

JUCE handles much of the plugin plumbing, while you focus on:

```
processBlock()
      ↓
MIDI events
      ↓
Synth voices
      ↓
DSP
      ↓
audio buffer
```

And you can build the UI using JUCE as well.

There’s an especially nice route for you

Given that you’re already comfortable with programming, I’d probably structure your learning project like this:

Phase 1 — Learn synthesis

Build a tiny standalone synth:

```
C++ / JUCE
     ↓
Sine oscillator
     ↓
MIDI
     ↓
ADSR
     ↓
Audio
```

Don’t worry about AUv3 yet.

Phase 2 — Make it polyphonic

```
MIDI
 ↓
Voice Manager
 ├── Voice 1 → Oscillator → ADSR
 ├── Voice 2 → Oscillator → ADSR
 ├── Voice 3 → Oscillator → ADSR
 └── Voice 4 → Oscillator → ADSR
             ↓
            Mix
```

This is where it starts becoming a real synthesizer.

Phase 3 — Add subtractive synthesis

```
Oscillator
    ↓
Mixer
    ↓
Filter ← Filter Envelope
    ↓
Amp Envelope
    ↓
Output
```

Add:

* saw
* square
* sine
* oscillator detuning
* cutoff
* resonance
* ADSR
* LFO

Phase 4 — Build AUv3

Now wrap your SynthEngine as an AUv3 instrument.

                  ┌── Standalone App
                  │
SynthEngine ──────┤
                  │
                  └── AUv3 Extension
                            ↓
                       GarageBand

Phase 5 — Put it on your iPad

This is where AUv3 becomes particularly cool.

You could have your own synth sitting alongside Apple’s instruments in GarageBand, with your own interface:

GarageBand
     │
     ├── Piano
     ├── Drums
     ├── Bass
     └── YourSynth AUv3  ← yours

And because you’re interested in Logic Pro on iPad, there’s an even bigger payoff: the same AUv3 concept can be used in Logic Pro for iPad as well.

One thing I’d change from my previous recommendation

If iPad is the ultimate target, I wouldn’t spend much time learning the old AUv2 architecture first.

I’d go:

C++ → JUCE → basic synth → AUv3

rather than:

C++ → AUv2 → AUv3

The DSP concepts are what you really want to learn. AUv3 is mostly the packaging/host integration layer around that DSP.

And honestly, building a little AUv3 synth that you can actually open in GarageBand or Logic on your iPad would be a fantastic programming/music project. It combines the software engineering stuff you already know with the music-production side you’ve been exploring.
