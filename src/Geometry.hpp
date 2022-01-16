#pragma once
#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"
#include "Flower.h"


class Geometry{
public:
    void generate(const Branch branch, ofVboMesh& mesh);
    void generateLeaf(const Leaf leaf);
    void generateFlower(const Flower flower);


//    bool grow = true;
//    float growthRate = 0.1;
};
