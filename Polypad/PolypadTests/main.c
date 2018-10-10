//
//  main.cpp
//  PolypadTests
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#include "arpeggiator.h"
#include "app_defs.h"
#include "dotmatrix.h"

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d",number_matrix[3][j][i]);
        }
        printf("\n");
    }
    
    printf("\n");
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d",matrix_one[j][i]);
        }
        printf("\n");
    }
    
    printf("\n");
    
    int tempo = 120;
    
    int ones = tempo % 10;
    int tens = (tempo / 10) % 10;
    int hundreds = (tempo / 100) % 10;
    
    
    return 0;
}
