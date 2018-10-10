//
//  polypad.c
//  PolyPadLib
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//
#include "polypad.h"
#include "dotmatrix.h"
#include "app_defs.h"
#include "app.h"
#include <stdio.h>

/**
 Globals
 */
u8 g_GridColors[100] = {0};

/**
 Flags
 */
u8 flag_editingTempo = 0;

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

void polypad_pad_light_off(u8 index) {
    if(g_GridColors[index] == 100) {
        hal_plot_led(TYPEPAD, index, MAXLED, 0, 0);
    } else if(g_GridColors[index] == 010) {
        hal_plot_led(TYPEPAD, index, 0, MAXLED, 0);
    } else {
        hal_plot_led(TYPEPAD, index, 0, 0, 0);
    }
    
    u8 x = polypad_index_to_x(index);
    u8 y = polypad_index_to_y(index);
    if(x > 4 && y < 7) {
        y++;
        x -= 5;
        polypad_pad_light_off(polypad_xy_to_index(x, y));
    }
}

void polypad_leftarrow_down(u16* ticks) {
    u8 bpm = polypad_ms_to_bpm(*ticks);
    bpm--;
    
    if(flag_editingTempo) {
        polypad_draw_tempo_select(bpm);
    }
    
    *ticks = polypad_bpm_to_ms(bpm);
}

void polypad_rightarrow_down(u16* ticks) {
    u8 bpm = polypad_ms_to_bpm(*ticks);
    bpm++;
    
    if(flag_editingTempo) {
        polypad_draw_tempo_select(bpm);
    }
    
    *ticks = polypad_bpm_to_ms(bpm);
}

void polypad_pad_down(u8 index, u8* startingNote) {
    if(index > 10 && index < 89 && (index % 10) < 9 && (index % 10) > 0) {
        polypad_pad_light_on(index);
        
        u8 x = polypad_index_to_x(index);
        u8 y = polypad_index_to_y(index);
        printf("%d\n", polypad_xy_to_midi_note(*startingNote, x, y));
    }
}

void polypad_click_down(u8 bpm) {
    flag_editingTempo = 1;
    polypad_draw_tempo_select(bpm);
}

void polypad_pad_up(u8 index) {
    polypad_pad_light_off(index);
}

void polypad_click_up() {
    flag_editingTempo = 0;
    polypad_restore_grid_from_store();
}

void polypad_uparrow_down(u8* startingNote) {
    *startingNote = *startingNote + 12;
}

void polypad_downarrow_down(u8* startingNote) {
    *startingNote = *startingNote - 12;
}

void polypad_restore_grid_from_store() {
    for(u8 i = 0; i < 100; i++) {
        if(g_GridColors[i] == 100) {
            hal_plot_led(TYPEPAD, i, MAXLED, 0, 0);
        } else if(g_GridColors[i] == 010) {
            hal_plot_led(TYPEPAD, i, 0, MAXLED, 0);
        } else {
            hal_plot_led(TYPEPAD, i, 0, 0, 0);
        }
    }
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

void polypad_draw_chromatic_grid() {
    
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
    }
}

u16 polypad_bpm_to_ms(u8 bpm) {
    return 60000 / bpm;
}

u8 polypad_ms_to_bpm(u16 ms) {
    return 60000 / ms;
}

u8 polypad_xy_to_midi_note(u8 startingNote, u8 x, u8 y) {
    return startingNote + x + (5 * y);
}
