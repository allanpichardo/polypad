//
//  note.h
//  PolyPadLib
//
//  Created by Allan Pichardo on 12/22/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#ifndef note_h
#define note_h

struct Note {
    u8 note;
    u8 padIndex;
    u16 ms_until_off;
};

void note_init(struct Note* note) {
    
}

#endif /* note_h */
