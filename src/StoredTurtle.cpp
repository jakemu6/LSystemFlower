//
//  StoredTurtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 7/4/2022.
//

#include "StoredTurtle.hpp"

StoredTurtle::StoredTurtle() {
}

void StoredTurtle::setup(vector<vector <string> > & axioms, float & _angle, float & _length, ofVec3f _startingPos) {
    
    angle = _angle;
    length = _length;
    
    startingPos = _startingPos;
    
    for (int i = 0; i < axioms.size(); i++) {
        for (int j = 0; j < axioms[i].size(); j++) {
            
            
            
            
        }
    }
}

void StoredTurtle::update() {
    
}

void StoredTurtle::draw() {
    
}
