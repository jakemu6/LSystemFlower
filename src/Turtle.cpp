//
//  Turtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//

#include "Turtle.hpp"

Turtle::Turtle() {
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.enableColors();
    
    //    unitDirectionVector.set(1.0f, 1.0f, 1.0f);
    //
    //    unitDirectionVectorU.set(1.0f, 1.0f, 1.0f);
    //    unitDirectionVectorL.set(1.0f, 1.0f, 1.0f);
    //    unitDirectionVectorH.set(1.0f, 1.0f, 1.0f);
    
    //Basic Init of variables,
    //Should all be changed further down with setAngle and setLength
    angle = 90;
    length = 10;

    x = 0;
    y = 0;
    z = 0;
    
    bookmarks.clear();
    nodesContainer.clear();
}

//Turtle::Turtle(string _forward, string _left, string _right) {
//    forward = _forward;
//    left = _left;
//    right = _right;
//
//    //default values that are replaced with setLength and setAngle called in ofApp.cpp
//    angle = 90;
//    length = 10;
//    curAngle = 0;
//    unitDirectionVector.set(1.0f, 1.0f, 1.0f);
//
//    unitDirectionVectorU.set(1.0f, 1.0f, 1.0f);
//    unitDirectionVectorL.set(1.0f, 1.0f, 1.0f);
//    unitDirectionVectorH.set(1.0f, 1.0f, 1.0f);
//
//    x = ofGetWidth()/2;
//    y = ofGetHeight()/2;
//    z = 0;
//
//}

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

void Turtle::draw(string input, float _x, float _y, float _z) {
    

    
    //Init the first root of the nodecontainer
    //set position and add it to the vector/sharedptr thingo
    shared_ptr<ofNode> root(new ofNode);
    root->setPosition(x, y, z);
    nodesContainer.push_back(root);
    mesh.addVertex(root->getGlobalPosition());
    mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));
    
    
    
