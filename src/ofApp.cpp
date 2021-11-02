#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(100);
    

//    //setStart is the starting axiom
    system.setStart("Q");
    system.printStart();
    
    system.addRule(LRule("Q", "FW"));
    system.addRule(LRule("W", "FE"));
    system.addRule(LRule("E", "FR"));
    system.addRule(LRule("R", "FT"));
    system.addRule(LRule("T", "FY"));
    system.addRule(LRule("Y", "FU"));
    system.addRule(LRule("U", "FI"));
    system.addRule(LRule("I", "FO"));
    system.addRule(LRule("O", "FP"));
    system.addRule(LRule("P", "[C][V]"));

    system.addRule(LRule("C", "Z", 0.9, "L", 0.1));
    system.addRule(LRule("V", "X", 0.9, "L", 0.1));

    system.addRule(LRule("Z", "+FQ", 0.9, "-FL", 0.1));
    system.addRule(LRule("X", "&FQ", 0.5, "^FQ", 0.5));
    
    
//    system.addRule(LRule("Y", "^FA"));

    //0 - the rules in vector string format.
    //1 - the level of rewrite
    //2 - starting axiom
    // returns a vector of the strings at each level.
//    resultStochastic = ofxLSystemGrammar::buildSentences(systemRules, maxAxiomLevel, "A");


    system.printRules();
    
    turtle = Turtle();
    
    length = 1;
    theta = 22.5;
    axiomLevel = 0.2;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    
    //Build out the sentances and store in into this vector.
    results = system.getLevels(maxAxiomLevel + 1);
    rotation = 0;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 1;
    
    
    if (grow) {
        axiomLevel += 1;
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
    turtle.draw(results[axiomLevel], 0, -50, 0); // input string, x, y, z
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
