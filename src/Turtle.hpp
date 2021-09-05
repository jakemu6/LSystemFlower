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

class Turtle {
public:
    Turtle();
    Turtle(string forward, string left, string right);
    void setAngle(float angle);
    void setLength(float length);
    void setAnotherForward(string forward);
    void setNoDrawForward(string noDrawForward);


    void draw(string input, float x, float y, float z);
    void moveForward();
    void moveForwardNoLine();

    void turnLeft();
    void turnRight();
    
    void pitchDown();
    void pitchUp();
    
    void rollLeft();
    void rollRight();
    
    void turnAround();
    
    ofVec3f rotateVector(ofMatrix3x3 rotationMatrix, ofVec3f pVector);
    
    ofVboMesh mesh;
    
    //the container of nodes can be stored here.
    //shared_ptr is a pointer object that removes itself when empty of refs or something I think.
    std::vector<shared_ptr<ofNode> > nodesContainer;
    std::vector<shared_ptr<ofNode> > bookmarks;

    
protected:
//    string forward;
    string anotherForward;
    string noDrawForward;


//    string left;
//    string right;
    
    float angle;
    
    //being replaced by rotationU
    float curAngle;
    
    // this unit vector is only for direction
    ofVec3f unitDirectionVector;
    
    ofVec3f unitDirectionVectorU;
    ofVec3f unitDirectionVectorL;
    ofVec3f unitDirectionVectorH;

    
    float length;
    float x;
    float y;
    float z;
    
    vector<float> xHis;
    vector<float> yHis;
    vector<float> zHis;

    vector<ofVec3f> unitDirectionUnityHis;
    
    vector<ofVec3f> unitDirectionUnityHisU;
    vector<ofVec3f> unitDirectionUnityHisL;
    vector<ofVec3f> unitDirectionUnityHisH;

    
    void pushValues();
    void popValues();
};

#endif /* Turtle_hpp */
