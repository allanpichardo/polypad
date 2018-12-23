#include "arpeggiator.h"
#include "sequence.h"
#include "app_defs.h"
#include <string.h>

void arpeggiator_init(struct Arpeggiator* arpeggiator) {
    u8 scale[16] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
    memcpy(arpeggiator->scale, scale, sizeof(scale));
    
    u8 arpeggio[16] = {0,255,3,5,255,8,10,255,255,255,255,255,255,255,255,255};
    memcpy(arpeggiator->arpeggio, arpeggio, sizeof(arpeggio));
    
    arpeggiator->length = 8;
    arpeggiator->index = 0;
    
    arpeggiator->state.isPlaying = 0;
    arpeggiator->state.isLatched = 0;
    
    arpeggiator->sequence.length = 8;
    arpeggiator->sequence.onsets = 5;
    
    arpeggiator->time_to_next_note = 0;
    arpeggiator->multiplier = 3;
    
    u8 sequence[16] = {1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0};
    memcpy(arpeggiator->sequence.sequence, sequence, sizeof(sequence));
}

void _arpeggiator_computeArp(struct Arpeggiator* arpeggiator) {
    arpeggiator->length = arpeggiator->sequence.length;
    
    for(u8 i = 0; i < arpeggiator->sequence.length; i++) {
        arpeggiator->arpeggio[i] = arpeggiator->sequence.sequence[i] ? arpeggiator->scale[i] : 255;
    }
}

void arpeggiator_setPatern(struct Arpeggiator* arpeggiator, const u8 onsets, const u8 length) {
    sequence_generate(&arpeggiator->sequence, onsets, length);
    _arpeggiator_computeArp(arpeggiator);
}

void arpeggiator_shift(struct Arpeggiator* arpeggiator, const u8 steps) {
    sequence_rotate(&arpeggiator->sequence, steps);
    _arpeggiator_computeArp(arpeggiator);
}

void arpeggiator_setScale(struct Arpeggiator* arpeggiator, enum Scale scale) {
    switch(scale) {
        case major: {
            u8 maj[16] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
            memcpy(arpeggiator->scale, maj, sizeof(maj));
            break;
        }
        case minor: {
            u8 min[16] = {0,2,3,5,7,8,10,12,14,15,17,19,20,22,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
        case dorian: {
            u8 min[16] = {0,2,3,5,7,9,10,12,14,15,17,19,21,22,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
        case phyrgian: {
            u8 min[16] = {0,1,3,5,7,8,10,12,13,15,17,19,20,22,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
        case lydian: {
            u8 min[16] = {0,2,4,6,7,9,11,12,14,16,18,19,21,23,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
        case mixolydian: {
            u8 min[16] = {0,2,4,5,7,9,10,12,14,16,17,19,21,22,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
        case locrian: {
            u8 min[16] = {0,1,3,5,6,8,10,12,13,15,17,18,20,22,24};
            memcpy(arpeggiator->scale, min, sizeof(min));
            break;
        }
    }
    _arpeggiator_computeArp(arpeggiator);
}


