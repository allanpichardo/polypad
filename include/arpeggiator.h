
#ifndef arpeggiator_h
#define arpeggiator_h

#include "sequence.h"
#include "app_defs.h"

enum Scale {
    majorScale, minorScale
};

struct ArpeggiatorState {
    u8 baseNote;
    u8 isPlaying;
    u8 step;
    u8 isLatched;
};

struct Arpeggiator {
    u8 index;
    u8 scale[16];
    u8 arpeggio[16];
    u8 length;
    struct Sequence sequence;
    struct ArpeggiatorState state;
};

void arpeggiator_init(struct Arpeggiator* arpeggiator);
void _apreggiator_computeArp(struct Arpeggiator* arpeggiator);
void arpeggiator_setPatern(struct Arpeggiator* arpeggiator, u8 const onsets, u8 const length);
void apreggiator_shift(struct Arpeggiator* arpeggiator, u8 const steps);
void apreggiator_setScale(struct Arpeggiator* arpeggiator, enum Scale scale);

#endif
