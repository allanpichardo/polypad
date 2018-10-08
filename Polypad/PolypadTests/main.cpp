//
//  main.cpp
//  PolypadTests
//
//  Created by Allan Pichardo on 10/8/18.
//  Copyright © 2018 comp345. All rights reserved.
//

#include "arpeggiator.h"
#include "sequence.h"
#include "app_defs.h"

#include <iostream>
using namespace std;

void printSequence(Sequence &seq) {
    for(int i = 0; i < seq.getLength(); i++) {
        cout << seq.getSequence()[i];
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    
    Arpeggiator arpeggiator;
    
    cout << "test" << endl;
    
    for(u8 i = 0; i < arpeggiator.getLength(); i++) {
        cout << +arpeggiator.getArpeggio()[i] << ",";
    }
    cout << endl;
    
    arpeggiator.setPatern(7, 13);
    arpeggiator.setScale(Scale::minorScale);
    
    for(char i = 0; i < arpeggiator.getLength(); i++) {
        cout << +arpeggiator.getArpeggio()[i] << ",";
    }
    cout << endl;
    
    arpeggiator.shift(3);
    
    for(char i = 0; i < arpeggiator.getLength(); i++) {
        cout << +arpeggiator.getArpeggio()[i] << ",";
    }
    cout << endl;
    
    cout << "Size of Arpeggiator class: " << sizeof(Arpeggiator) << endl;
    cout << "Size of arpeggiator object: " << sizeof(arpeggiator) << endl;
    cout << endl;
    
    for(char i = 0; i < arpeggiator.getLength(); i++) {
        cout << +arpeggiator.getArpeggio()[i] + 60 << ",";
    }
    cout << endl;
    
    return 0;
}
