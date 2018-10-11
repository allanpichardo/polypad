//
//  polypad.c
//  PolyPadLib
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//
#include "polypad.h"
#include "dotmatrix.h"
#include "arpeggiator.h"
#include "app_defs.h"
#include "app.h"
#include <stdio.h>

/**
 Globals
 */
u8 g_GridColors[100] = {0};
u8 g_Midi_Channel = 1;
u8 g_ActiveNotes[8][2] = {0};
static struct Arpeggiator g_arpeggiators[8];

/**
 Flags
 */
u8 flag_editingTempo = 0;
u8 flag_editingQuantize = 0;

u8 polypad_xy_to_index(u8 x, u8 y) {
    return ((y+1) * 10) + (x+1);
}

u8 polypad_index_to_y(u8 index) {
    return ((index / 10) % 10) - 1;
}

u8 polypad_index_to_x(u8 index) {
    return (index % 10) - 1;
}

void polypad_pad_light_on(u8 index) {
    hal_plot_led(TYPEPAD, index, 0, 0, MAXLED);
    u8 x = polypad_index_to_x(index);
    u8 y = polypad_index_to_y(index);
    if(x > 4 && y < 7) {
        y++;
        x -= 5;
        hal_plot_led(TYPEPAD, polypad_xy_to_index(x, y), 0, 0, MAXLED);
    }
}

void polypad_pad_light_restore(u8 index) {
    if(g_GridColors[index] == 100) {
        hal_plot_led(TYPEPAD, index, MAXLED, 0, 0);
    } else if(g_GridColors[index] == 010) {
        hal_plot_led(TYPEPAD, index, 0, MAXLED, 0);
    } else if(g_GridColors[index] == 000){
        hal_plot_led(TYPEPAD, index, 0, 0, 0);
    } else if(index == 91 || index == 92){
        hal_plot_led(TYPEPAD, index, 0, g_GridColors[index], 0);
    } else if(index == 93 || index == 94) {
        hal_plot_led(TYPEPAD, index, 0, g_GridColors[index], g_GridColors[index]);
    } else if(index % 10 == 9) {
        hal_plot_led(TYPEPAD, index, g_GridColors[index], 0, g_GridColors[index]);
    }
    
    u8 x = polypad_index_to_x(index);
    u8 y = polypad_index_to_y(index);
    if(x > 4 && y < 7) {
        y++;
        x -= 5;
        polypad_pad_light_restore(polypad_xy_to_index(x, y));
    }
}

void polypad_leftarrow_down(u16* ticks) {
    hal_plot_led(TYPEPAD, 93, 0, MAXLED, MAXLED);
    
    u8 bpm = polypad_ms_to_bpm(*ticks);
    bpm--;
    
    if(flag_editingTempo) {
        polypad_draw_tempo_select(bpm);
    }
    
    *ticks = polypad_bpm_to_ms(bpm);
}

void polypad_rightarrow_down(u16* ticks) {
    hal_plot_led(TYPEPAD, 94, 0, MAXLED, MAXLED);
    
    u8 bpm = polypad_ms_to_bpm(*ticks);
    bpm++;
    
    if(flag_editingTempo) {
        polypad_draw_tempo_select(bpm);
    }
    
    *ticks = polypad_bpm_to_ms(bpm);
}

void polypad_pad_down(u8 index, u8* startingNote) {
    
    if(flag_editingQuantize) {
        
    } else {
        polypad_pad_light_on(index);
        
        u8 x = polypad_index_to_x(index);
        u8 y = polypad_index_to_y(index);
        u8 note = polypad_xy_to_midi_note(*startingNote, x, y);
        
        for(u8 i = 0; i < 8; i++) {
            if(!g_arpeggiators[i].state.isPlaying) {
                g_arpeggiators[i].state.isPlaying = 1;
                g_arpeggiators[i].index = index;
                g_arpeggiators[i].state.baseNote = note;
                
                polypad_make_note(startingNote, &g_arpeggiators[i], i);
                
                return;
            }
        }
    }
}

void polypad_track_play_down(u8 index) {
    u8 trackIndex = 8 - ((index / 10) % 10);
    
    if(flag_editingQuantize) {
        polypad_draw_quantize_menu(trackIndex);
    } else {
        if(g_arpeggiators[trackIndex].state.isLatched) {
            g_arpeggiators[trackIndex].state.isLatched = 0;
            g_arpeggiators[trackIndex].state.isPlaying = 0;
            polypad_pad_light_restore(index);
        } else {
            if(g_arpeggiators[trackIndex].state.isPlaying) {
                g_arpeggiators[trackIndex].state.isLatched = 1;
                hal_plot_led(TYPEPAD, index, MAXLED, 0, MAXLED);
            }
        }
    }
}

