//
//  sequence.cpp
//  polypad
//
//  Created by Allan Pichardo on 9/29/18.
//  Copyright © 2018 Allan Pichardo. All rights reserved.
//

#include "sequence.h"
#include "app_defs.h"
#include <iostream>
using namespace std;

void Sequence::shift(u8 const &fromIndex, u8 const &toIndex) {
    if(fromIndex < toIndex) {
        u8 temp = sequence[fromIndex];
        for(u8 i = fromIndex + 1; i < toIndex + 1; i++) {
            sequence[i - 1] = sequence[i];
        }
        sequence[toIndex] = temp;
    } else {
        u8 temp = sequence[fromIndex];
        for(u8 i = fromIndex; i > toIndex; i--) {
            sequence[i] = sequence[i - 1];
        }
        sequence[toIndex] = temp;
    }
}

void Sequence::rotate(u8 const &steps) {

    for (u8 i = 0; i < steps; i++)  {
        shift(length - 1, 0);
    }

}

void Sequence::generate(u8 const &beats, u8 const &steps) {
    u8 bucket = 0;
    this->length = steps;

    for(u8 i = 0; i < length; i++) {
        bucket += beats;

        if(bucket >= length) {
            bucket -= length;
            sequence[i] = 1;
        }else{
            sequence[i] = 0;
        }
    }

    rotate(1);
}
