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

u8 polypad_xy_to_index(u8 x, u8 y);
void polypad_draw_chromatic_grid(void);
void polypad_pad_down(u8 index);
void polypad_pad_up(u8 index);
u8 polypad_index_to_y(u8 index);
u8 polypad_index_to_x(u8 index);

#endif /* polypad_h */
