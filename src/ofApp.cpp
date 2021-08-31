#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(1000);
    
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
    
    length = 100.0;

    
    
    //character for move forward turn left/right
    //[] already set for save and restore state
    turtle = Turtle("F", "+", "-");
//    turtle.setAnotherForward("G");
//        turtle.setNoDrawForward("f");

    turtle.setAngle(ofDegToRad(90));
    turtle.setLength(length);

    
    ofLog() << "axiom = " << axiom;
}

//--------------------------------------------------------------
void ofApp::update(){
    axiomLevel = ofMap(ofGetMouseX(), 0, 1024, 0, 10);
    axiom = system.getLevel(2);


//    length = ofMap(ofGetMouseX(), 0, 1024, 0.1, 20);

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(255, 255, 255);
    ofNoFill();
    turtle.draw(axiom, 0, 0 , 90); // input string, x, y, starting angle
    ofDrawSphere(1);
    cam.end();
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
