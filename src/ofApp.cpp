#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //addVariable is for values that can be replaced
    system.addVariable("F");
    system.addVariable("L");
    system.addVariable("R");


    //Print sends to console
    system.printVariables();

    //addConstant is for values in the string which can not be replaced
    system.addConstant("-");
    system.addConstant("+");
//    system.addConstant("[");
//    system.addConstant("]");
    //Print sends to console
    system.printConstants();

    //setStart is the starting axiom
    system.setStart("-L");
    system.printStart();

    //addRule is for changing the variables in each level
    system.addRule(LRule("L", "LF+RFR+FL-F-LFLFL-FRFR+"));
    system.addRule(LRule("R", "-LFLF+RFRFR+F+RF-LFL-FR"));
    system.printRules();
    
    length = 10.0;

    
    
    //character for move forward turn left/right
    //[] already set for save and restore state
    turtle = Turtle("F", "-", "+");
//    turtle.setAnotherForward("G");
//        turtle.setNoDrawForward("f");

    turtle.setAngle(90);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    axiomLevel = ofMap(ofGetMouseX(), 0, 1024, 0, 10);
    axiom = system.getLevel(3);
    ofLog() << "axiom = " << axiom;

//    length = ofMap(ofGetMouseX(), 0, 1024, 0.1, 20);
    turtle.setLength(length);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    turtle.draw(axiom, ofGetWidth()/2, ofGetHeight()/2 , 90); // input string, x, y, starting angle
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
