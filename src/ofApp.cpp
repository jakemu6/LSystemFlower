#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(1000);
    
//    //addVariable is for values that can be replaced
//    system.addVariable("F");
////    system.addVariable("X");
//
//
//
//    //Print sends to console
//    system.printVariables();
//
//    //addConstant is for values in the string which can not be replaced
//    system.addConstant("+");
//    system.addConstant("-");
//
//    system.addConstant("&");
//    system.addConstant("^");
//    system.addConstant("@");
//    system.addConstant("/");
//    system.addConstant("|");
//    system.addConstant("[");
//    system.addConstant("]");
//    //Print sends to console
//    system.printConstants();

    //setStart is the starting axiom
    system.setStart("X");
    system.printStart();

    //addRule is for changing the variables in each level
//    system.addRule(LRule("A", "B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
//    system.addRule(LRule("B", "A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
//    system.addRule(LRule("C", "|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
//    system.addRule(LRule("D", "|CFB-F+B|FA&F^A&&FB-F+B|FC//"));
    
    system.addRule(LRule("X", "F[+X][-X]FX"));
    system.addRule(LRule("F", "FF"));


    
    system.printRules();
    
    turtle = Turtle();
    
    length = 3;
    theta = 25.7;
    axiomLevel = 7;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    axiom = system.getLevel(axiomLevel);

    
    
//  character for move forward turn left/right
//  turtle.setAnotherForward("G");
//  turtle.setNoDrawForward("f");


    
}

//--------------------------------------------------------------
void ofApp::update(){


//    length = ofMap(ofGetMouseX(), 0, 1024, 0.1, 20);

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(0, 0, 0);
    ofNoFill();
    turtle.draw(axiom, 0, 0, 0); // input string, x, y, z
//    ofDrawSphere(10);
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
