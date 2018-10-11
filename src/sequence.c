//
//  sequence.cpp
//  polypad
//
//  Created by Allan Pichardo on 9/29/18.
//  Copyright © 2018 Allan Pichardo. All rights reserved.
//

#include "sequence.h"
#include "app_defs.h"

void sequence_shift(struct Sequence* sequence, u8 const fromIndex, u8 const toIndex) {
    if(fromIndex < toIndex) {
        u8 temp = sequence->sequence[fromIndex];
        for(u8 i = fromIndex + 1; i < toIndex + 1; i++) {
            sequence->sequence[i - 1] = sequence->sequence[i];
        }
        sequence->sequence[toIndex] = temp;
    } else {
        u8 temp = sequence->sequence[fromIndex];
        for(u8 i = fromIndex; i > toIndex; i--) {
            sequence->sequence[i] = sequence->sequence[i - 1];
        }
        sequence->sequence[toIndex] = temp;
    }
}

void sequence_rotate(struct Sequence* sequence, u8 const steps) {

    for (u8 i = 0; i < steps; i++)  {
        sequence_shift(sequence, sequence->length - 1, 0);
    }

}

void sequence_generate(struct Sequence* sequence, u8 const beats, u8 const steps) {
    u8 bucket = 0;
    sequence->length = steps;
    sequence->onsets = beats;

    for(u8 i = 0; i < sequence->length; i++) {
        bucket += beats;

        if(bucket >= sequence->length) {
            bucket -= sequence->length;
            sequence->sequence[i] = 1;
        }else{
            sequence->sequence[i] = 0;
        }
    }

    sequence_rotate(sequence, 1);
}
