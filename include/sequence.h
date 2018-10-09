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

struct Sequence {
    u8 length;
    u8 sequence[16];
};

void sequence_shift(struct Sequence* sequence, u8 const fromIndex, u8 const toIndex);
void sequence_generate(struct Sequence* sequence, u8 const onsets, u8 const length);
void sequence_rotate(struct Sequence* sequence, u8 const steps);

#endif /* sequence_h */