//    x = _x;
//    y = _y;
//    z = _z;
//
//    curAngle = _angle;
//    unitDirectionVector.set(1.0f, 1.0f, 1.0f);
//
//    unitDirectionVectorU.set(1.0f, 1.0f, 1.0f);
//    unitDirectionVectorL.set(1.0f, 1.0f, 1.0f);
//    unitDirectionVectorH.set(1.0f, 1.0f, 1.0f);

    //get length of the input string
    int stringLength = input.length();
        
    
    //split the string into 1 character
    string substr[stringLength];
    for(int i = 0; i < stringLength; i++) {
        substr[i] = input.substr(i, 1);
    }
    
    //check every character and act accordingly
    for(int i = 0; i < stringLength; i++) {
        if(substr[i] == "F") {
            auto previousPoint = nodesContainer.back();
            shared_ptr<ofNode> newPoint(new ofNode);
            newPoint->setParent(*nodesContainer.back());
            newPoint->move(0, length, 0);
            mesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
            mesh.addVertex(newPoint->getGlobalPosition());
            nodesContainer.push_back(newPoint);
        }
        else if(substr[i] == noDrawForward) {
            moveForwardNoLine();
        }
        else if(substr[i] == "+") {
            //TURN LEFT
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->rollDeg(angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "-") {
            //TURN RIGHT
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->rollDeg(-angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "[") {
            bookmarks.push_back(nodesContainer.back());
        }
        else if(substr[i] == "]") {
            nodesContainer.push_back(bookmarks.back());
            bookmarks.pop_back();
        }
        else if(substr[i] == "&") {
            //PITCH DOWN
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->tiltDeg(angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "^") {
            //PITCH UP
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->tiltDeg(-angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "?") {
            //ROLL LEFT
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->panDeg(angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "/") {
            //ROLL RIGHT
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->panDeg(-angle);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "|") {
            //TURN AROUND
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->rollDeg(180);
            nodesContainer.push_back(rotatingPoint);
        }
    }
    
    
    mesh.draw();
    //clear the nodeContainer each time to get it
    nodesContainer.clear();
    bookmarks.clear();
}

void Turtle::pushValues(){
//    xHis.push_back(x);
//    yHis.push_back(y);
//    zHis.push_back(z);
//
//    unitDirectionUnityHis.push_back(unitDirectionVector);
//    unitDirectionUnityHisU.push_back(unitDirectionVectorU);
//    unitDirectionUnityHisL.push_back(unitDirectionVectorL);
//    unitDirectionUnityHisH.push_back(unitDirectionVectorH);

}

void Turtle::popValues(){
//    x = xHis[xHis.size()-1];
//    y = yHis[yHis.size()-1];
//    z = zHis[zHis.size()-1];
//    unitDirectionVector = unitDirectionUnityHis[unitDirectionUnityHis.size()-1];
//    unitDirectionVectorU = unitDirectionUnityHisU[unitDirectionUnityHisU.size()-1];
//    unitDirectionVectorL = unitDirectionUnityHisL[unitDirectionUnityHisL.size()-1];
//    unitDirectionVectorH = unitDirectionUnityHisH[unitDirectionUnityHisH.size()-1];
//
//
//    xHis.pop_back();
//    yHis.pop_back();
//    zHis.pop_back();
}


void Turtle::pitchDown(){
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = cosf(angle);     rotationMatrix.b = 0;      rotationMatrix.c = -sinf(angle);
    rotationMatrix.d = 0;               rotationMatrix.e = 1;      rotationMatrix.f = 0;
    rotationMatrix.g = sinf(angle);     rotationMatrix.h = 0;      rotationMatrix.i = cosf(angle);

    unitDirectionVectorL = rotateVector(rotationMatrix, unitDirectionVectorL);
}

void Turtle::pitchUp(){
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = cosf(-angle);     rotationMatrix.b = 0;      rotationMatrix.c = -sinf(-angle);
    rotationMatrix.d = 0;                rotationMatrix.e = 1;      rotationMatrix.f = 0;
    rotationMatrix.g = sinf(-angle);     rotationMatrix.h = 0;      rotationMatrix.i = cosf(-angle);

    unitDirectionVectorL = rotateVector(rotationMatrix, unitDirectionVectorL);
}

void Turtle::rollLeft(){
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = 1;      rotationMatrix.b = 0;               rotationMatrix.c = 0;
    rotationMatrix.d = 0;      rotationMatrix.e = cosf(angle);     rotationMatrix.f = -sinf(angle);
    rotationMatrix.g = 0;      rotationMatrix.h = sinf(angle);     rotationMatrix.i = cosf(angle);

    unitDirectionVectorH = rotateVector(rotationMatrix, unitDirectionVectorH);
}
    
void Turtle::rollRight(){
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = 1;      rotationMatrix.b = 0;                rotationMatrix.c = 0;
    rotationMatrix.d = 0;      rotationMatrix.e = cosf(-angle);     rotationMatrix.f = -sinf(-angle);
    rotationMatrix.g = 0;      rotationMatrix.h = sinf(-angle);     rotationMatrix.i = cosf(-angle);

    unitDirectionVectorH = rotateVector(rotationMatrix, unitDirectionVectorH);
}
    
void Turtle::turnAround(){
    ofMatrix3x3 rotationMatrix;
    rotationMatrix.a = cosf(ofDegToRad(180));       rotationMatrix.b = sinf(ofDegToRad(180));     rotationMatrix.c = 0;
    rotationMatrix.d = -sinf(ofDegToRad(180));      rotationMatrix.e = cosf(ofDegToRad(180));     rotationMatrix.f = 0;
    rotationMatrix.g = 0;                           rotationMatrix.h = 0;                         rotationMatrix.i = 1;

    unitDirectionVectorU = rotateVector(rotationMatrix, unitDirectionVectorU);
}
    
ofVec3f Turtle::rotateVector(ofMatrix3x3 pRotationMatrix, ofVec3f pVector){
    ofVec3f result;
    result.x = pRotationMatrix.a * pVector.x + pRotationMatrix.b * pVector.y + pRotationMatrix.c *  pVector.z;
    result.y = pRotationMatrix.d * pVector.x + pRotationMatrix.e * pVector.y + pRotationMatrix.f *  pVector.z;
    result.z = pRotationMatrix.g * pVector.x + pRotationMatrix.h * pVector.y + pRotationMatrix.i *  pVector.z;

    return result;
}




void Turtle::moveForward() {
//    float newX = x + (unitDirectionVectorU*length).x;
//    float newY = y + (unitDirectionVectorL*length).y;
//    float newZ = z + (unitDirectionVectorH*length).z;
//
////    cout << "move forward from: " << x << ", " << y << ", " << z << " to " << newX << ", " << newY << ", " << newZ << endl;
//    ofEnableAlphaBlending();
//    ofSetColor(0, 0, 0, 120);
//    ofSetLineWidth(2);
//    ofDrawLine(x, y, z, newX, newY, newZ);
//    x = newX;
//    y = newY;
//    z = newZ;

    auto previousPoint = nodesContainer.back();
    shared_ptr<ofNode> newPoint(new ofNode);
    newPoint->setParent(*nodesContainer.back());
    newPoint->move(0, -100, 0);
    mesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
    mesh.addVertex(newPoint->getGlobalPosition());


}

void Turtle::moveForwardNoLine() {
//    //curAngle which is decided by turnLeft and turnRight functions determine by the degree of which way the line will move
//    float newX = x + (unitDirectionVectorU.x*length);
//    float newY = y + (unitDirectionVectorL.y*length);
//    float newZ = z + (unitDirectionVectorH.z*length);
//    x = newX;
//    y = newY;
//    z = newZ;

}
