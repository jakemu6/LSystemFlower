#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(1000);
    
//    //addVariable is for values that can be replaced
//    system.addVariable("F");
//
//    //Print sends to console
//    system.printVariables();
//
//    //addConstant is for values in the string which can not be replaced
//    system.addConstant("+");
//    system.addConstant("-");
//
//    //Print sends to console
//    system.printConstants();

    //setStart is the starting axiom
    system.setStart("A");
    system.printStart();

    //addRule is for changing the variables in each level
//    system.addRule(LRule("A", "B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
//    system.addRule(LRule("B", "A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
//    system.addRule(LRule("C", "|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
//    system.addRule(LRule("D", "|CFB-F+B|FA&F^A&&FB-F+B|FC//"));
    
    system.addRule(LRule("A", "[&FLA]/////[&FLA]///////'[&FLA]"));
    system.addRule(LRule("F", "S/////F"));
    system.addRule(LRule("S", "FL"));
    system.addRule(LRule("L", "F"));


    system.printRules();
    
    turtle = Turtle();
    
    length = 10;
    theta = 22.5;
    axiomLevel = 5;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    axiom = system.getLevel(axiomLevel);
    
    rotation = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 0.5;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    
    ofPushMatrix();
    ofRotateYDeg(rotation);
    ofBackground(0, 0, 0);
    ofNoFill();
    turtle.draw(axiom, 0, 0, 0); // input string, x, y, z
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//        ofLog() << "axiom = " << axiom;

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
