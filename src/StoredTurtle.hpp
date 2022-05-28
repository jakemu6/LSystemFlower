//
//  StoredTurtle.hpp
//  LSystemFlower
//
//  Created by Jake Mu on 7/4/2022.
//

#ifndef StoredTurtle_hpp
#define StoredTurtle_hpp

#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"
#include "Flower.h"
#include "Geometry.hpp"

class StoredTurtle {
public:
    
    StoredTurtle();

    void setup(vector<vector <string> > & axioms, float & _angle, float & _length, ofVec3f _startingPos);
    void update();
    void draw();
    
    vector<Geometry> meshes;
    
    float angle;
    float length;
    ofVec3f startingPos;
    

    
protected:
};
#endif /* StoredTurtle_hpp */
