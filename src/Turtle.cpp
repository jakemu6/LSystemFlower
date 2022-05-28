//
//  Turtle.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 23/8/21.
//

#include "Turtle.hpp"

Turtle::Turtle() {
}

void Turtle::setup(float & _angle, float & _length, ofColor & lineCol, ofColor & poly1Col, ofColor & poly2Col) {
    angle = _angle;
    length = _length;
    lineMesh.setup();
    meshGeo.setup();

    lineMesh.setBranchColor(lineCol);
    meshGeo.setP1Color(poly1Col);
    meshGeo.setP2Color(poly2Col);
}

void Turtle::draw(string & input, const float & _x, const float & _y, const float & _z) {
    
    bookmarks.clear();
    nodesContainer.clear();
    branchContainer.clear();
    leafContainer.clear();
    flowerContainer.clear();

    
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
                
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, ofToFloat(value), 0);
                nodesContainer.push_back(newPoint);
                
                if (fillPolygon) {
                    leafContainer.push_back(newPoint);
                } else if (flowerFill) {
                    flowerContainer.push_back(newPoint);
                } else {
                    //save each segment seperately so that when it's drawn to a mesh the push pop doesn't cause problems
                    //checks each branch in the container to make sure that there are no overlaps but this ends up being slower.
                    auto newBranch = Branch(*previousPoint, *newPoint);
                    lineMesh.generate(newBranch);
                }
                i+=closed;

                
            } else {
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, length, 0);
                nodesContainer.push_back(newPoint);
                
                if (fillPolygon) {
                    leafContainer.push_back(newPoint);
                } else if (flowerFill) {
                    flowerContainer.push_back(newPoint);
                } else {
                    //save each segment seperately so that when it's drawn to a mesh the push pop doesn't cause problems
                    //checks each branch in the container to make sure that there are no overlaps but this ends up being slower.
                    auto newBranch = Branch(*previousPoint, *newPoint);
                    lineMesh.generate(newBranch);
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

                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                //FORWARD NO LINE
                auto previousPoint = nodesContainer.back();
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, ofToFloat(value), 0);
                nodesContainer.push_back(newPoint);
                i+=closed;

                
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

                string value = truncatedCurrentStr.substr(open + 1, closed - 2);

                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->rollDeg(ofToFloat(value));
                nodesContainer.push_back(rotatingPoint);
                i+=closed;
                
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
                
                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->tiltDeg(ofToFloat(value));
                nodesContainer.push_back(rotatingPoint);
                i+=closed;

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
        else if(substr[i] == "%") {
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

                shared_ptr<ofNode> rotatingPoint(new ofNode);
                rotatingPoint->setParent(*nodesContainer.back());
                rotatingPoint->panDeg(-ofToFloat(value));
                nodesContainer.push_back(rotatingPoint);
                i+=closed;

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
            if(substr[i + 1] == "(") {
                //if parametric check the paraBools to see if it satisfies
                //need to get the value in brackets and substitute values into the bool
                string truncatedCurrentStr = input.substr(i, stringLength);
                
                //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                int open = truncatedCurrentStr.find("(");
                int closed = truncatedCurrentStr.find(")");
//
                string value = truncatedCurrentStr.substr(open + 1, closed - 2);
                
                //if in the axiom there is a comma, use the first value to determine the amount to move G by.
                //This is used in leaf for adding growth rule
                if (value.find(",") != std::string::npos) {
                    vector<string> splitValue;
                    splitValue = ofSplitString(value, ",");
                    shared_ptr<ofNode> newPoint(new ofNode);
                    newPoint->setParent(*nodesContainer.back());
                    newPoint->move(0, ofToFloat(splitValue[0]), 0);
                    nodesContainer.push_back(newPoint);
                } else {
                    shared_ptr<ofNode> newPoint(new ofNode);
                    newPoint->setParent(*nodesContainer.back());
                    newPoint->move(0, ofToFloat(value), 0);
                    nodesContainer.push_back(newPoint);
                }
                i+=closed;

            } else {
                shared_ptr<ofNode> newPoint(new ofNode);
                newPoint->setParent(*nodesContainer.back());
                newPoint->move(0, length, 0);
                nodesContainer.push_back(newPoint);
            }
        }
        else if(substr[i] == "#") {
            shared_ptr<ofNode> newPoint(new ofNode);
            newPoint->setParent(*nodesContainer.back());
            //add a new point to the leafcontainer at the position of the .
            if (fillPolygon) {
                leafContainer.push_back(newPoint);
            } else if (flowerFill) {
                flowerContainer.push_back(newPoint);
            }
            else {
                nodesContainer.push_back(newPoint);
            }
        }
        else if(substr[i] == "{") {
            //the curly brackets indicate that this needs to be a filled polygon
            //Init the first root of the leafcontainer
            //set position and add it to the vector/sharedptr thingo
            //this is also the starting point
            shared_ptr<ofNode> root(new ofNode);
            root->setParent(*nodesContainer.back());
            
            //create a starting root position for the leaf
            leafContainer.push_back(root);
            fillPolygon = true;
            
        }
        else if(substr[i] == "}") {
            //when all the nodes are in the leafcontainer create a leaf object out of the nodes
            fillPolygon = false;
            auto newLeaf = Leaf(leafContainer);

            meshGeo.generateLeaf(newLeaf);
            leafContainer.clear();
        }
        else if(substr[i] == "<") {
            //the curly brackets indicate that this needs to be a filled polygon
            //Init the first root of the leafcontainer
            //set position and add it to the vector/sharedptr thingo
            //this is also the starting point
            shared_ptr<ofNode> root(new ofNode);
            root->setParent(*nodesContainer.back());
            
            //create a starting root position for the leaf
            flowerContainer.push_back(root);
            flowerFill = true;
            
        }
        else if(substr[i] == ">") {
            //when all the nodes are in the leafcontainer create a leaf object out of the nodes
            flowerFill = false;
            auto newFlower = Flower(flowerContainer);
            
            meshGeo.generateFlower(newFlower);
            flowerContainer.clear();
        }
    }
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
