//
//  Leaf.h
//  LSystemFlower
//
//  Created by Jake Mu on 8/1/22.
//

#pragma once
#include "ofMain.h"

class Flower {
public:
    Flower(const vector<shared_ptr<ofNode> > &flowerContainer) {
        container = flowerContainer;
    };
    vector<shared_ptr<ofNode> > container;
};
