//
//  arrangements.hpp
//  LSystemFlower
//
//  Created by Jake Mu on 14/8/2022.
//

#pragma once
#include "ofMain.h"
#include "LSystem.h"
#include "Turtle.hpp"

//typedef enum {
//lillies, // these can have any name you want, eg STATE_CLAP etc
//lavender,
//palm
//} Names;
enum types {
    palm,
    branch,
    lavender,
    flowerBall,
    phyllotaxis,
    fan,
    acro,
    sigma,
    alpha,
    beta
};

class Systems {
public:
    Systems();
    void createSystem(types select_types, int variations, int maxAxiomLevel);
    void renderArrangement(ofVec3f startPos, ofVec3f angle, int varNum, float axiomLevel);
    void overwriteCol(ofColor & lineCol, ofColor & poly1Col, ofColor & poly2Col);

    //length of segments
    float length = 10;
    //angle of segments
    float theta = 5;
    
    LSys sys;
    vector<vector <string> > res;
    Turtle turt;
    
    ofColor branchCol;
    ofColor poly1Col;
    ofColor poly2Col;
};
