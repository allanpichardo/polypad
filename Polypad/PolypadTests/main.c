//
//  main.cpp
//  PolypadTests
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#include "arpeggiator.h"
#include "app_defs.h"

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    struct Arpeggiator arpeggiator;
    
    arpeggiator_init(&arpeggiator);
    
    printf("%d",sizeof(arpeggiator));
    printf("\n");
    
    
    
    return 0;
}
