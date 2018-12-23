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
#include "arpeggiator.h"

void polypad_on_beat(void);
void polypad_on_tick(u8* startingNote, u16* ms_ticks);
void polypad_note_on(u8 note, u8 arpIndex, u8 padIndex);
void polypad_note_off(u8 note, u8 arpIndex, u8 padIndex);
void polypad_make_note(u8* startingNote, struct Arpeggiator* arpeggiator, u8 arpIndex);
u8 polypad_semitoneoffset_to_index(u8 startIndex, u8 startNote, u8 offset);

void polypad_clear_grid(void);
void polypad_initialize_grid(u16* ms_ticks);
void polypad_restore_grid_from_store(void);
void polypad_draw_tempo_select(u8 tempo);
void polypad_draw_quantize_menu(u8 trackId);

void polypad_pad_down(u8 index, u8* startingNote);
void polypad_click_down(u8 bpm);
void polypad_color_octave_arrows(u8* startingNote);
void polypad_click_up(void);
void polypad_pad_up(u8 index);
void polypad_leftarrow_down(u16* ticks);
void polypad_rightarrow_down(u16* ticks);
void polypad_uparrow_down(u8* startingNote);
void polypad_downarrow_down(u8* startingNote);
void polypad_track_play_down(u8 index);
void polypad_track_play_up(u8 index);
void polypad_quantize_down(void);
void polypad_quantize_up(void);
void polypad_stop_clip_down(void);

u8 polypad_xy_to_index(u8 x, u8 y);
u8 polypad_index_to_y(u8 index);
u8 polypad_index_to_x(u8 index);

u16 polypad_bpm_to_ms(u8 bpm);
u8 polypad_ms_to_bpm(u16 ms);
u8 polypad_note_to_led_intensity(u8 startingNote);

u8 polypad_xy_to_midi_note(u8 startingNote, u8 x, u8 y);

#endif /* polypad_h */
