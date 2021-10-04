#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(50);
    
////    //addVariable is for values that can be replaced
////    system.addVariable("F");
////
////    //Print sends to console
////    system.printVariables();
////
////    //addConstant is for values in the string which can not be replaced
////    system.addConstant("+");
////    system.addConstant("-");
////
////    //Print sends to console
////    system.printConstants();
//
//    //setStart is the starting axiom
    system.setStart("A");
    system.printStart();
    
    system.addRule(LRule("A", "FB"));
    system.addRule(LRule("B", "FC"));
    system.addRule(LRule("C", "FD"));
    system.addRule(LRule("D", "FE"));
    system.addRule(LRule("E", "[W][Y][X][Y]"));
//    system.addRule(LRule("W", "+F"));
//    system.addRule(LRule("X", "-FA"));
    system.addRule(LRule("W", "+FA", 0.5, "-FA", 0.5));

    system.addRule(LRule("Y", "&FA", 0.5, "^FA", 0.5));
//    system.addRule(LRule("Y", "^FA"));

    //Build out the sentances and store in into this vector.
    //0 - the rules in vector string format.
    //1 - the level of rewrite
    //2 - starting axiom
    // returns a vector of the strings at each level.
//    resultStochastic = ofxLSystemGrammar::buildSentences(systemRules, maxAxiomLevel, "A");


    system.printRules();
    
    turtle = Turtle();
    
    length = 0.5;
    theta = 22.5;
    axiomLevel = 1;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
//    axiom = system.getLevel(30);
    //is actually getting 31 levels because it also retrieves 0
    results = system.getLevels(maxAxiomLevel + 1);
    rotation = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 0.1;
    
    
    if (grow) {
        axiomLevel += 0.1;
    }

    if (axiomLevel > maxAxiomLevel) {
        axiomLevel = maxAxiomLevel;
    }
    axiom = system.getLevel(axiomLevel);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    
    ofPushMatrix();
    ofRotateYDeg(rotation);
    ofBackground(0, 0, 0);
    ofNoFill();
    turtle.draw(results[axiomLevel], 0, 0, 0); // input string, x, y, z
//    turtle.draw(resultStochastic[axiomLevel], 0, 0, 0); // input string, x, y, z
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    ofLog() << "axiom - " << axiomLevel << " result : " << results[axiomLevel];

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
