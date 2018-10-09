//
//  dotmatrix.h
//  PolyPadLib
//
//  Created by Allan Pichardo on 10/9/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#ifndef dotmatrix_h
#define dotmatrix_h

#include "app_defs.h"

u8 matrix_zero[3][4] =  [1,1,1,1],
                        [1,0,0,1],
                        [1,1,1,1];

u8 matrix_one[3][4] =   [0,0,0,0],
                        [1,1,1,1],
                        [0,0,0,0];

u8 matrix_two[3][4] =   [0,0,0,0],
                        [1,1,0,1],
                        [1,0,1,1];

u8 matrix_three[3][4] =     [1,0,0,1],
                            [1,0,1,1],
                            [1,1,1,1];

u8 matrix_four[3][4] =      [0,1,1,1],
                            [0,1,0,0],
                            [1,1,1,0];

u8 matrix_five[3][4] =      [0,0,0,0],
                            [1,0,1,1],
                            [1,1,0,1];

u8 matrix_six[3][4] =   [0,0,0,0],
                        [1,1,1,1],
                        [1,1,0,0];

u8 matrix_seven[3][4] =     [0,0,0,0],
                            [0,0,0,1],
                            [1,1,1,1];

u8 matrix_eight[3][4] =     [1,1,1,1],
                            [1,0,1,1],
                            [1,1,1,1];

u8 matrix_nine[3][4] =      [0,0,0,0],
                            [0,0,1,1],
                            [1,1,1,1];

#endif /* dotmatrix_h */
