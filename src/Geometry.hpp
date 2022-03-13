#pragma once
#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"
#include "Flower.h"


class Geometry{
public:
    void generate(const Branch branch);
    ofMesh generateLeaf(const Leaf leaf);
    ofMesh generateFlower(const Flower flower);


//    bool grow = true;
//    float growthRate = 0.1;
};
