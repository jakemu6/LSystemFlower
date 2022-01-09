//
//  Turtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//

#include "Turtle.hpp"

Turtle::Turtle() {
    
    branchMesh.setMode(OF_PRIMITIVE_LINES);
    leafMesh.setMode(OF_PRIMITIVE_LINES);

//    leafMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

//    mesh.enableColors();
    
    //    unitDirectionVector.set(1.0f, 1.0f, 1.0f);
    //
    //    unitDirectionVectorU.set(1.0f, 1.0f, 1.0f);
    //    unitDirectionVectorL.set(1.0f, 1.0f, 1.0f);
    //    unitDirectionVectorH.set(1.0f, 1.0f, 1.0f);
    
    //Basic Init of variables,
    //Should all be changed further down with setAngle and setLength
//    angle = 90;
//    length = 10;

    x = 0;
    y = 0;
    z = 0;
    
    bookmarks.clear();
    nodesContainer.clear();
    branchContainer.clear();
    leafContainer.clear();
//    //LEAF PRIMITIVE SETUP
//    leaf.getMesh().addVertex(ofVec3f(0,0));
//    leaf.getMesh().addVertex(ofVec3f(40,20));
//    leaf.getMesh().addVertex(ofVec3f(40,40));
//    leaf.getMesh().addVertex(ofVec3f(20,40));
//    leaf.getMesh().setMode(OF_PRIMITIVE_TRIANGLE_FAN);
//
//
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
    leafContainer.clear();
    
    branchMesh.clear();
    leafMesh.clear();

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
            
            //check if parametric
            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                float floatVal = ofToFloat(value);

                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, floatVal, 0);
                nodesContainer.push_back(newPoint);
                
                if (fillPolygon) {
                    leafContainer.push_back(newPoint);
                } else {
                    //save each segment seperately so that when it's drawn to a mesh the push pop doesn't cause problems
                    //checks each branch in the container to make sure that there are no overlaps but this ends up being slower.
                    auto newBranch = Branch(*previousPoint, *newPoint);
                    lineMesh.generate(newBranch, branchMesh);
                }
                
                
            } else {
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, length, 0);
                nodesContainer.push_back(newPoint);
                
                if (fillPolygon) {
                    leafContainer.push_back(newPoint);
                } else {
                    //save each segment seperately so that when it's drawn to a mesh the push pop doesn't cause problems
                    //checks each branch in the container to make sure that there are no overlaps but this ends up being slower.
                    auto newBranch = Branch(*previousPoint, *newPoint);
                    lineMesh.generate(newBranch, branchMesh);
                }
            }
        }
        else if(substr[i] == "f") {
            //FORWARD NO LINE

            //check if parametric
            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                float floatVal = ofToFloat(value);

                //FORWARD NO LINE
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, floatVal, 0);
                nodesContainer.push_back(newPoint);
                
            } else {
            
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, length, 0);
                nodesContainer.push_back(newPoint);
            }
            
        }
        else if(substr[i] == "+") {
            //TURN LEFT
            
            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                float floatVal = ofToFloat(value);

                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->rollDeg(floatVal);
                nodesContainer.push_back(rotatingPoint);
                
            } else {
            
                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->rollDeg(angle);
                nodesContainer.push_back(rotatingPoint);
        
            }
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

            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                float floatVal = ofToFloat(value);

                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->tiltDeg(floatVal);
                nodesContainer.push_back(rotatingPoint);
                
            } else {
            
                //PITCH DOWN
                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->tiltDeg(angle);
                nodesContainer.push_back(rotatingPoint);
        
            }
            

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
            
            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                float floatVal = ofToFloat(value);

                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->panDeg(-floatVal);
                nodesContainer.push_back(rotatingPoint);
                
            } else {
            
                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->panDeg(-angle);
                nodesContainer.push_back(rotatingPoint);
        
            }
            

        }
        else if(substr[i] == "|") {
            //TURN AROUND
            shared_ptr<ofNode> rotatingPoint(new ofNode);
            rotatingPoint->setParent(*nodesContainer.back());
            rotatingPoint->rollDeg(180);
            nodesContainer.push_back(rotatingPoint);
        }
        else if(substr[i] == "G") {
            shared_ptr<ofNode> newPoint(new ofNode);
            newPoint->setParent(*nodesContainer.back());
            newPoint->move(0, length, 0);
            nodesContainer.push_back(newPoint);
            
        }
//        else if(substr[i] == ".") {
//            shared_ptr<ofNode> newPoint(new ofNode);
//            newPoint->setParent(*nodesContainer.back());
//            leafContainer.push_back(newPoint);
////            ofLog() << startPtPos;
//
////            shared_ptr<ofNode> startingPt(new ofNode);
////            startingPt->setPosition(startPtPos);
//            nodesContainer.push_back(startingPt);
//        }
        else if(substr[i] == "{") {
            //the curly brackets indicate that this needs to be a filled polygon
            //Init the first root of the leafcontainer
            //set position and add it to the vector/sharedptr thingo
            //this is also the starting point
            shared_ptr<ofNode> root(new ofNode);
            root->setParent(*nodesContainer.back());
//            startPtPos = root->getGlobalPosition();
            startingPt = root;
            

            
//            startPtPos = root->getGlobalPosition();
//            startingPt->setGlobalPosition(root->getGlobalPosition());
            leafContainer.push_back(root);
            
            fillPolygon = true;
            
        }
        else if(substr[i] == "}") {
            //when all the nodes are in the leafcontainer create a leaf object out of the nodes
            fillPolygon = false;

            
            auto newLeaf = Leaf(leafContainer);
            meshGeo.generateLeaf(newLeaf, leafMesh);

            leafContainer.clear();
        }
        
//        else if(substr[i] == "L") {
//            //DRAW Flower
//            shared_ptr<ofNode> flowerPoint(new ofNode);
////            flowerPoint->setParent(*nodesContainer.back());
//            ofEnableDepthTest();
//            ofSetColor(0, 255, 0, 255);
//            ofFill();
//            leaf.setParent(*nodesContainer.back());
//            leaf.draw();
////            ofDrawSphere(flowerPoint->getGlobalPosition(), 1);
//
//            ofSetColor(255);
//
//            ofDisableDepthTest();
//        }
    }
    branchMesh.draw();
//    leafMesh.draw();

}

//Check the branchContainer to see if there have already been branches in the same position.
bool Turtle::branchAlreadySaved(const Branch &newBranch){
    for (auto savedBranch:branchContainer) {
        if(newBranch.begin.getGlobalPosition() == savedBranch.begin.getGlobalPosition() &&
           newBranch.end.getGlobalPosition() == savedBranch.end.getGlobalPosition()){
            return true;
        }
    }
    return false;
};
