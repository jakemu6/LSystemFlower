//
//  Turtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//

#include "Turtle.hpp"

Turtle::Turtle() {
    angle = 90;
    curAngle = 0;
    length = 10;
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
}

Turtle::Turtle(string _forward, string _left, string _right) {
    forward = _forward;
    left = _left;
    right = _right;
    
    //default values that are replaced with setLength and setAngle called in ofApp.cpp
    angle = 90;
    length = 10;
    curAngle = 0;
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
}

void Turtle::setAngle(float _angle) {
    angle = _angle;
    
}

void Turtle::setLength(float _length) {
    length = _length;
}

void Turtle::setAnotherForward(string _forward) {
    anotherForward = _forward;
}

void Turtle::setNoDrawForward(string _noDrawForward) {
    noDrawForward = _noDrawForward;
}

void Turtle::draw(string input, float _x, float _y, float _angle) {
    x = _x;
    y = _y;
    curAngle = _angle;
    
    //get length of the input string
    int length = input.length();
    
    ofLog() << "length: " << length;
    
    //split the string into 1 character
    string substr[length];
    for(int i = 0; i < length; i++) {
        substr[i] = input.substr(i, 1);
    }
    
    //check every character and act accordingly
    for(int i = 0; i < length; i++) {
        if(substr[i] == forward)
            moveForward();
        if(substr[i] == anotherForward)
            moveForward();
        if(substr[i] == noDrawForward)
            moveForwardNoLine();
        if(substr[i] == left)
            turnLeft();
        if(substr[i] == right)
            turnRight();
        if(substr[i] == "[")
            pushValues();
        if(substr[i] == "]")
            popValues();
    }
}

void Turtle::pushValues(){
    xHis.push_back(x);
    yHis.push_back(y);
    aHis.push_back(curAngle);
//    curAngle += angle;
}

void Turtle::popValues(){
    x = xHis[xHis.size()-1];
    y = yHis[yHis.size()-1];
    curAngle = aHis[aHis.size()-1];
    
    xHis.pop_back();
    yHis.pop_back();
    aHis.pop_back();
//    curAngle -= angle;
}

void Turtle::turnLeft(){
//    cout << "turn left" << endl;
    curAngle += angle;
}

void Turtle::turnRight(){
//    cout << "turn right" << endl;
    curAngle -= angle;
}


void Turtle::moveForward() {
    //curAngle which is decided by turnLeft and turnRight functions determine by the degree of which way the line will move
    float newX = x + (cos(ofDegToRad(curAngle))*length);
    float newY = y + (sin(ofDegToRad(curAngle))*length);

    //cout << "move forward from: " << x << ", " << y << " to " << newX << ", " << newY << endl;
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 120);
    ofSetLineWidth(2);
    ofDrawLine(x, y, newX, newY);
    x = newX;
    y = newY;
}

void Turtle::moveForwardNoLine() {
    //curAngle which is decided by turnLeft and turnRight functions determine by the degree of which way the line will move
    float newX = x + (cos(ofDegToRad(curAngle))*length);
    float newY = y + (sin(ofDegToRad(curAngle))*length);

    x = newX;
    y = newY;
}
