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


    void draw(string input, float x, float y, float angle);
    void moveForward();
    void moveForwardNoLine();

    void turnLeft();
    void turnRight();
    
    void pitchDown();
    void pitchUp();
    
    void rollLeft();
    void rollRight();
    
    ofVec3f rotateVector(ofMatrix3x3 rotationMatrix, ofVec3f pVector);
    
protected:
    string forward;
    string anotherForward;
    string noDrawForward;


    string left;
    string right;
    
    float angle;
    
    //being replaced by rotationU
    float curAngle;
    
    // this unit vector is only for direction
    ofVec3f unitDirectionVector;
    
    float length;
    float x;
    float y;
    float z;
    
    vector<float> xHis;
    vector<float> yHis;
    vector<float> aHis;
    
    void pushValues();
    void popValues();
};

#endif /* Turtle_hpp */
