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

    void setup(float & _angle, float & _length, ofColor & lineCol, ofColor & poly1Col, ofColor & poly2Col);
    void update();
    

    void draw(string & input, const float & x, const float & y, const float & z);

    
    //the container of nodes can be stored here.
    //shared_ptr is a pointer object that removes itself when empty of refs or something I think.
    std::vector<shared_ptr<ofNode> > nodesContainer;
    std::vector<shared_ptr<ofNode> > leafContainer;
    std::vector<shared_ptr<ofNode> > flowerContainer;
    std::vector<shared_ptr<ofNode> > bookmarks;
    std::vector<Branch> branchContainer;

    float angle;
    float length;
    float x;
    float y;
    float z;
    
    bool fillPolygon;
    bool flowerFill;

    //Lines from branches
    Geometry lineMesh;
    //polygons from the flowers and leaves
    Geometry meshGeo;
    bool branchAlreadySaved(const Branch &newBranch);
    
    
protected:
};

#endif /* Turtle_hpp */
