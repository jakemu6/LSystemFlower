//
//  Branch.h
//  LSystemFlower
//
//  Created by Jake Mu on 12/9/21.
//

#pragma once
#include "ofMain.h"


//class for saving each (F) branch as an object with the variables to be able to cross reference whether there is already a branch in there.
//This is what will end up being drawn
//later adds the cap sizes to create varying widths.
class Branch {
public:
    Branch(const ofNode &_begin, const ofNode &_end) {
        begin = _begin;
        end = _end;
    };
    ofNode begin;
    ofNode end;
};
