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
    
    void draw(string input, float x, float y, float angle);
    void moveForward();
    void turnLeft();
    void turnRight();
    
protected:
    string forward;
    string left;
    string right;
    
    float angle;
    float curAngle;
    float length;
    float x;
    float y;
    
    vector<float> xHis;
    vector<float> yHis;
    vector<float> aHis;
    
    void pushValues();
    void popValues();
};

#endif /* Turtle_hpp */