void polypad_track_play_up(u8 index) {
    if(flag_editingQuantize) {
        
    }
}

void polypad_click_down(u8 bpm) {
    flag_editingTempo = 1;
    polypad_draw_tempo_select(bpm);
}

void polypad_quantize_down(void) {
    flag_editingQuantize = 1;
    polypad_draw_quantize_menu(0);
}

void polypad_quantize_up(void){
    flag_editingQuantize = 0;
    polypad_restore_grid_from_store();
}

void polypad_pad_up(u8 index) {
    
    if(flag_editingQuantize) {
        
    } else {
        polypad_pad_light_restore(index);
        
        for(u8 i = 0; i < 8; i++) {
            if(g_arpeggiators[i].index == index && g_arpeggiators[i].state.isPlaying && !g_arpeggiators[i].state.isLatched) {
                g_arpeggiators[i].state.isPlaying = 0;
                g_arpeggiators[i].index = 0;
                g_arpeggiators[i].state.baseNote = 0;
                return;
            }
        }
    }
    
}

void polypad_click_up() {
    flag_editingTempo = 0;
    polypad_restore_grid_from_store();
}

void polypad_uparrow_down(u8* startingNote) {
    *startingNote = *startingNote + 12;
    polypad_color_octave_arrows(startingNote);
}

void polypad_downarrow_down(u8* startingNote) {
    *startingNote = *startingNote - 12;
    polypad_color_octave_arrows(startingNote);
}

void polypad_restore_grid_from_store() {
    for(u8 i = 0; i < 100; i++) {
        polypad_pad_light_restore(i);
    }
}

void polypad_draw_quantize_menu(u8 trackId) {
    
    u8 playButtonIndex = ((8 - trackId) * 10) + 9;
    
    hal_plot_led(TYPEPAD, playButtonIndex, 0, 0, MAXLED);
    for(u8 i = 19; i < 99; i += 10) {
        if(i != playButtonIndex)
            polypad_pad_light_restore(i);
    }
    polypad_clear_grid();
    
    
}

void polypad_draw_tempo_select(u8 tempo) {
    
    polypad_clear_grid();
    
    u8 ones = tempo % 10;
    for(u8 i = 0; i < 3; i++) {
        for(u8 j = 0; j < 4; j++) {
            if(number_matrix[ones][i][j]) {
                u8 index = polypad_xy_to_index(i + 5, j + 4);
                hal_plot_led(TYPEPAD, index, 0, MAXLED, MAXLED);
            }
        }
    }
    
    if(tempo > 9) {
        u8 tens = (tempo / 10) % 10;
        for(u8 i = 0; i < 3; i++) {
            for(u8 j = 0; j < 4; j++) {
                if(number_matrix[tens][i][j]) {
                    u8 index = polypad_xy_to_index(i + 2, j + 4);
                    hal_plot_led(TYPEPAD, index, 0, MAXLED, MAXLED);
                }
            }
        }
    }
    
    if(tempo > 99) {
        u8 hundreds = (tempo / 100) % 10;
        for(u8 i = 0; i < 3; i++) {
            for(u8 j = 0; j < 4; j++) {
                if(number_matrix[hundreds][i][j]) {
                    u8 index = polypad_xy_to_index(i - 1, j + 4);
                    hal_plot_led(TYPEPAD, index, 0, MAXLED, MAXLED);
                }
            }
        }
    }
}

void polypad_clear_grid() {
    for(u8 i = 0; i < 8; i++) {
        for(u8 j = 0; j < 8; j++) {
            hal_plot_led(TYPEPAD, polypad_xy_to_index(i, j), 0, 0, 0);
        }
    }
}

void polypad_color_octave_arrows(u8* startingNote) {
    u8 octLed = polypad_note_to_led_intensity(*startingNote);
    hal_plot_led(TYPEPAD, 91, 0, octLed, 0);
    hal_plot_led(TYPEPAD, 92, 0, octLed, 0);
    g_GridColors[91] = octLed;
    g_GridColors[92] = octLed;
}

