#pragma once
#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"
#include "Flower.h"


class Geometry{
public:
    
    bool isShaderDirty;
    shared_ptr<ofShader>    mShdInstanced;
    ofTexture    mTexDepth;

    
    void setup();
    void generate(const Branch & branch);
    
    void setBranchColor(ofColor & Col);
    void setP1Color(ofColor & Col);
    void setP2Color(ofColor & Col);
    
    void generateLeaf(const Leaf & leaf);
    void generateFlower(const Flower & flower);
protected:
    ofColor branchColor;
    ofColor p1Color;
    ofColor p2Color;
};
