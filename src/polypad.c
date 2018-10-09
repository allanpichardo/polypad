//
//  polypad.c
//  PolyPadLib
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//
#include "polypad.h"
#include "app_defs.h"
#include "app.h"
#include <stdio.h>

u8 g_Octave = 4;
u8 g_GridColors[100] = {0};

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

void polypad_pad_down(u8 index) {
    polypad_pad_light_on(index);
}

void polypad_pad_up(u8 index) {
    polypad_pad_light_off(index);
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
