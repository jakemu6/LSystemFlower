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
    unitDirectionVector.set(0.0f, -1.0f, 0.0f);


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
    unitDirectionVector.set(0.0f, -1.0f, 0.0f);


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
    unitDirectionVector.set(0.0f, -1.0f, 0.0f);

    //get length of the input string
    int length = input.length();
        

    
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
//    cout << cosf( -angle ) << endl;
//    curAngle += angle;

    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = cosf( -angle );     rotationMatrix.b = sinf( -angle );     rotationMatrix.c = 0;
    rotationMatrix.d = -sinf( -angle );    rotationMatrix.e = cosf( -angle );     rotationMatrix.f = 0;
    rotationMatrix.g = 0;                  rotationMatrix.h = 0;                  rotationMatrix.i = 1;

    unitDirectionVector = rotateVector(rotationMatrix, unitDirectionVector);
    cout << unitDirectionVector << endl;

}

void Turtle::turnRight(){
//    cout << "turn right" << endl;
//    curAngle -= angle;
    
    
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = cosf(angle);       rotationMatrix.b = sinf(angle);     rotationMatrix.c = 0;
    rotationMatrix.d = -sinf(angle);      rotationMatrix.e = cosf(angle);     rotationMatrix.f = 0;
    rotationMatrix.g = 0;                 rotationMatrix.h = 0;               rotationMatrix.i = 1;

    unitDirectionVector = rotateVector(rotationMatrix, unitDirectionVector);
    cout << unitDirectionVector << endl;
}




ofVec3f Turtle::rotateVector(ofMatrix3x3 pRotationMatrix, ofVec3f pVector){
    ofVec3f result;
    result.x = pRotationMatrix.a * pVector.x + pRotationMatrix.b * pVector.y + pRotationMatrix.c *  pVector.z;
    result.y = pRotationMatrix.d * pVector.x + pRotationMatrix.e * pVector.y + pRotationMatrix.f *  pVector.z;
    result.z = pRotationMatrix.g * pVector.x + pRotationMatrix.h * pVector.y + pRotationMatrix.i *  pVector.z;

    return result;
}




void Turtle::moveForward() {
    //curAngle which is decided by turnLeft and turnRight functions determine by the degree of which way the line will move
//    float newX = x + (cos(ofDegToRad(curAngle))*length);
//    float newY = y + (sin(ofDegToRad(curAngle))*length);
    float newX = x + (unitDirectionVector.x*length);
    float newY = y + (unitDirectionVector.y*length);
    float newZ = z + (unitDirectionVector.z*length);

//    cout << "move forward from: " << x << ", " << y << " to " << newX << ", " << newY << endl;
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 120);
    ofSetLineWidth(2);
    ofDrawLine(x, y, z, newX, newY, newZ);
    x = newX;
    y = newY;
    


}

void Turtle::moveForwardNoLine() {
    //curAngle which is decided by turnLeft and turnRight functions determine by the degree of which way the line will move
    float newX = x + (unitDirectionVector.x*length);
    float newY = y + (unitDirectionVector.y*length);

    x = newX;
    y = newY;

}
