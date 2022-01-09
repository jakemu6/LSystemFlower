//
//  Leaf.h
//  LSystemFlower
//
//  Created by Jake Mu on 8/1/22.
//

#pragma once
#include "ofMain.h"

class Leaf {
public:
    Leaf(const vector<shared_ptr<ofNode> > &leafContainer) {
        container = leafContainer;
    };
    
    vector<shared_ptr<ofNode> > container;
};
