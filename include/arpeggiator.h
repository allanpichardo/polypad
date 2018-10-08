
#ifndef arpeggiator_h
#define arpeggiator_h

#include "sequence.h"
#include "app_defs.h"

enum Scale: u8 {
    majorScale, minorScale
};

class Arpeggiator {

    private:
    u8 scale[16] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
    u8 arpeggio[16] = {0,255,3,5,255,8,10,255,255,255,255,255,255,255,255,255};
    u8 length = 8;
    Sequence sequence;

    void computeArp();

    public:
    Arpeggiator(): sequence() {};
    void setPatern(u8 const &onsets, u8 const &length);
    void shift(u8 const &steps);
    void setScale(Scale scale);
    u8* getArpeggio() { return arpeggio; };
    u8 getLength() { return length; };
};

#endif
