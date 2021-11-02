//
//  Turtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//

#include "Turtle.hpp"

Turtle::Turtle() {
    
    branchMesh.setMode(OF_PRIMITIVE_LINES);
//    mesh.enableColors();
    
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
    branchContainer.clear();

}


void Turtle::setAngle(float _angle) {
    angle = _angle;
    
}

void Turtle::setLength(float _length) {
    length = _length;
}


void Turtle::draw(string input, float _x, float _y, float _z) {
    
    bookmarks.clear();
    nodesContainer.clear();
    branchContainer.clear();

    
    branchMesh.clear();
//    mesh.clear();

    
    x = _x;
    y = _y;
    z = _z;
    
    //Init the first root of the nodecontainer
    //set position and add it to the vector/sharedptr thingo
    shared_ptr<ofNode> root(new ofNode);
    root->setPosition(x, y, z);
    nodesContainer.push_back(root);
    

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
            nodesContainer.push_back(newPoint);
            
            //save each segment seperately so that when it's drawn to a mesh the push pop doesn't cause problems
//            checks each branch in the container to make sure that there are no overlaps but this ends up being slower.

            auto newBranch = Branch(*previousPoint, *newPoint);
            lineMesh.generate(newBranch, branchMesh);

            
//            if (!branchAlreadySaved(newBranch)) {
//                //send the branch, a mesh and the length of the branch to this.
//                lineMesh.generate(newBranch, branchMesh);
//                branchContainer.push_back(newBranch);
//            }

        }
        else if(substr[i] == noDrawForward) {
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
        else if(substr[i] == "L") {
            //DRAW LEAF
            shared_ptr<ofNode> flowerPoint(new ofNode);
            flowerPoint->setParent(*nodesContainer.back());
            ofEnableDepthTest();
            ofSetColor(100);
            ofFill();
            ofDrawSphere(flowerPoint->getGlobalPosition(), 1);
            ofDisableDepthTest();
        }
    }
    branchMesh.draw();

}

//Check the branchContainer to see if there have already been branches in the same position.
bool Turtle::branchAlreadySaved(Branch newBranch){
    for (auto savedBranch:branchContainer) {
        if(newBranch.begin.getGlobalPosition() == savedBranch.begin.getGlobalPosition() &&
           newBranch.end.getGlobalPosition() == savedBranch.end.getGlobalPosition()){
            return true;
        }
    }
    return false;
};
