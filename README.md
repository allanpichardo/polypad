[![Build Status](https://travis-ci.org/dvhdr/launchpad-pro.svg?branch=master)](https://travis-ci.org/dvhdr/launchpad-pro)

# Polypad
Standalone polymetric arpeggiator firmware for the Launchpad Pro

## Latest Release
- [v 1.1](https://github.com/allanpichardo/polypad/releases/tag/1.1)

# Features
- Play 8 independent sequences
- MIDI out to up to 8 devices
- 8 scales to choose from
- Independently dial combinations of Euclidean rhythms

# Instructions
## Main View
![polypad main view](https://github.com/allanpichardo/polypad/blob/master/docs/overview.png "Main View")
### Arpeggios
Holding a note down will trigger an arpeggiation. There can be up to 8 simultaneous arpeggiations if 8 notes are held at the same time.Each arpeggio can be latched (or held indefinitely) by using one of the play buttons long the right.

### Tempo
The tempo may be set by using the ◀️ and ▶️ arrows on the top row. Alternately, a numerical tempo display can be seen by holding down the **Click** button.

### Octave Select
The default octave is 4. But may be changed by using the 🔼 and 🔽 buttons on the top row.

## Sequence Settings
Each arpeggio can be individually customized by holding down the **Quantize** button.
![polypad sequence settings](https://github.com/allanpichardo/polypad/blob/master/docs/sequence.png "Quantize View")

### Altering an Arpeggio
* Select the track you wish to edit from the arrow buttons along the right.
* Rows 1 & 2 set the number of onsets per pattern.
* Rows 3 & 4 set the maximum length of the pattern (up to 16 notes).
* Row 5 sets the scale to one of the following:
..1. Major (Ionian mode)
..2. Minor (Aeolian mode)
..3. Dorian mode
..4. Phrygian mode
..5. Lydian mode
..6. Mixolydian mode
..7. Locrian mode
* Row 6 sets the subdivision of notes to 1/8, 1/4, 1/2, 1, 2 or 4
* Row 7 & 8 sets the MIDI channel (1 through 16).

## MIDI
Polypad outputs MIDI note data as well as clock through the 1/8" port or USB. At the moment, it does not accept MIDI clock in.

# Uploading to a Launchpad Pro
To upload it to your Launchpad Pro, you'll need a sysex tool for your host platform (I'd love to get it working from the virtual machine, but that's for later).  I recommend [Sysex Librarian](http://www.snoize.com/SysExLibrarian/) on macOS, and [MIDI OX](http://www.midiox.com/) on Windows.  On Linux, I'll bet you already have a tool in mind.

I won't describe how to use these tools, I'm sure you already know - and if you don't, their documentation is superior to mine!  Here's what you need to do:

1. Unplug your Launchpad Pro
2. Hold the "Setup" button down while connecting it to your host via USB (ensure it's connected to the host, and not to a virtual machine!)
3. The unit will start up in "bootloader" mode
4. Send your polypad.syx file to the device MIDI port - it will briefly scroll "upgrading..." across the grid.
5. Wait for the update to complete, and for the device to reboot!

Tip - set the delay between sysex messages to as low a value as possible, so you're not waiting about for ages while the firmware uploads!