void polypad_initialize_grid() {
    
    //note grid
    u8 chromatic_scale[12] = {2,0,1,0,1,1,0,1,0,1,0,1};
    
    for(u8 i = 0; i < 8; i++) {
        u8 offset = 0;
        for(u8 j = 0; j < 8; j++) {
            offset = j * 5;
            u8 index = polypad_xy_to_index(i, j);
            if(chromatic_scale[(i + offset) % 12] == 2) {
                g_GridColors[index] = 100;
                hal_plot_led(TYPEPAD, index, MAXLED, 0, 0);
            } else if(chromatic_scale[(i + offset) % 12] == 1) {
                g_GridColors[index] = 010;
                hal_plot_led(TYPEPAD, index, 0, MAXLED, 0);
            } else {
                g_GridColors[index] = 000;
                hal_plot_led(TYPEPAD, index, 0, 0, 0);
            }
        }
        
        arpeggiator_init(&g_arpeggiators[i]);
    }
    
    //octave arrows
    u8 startingNote = 60;
    polypad_color_octave_arrows(&startingNote);
    
    //tempo arrows
    hal_plot_led(TYPEPAD, 93, 0, 30, 30);
    hal_plot_led(TYPEPAD, 94, 0, 30, 30);
    g_GridColors[93] = 30;
    g_GridColors[94] = 30;
    
    //track buttons
    for(u8 i = 19; i < 99; i += 10) {
        hal_plot_led(TYPEPAD, i, 1, 0, 1);
        g_GridColors[i] = 1;
    }
    
    //quantize button
    hal_plot_led(TYPEPAD, 40, 1, 0, 1);
    g_GridColors[40] = 1;
}

u16 polypad_bpm_to_ms(u8 bpm) {
    return 30000 / bpm;
}

u8 polypad_ms_to_bpm(u16 ms) {
    return 30000 / ms;
}

u8 polypad_xy_to_midi_note(u8 startingNote, u8 x, u8 y) {
    return startingNote + x + (5 * y);
}

u8 polypad_note_to_led_intensity(u8 startingNote) {
    u8 intensity = startingNote >> 1;
    return intensity <= MAXLED ? intensity : MAXLED;
}

u8 polypad_semitoneoffset_to_index(u8 startIndex, u8 startNote, u8 offset) {
    u8 y = polypad_index_to_x(startIndex);
    u8 newY = y + offset % 5;
    u8 newX = offset - (5 * newY);
    return polypad_xy_to_index(newX, newY);
}

void polypad_make_note(u8* startingNote, struct Arpeggiator* arpeggiator, u8 arpIndex) {
    u8 stepIndex = arpeggiator->state.step % arpeggiator->length;
    
    if(arpeggiator->arpeggio[stepIndex] == 0) {
        polypad_note_on(arpeggiator->state.baseNote, arpIndex, arpeggiator->index);
    } else if(arpeggiator->arpeggio[stepIndex] < 255) {
        u8 newIndex = polypad_semitoneoffset_to_index(arpeggiator->index, arpeggiator->state.baseNote, arpeggiator->arpeggio[stepIndex]);
        polypad_note_on(arpeggiator->arpeggio[stepIndex] + arpeggiator->state.baseNote, arpIndex, newIndex);
    }
    
    arpeggiator->state.step = stepIndex + 1;
}

void polypad_note_on(u8 note, u8 arpIndex, u8 padIndex) {
    hal_send_midi(DINMIDI, NOTEON | g_Midi_Channel, note, 127);
    
    if(padIndex % 10 != 9)
        polypad_pad_light_on(padIndex);
    
    g_ActiveNotes[arpIndex][0] = note;
    g_ActiveNotes[arpIndex][1] = padIndex;
}

void polypad_note_off(u8 note, u8 arpIndex, u8 padIndex) {
    hal_send_midi(DINMIDI, NOTEOFF | g_Midi_Channel, note, 0);
    g_ActiveNotes[arpIndex][0] = 0;
    g_ActiveNotes[arpIndex][1] = padIndex;
    polypad_pad_light_restore(padIndex);
}

void polypad_on_beat(u8* startingNote) {
    for(u8 i = 0; i < 8; i++) {
        if(g_ActiveNotes[i][0]) {
            polypad_note_off(g_ActiveNotes[i][0], i, g_ActiveNotes[i][1]);
        }
        if(g_arpeggiators[i].state.isPlaying || g_arpeggiators[i].state.isLatched) {
            polypad_make_note(startingNote, &g_arpeggiators[i], i);
        }
    }
}
