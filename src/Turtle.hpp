//
//  Turtle.hpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//
//https://github.com/daanvanhasselt/snippets/tree/master/LSystem
//Turtle is for creating the lines and forms. Draw the axiom into the draw.

#ifndef Turtle_hpp
#define Turtle_hpp

#include "ofMain.h"
#include "Branch.h"
#include "Leaf.h"
#include "Flower.h"
#include "Geometry.hpp"

class Turtle {
public:
    Turtle();
    Turtle(string forward, string left, string right);
    
    
    void setAngle(float angle);
    void setLength(float length);


    void draw(string input, float x, float y, float z);

//    ofVboMesh mesh;
//    ofVboMesh branchMesh;
//    ofVboMesh leafMesh;

    
    //the container of nodes can be stored here.
    //shared_ptr is a pointer object that removes itself when empty of refs or something I think.
    std::vector<shared_ptr<ofNode> > nodesContainer;
    std::vector<shared_ptr<ofNode> > leafContainer;
    std::vector<shared_ptr<ofNode> > flowerContainer;


    std::vector<shared_ptr<ofNode> > bookmarks;
    std::vector<Branch> branchContainer;
    
//    shared_ptr<ofNode> startingPt;
//    ofVec3f startPtPos;
    
//    of3dPrimitive leaf;

    
protected:

    float angle;
    float length;
    float x;
    float y;
    float z;
    
    bool fillPolygon;
    bool flowerFill;


    bool branchAlreadySaved(const Branch &newBranch);
    Geometry lineMesh;
    Geometry meshGeo;
    
    
    void pushValues();
    void popValues();
};

#endif /* Turtle_hpp */
