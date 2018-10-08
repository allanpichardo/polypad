//
//  sequence.h
//  polypad
//
//  Created by Allan Pichardo on 9/29/18.
//  Copyright © 2018 Allan Pichardo. All rights reserved.
//

#ifndef sequence_h
#define sequence_h

#include "app_defs.h"

class Sequence {
private:
    u8 length = 8;
    bool sequence[16] = {1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0};

    void shift(u8 const &fromIndex, u8 const &toIndex);
public:
    bool* getSequence() { return sequence; };
    u8 getLength() { return length; };
    void generate(u8 const &onsets, u8 const &length);
    void rotate(u8 const &steps);
};

#endif /* sequence_h */
