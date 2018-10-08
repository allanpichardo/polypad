#include "arpeggiator.h"
#include "sequence.h"
#include "app_defs.h"

#include <string>
using namespace std;

void Arpeggiator::setPatern(const u8 &onsets, const u8 &length) {
    sequence.generate(onsets, length);
    computeArp();
}

void Arpeggiator::shift(const u8 &steps) {
    sequence.rotate(steps);
    computeArp();
}

void Arpeggiator::setScale(Scale scale) {
    switch(scale) {
        case Scale::majorScale: {
            u8 maj[16] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
            memcpy(this->scale, maj, sizeof(maj));
            break;
        }
        case Scale::minorScale: {
            u8 min[16] = {0,2,3,5,7,8,10,12,14,15,17,19,20,22,24};
            memcpy(this->scale, min, sizeof(min));
            break;
        }
    }
    computeArp();
}

void Arpeggiator::computeArp() {
    this->length = sequence.getLength();

    for(u8 i = 0; i < sequence.getLength(); i++) {
        arpeggio[i] = sequence.getSequence()[i] ? scale[i] : 255;
    }
}


