#pragma once
#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"


class Geometry{
public:
    void generate(const Branch branch, ofVboMesh& mesh);
    void generateLeaf(const Leaf leaf, ofVboMesh& mesh);

//    bool grow = true;
//    float growthRate = 0.1;
};
