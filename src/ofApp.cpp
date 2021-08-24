#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //addVariable is for values that can be replaced
    system.addVariable("0");
    system.addVariable("1");
    //Print sends to console
    system.printVariables();

    //addConstant is for values in the string which can not be replaced
    system.addConstant("[");
    system.addConstant("]");
    //Print sends to console
    system.printConstants();

    //setStart is the starting axiom
    system.setStart("0");
    system.printStart();

    //addRule is for changing the variables in each level
    system.addRule(LRule("1", "11"));
    system.addRule(LRule("0", "1[0]0"));
    system.printRules();
    
    //character for move forward turn left/right
    //[] already set for save and restore state
    turtle = Turtle("1", "-", "+");
    turtle.setLength(10);
    turtle.setAngle(45);

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    turtle.draw(axiom, ofGetWidth()/2, ofGetHeight()/2, 0); // input string, x, y, starting angle

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    axiom = system.getNextLevel();


//    ofBuffer next;
//
//    for (int i = 0; i < axiom.length(); i++) {
//        char c = axiom[i];
//        if (c == '1') {
//            next.append("11");
//        } else if (c == '0') {
//            next.append("1[0]0");
//        }
//    }
//
//    axiom = next.getText();
//
//
//    count++;
//    ofLog() << "axiom = " << axiom;
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
