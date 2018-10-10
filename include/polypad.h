//
//  polypad.h
//  PolyPadLib
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#ifndef polypad_h
#define polypad_h

#include "app_defs.h"
#include "app.h"

void polypad_clear_grid(void);
void polypad_draw_chromatic_grid(void);
void polypad_restore_grid_from_store(void);
void polypad_draw_tempo_select(u8 tempo);

void polypad_pad_down(u8 index, u8* startingNote);
void polypad_click_down(u8 bpm);
void polypad_click_up(void);
void polypad_pad_up(u8 index);
void polypad_leftarrow_down(u16* ticks);
void polypad_rightarrow_down(u16* ticks);
void polypad_uparrow_down(u8* startingNote);
void polypad_downarrow_down(u8* startingNote);

u8 polypad_xy_to_index(u8 x, u8 y);
u8 polypad_index_to_y(u8 index);
u8 polypad_index_to_x(u8 index);

u16 polypad_bpm_to_ms(u8 bpm);
u8 polypad_ms_to_bpm(u16 ms);

u8 polypad_xy_to_midi_note(u8 startingNote, u8 x, u8 y);

#endif /* polypad_h */
