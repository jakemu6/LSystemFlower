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
#include "Geometry.hpp"

class Turtle {
public:
    Turtle();
    Turtle(string forward, string left, string right);
    
    
    void setAngle(float angle);
    void setLength(float length);


    void draw(string input, float x, float y, float z);

//    ofVboMesh mesh;
    ofVboMesh branchMesh;

    
    //the container of nodes can be stored here.
    //shared_ptr is a pointer object that removes itself when empty of refs or something I think.
    std::vector<shared_ptr<ofNode> > nodesContainer;
    std::vector<shared_ptr<ofNode> > bookmarks;
    std::vector<Branch> branchContainer;

    
protected:
//    string forward;
    string anotherForward;
    string noDrawForward;


//    string left;
//    string right;
    
    float angle;
    
    //being replaced by rotationU
    
    
    float length;
    float x;
    float y;
    float z;

    bool branchAlreadySaved(Branch branch);
    Geometry lineMesh;
    
    void pushValues();
    void popValues();
};

#endif /* Turtle_hpp */
