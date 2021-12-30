#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(100);
  
////    //CS TESTING
//    system.setStart("aaaabaaaaaaaaaaaa");
//    system.addRule(LRule("a", "b", "b"));
////    system.addRule(LRule("b", "a"));
//
    
//    FLOWERING
//    system.setStart("a");
//    system.addRule(LRule("a", "I[L]a", 0.9, "I[L]A", 0.1));
//    system.addRule(LRule("A", "K"));
//
//    system.addRule(LRule("I", "F"));
//    system.addRule(LRule("L", "-F", 0.5, "+F", 0.5));
    
//ROOT SYSTEM
//    //setStart is the starting axiom
//    system.setStart("Q");
//    system.printStart();
//
//    system.addRule(LRule("Q", "FW"));
//    system.addRule(LRule("W", "FE"));
//    system.addRule(LRule("E", "FR"));
//    system.addRule(LRule("R", "FT"));
//    system.addRule(LRule("T", "FY"));
//    system.addRule(LRule("Y", "FU"));
//    system.addRule(LRule("U", "FI"));
//    system.addRule(LRule("I", "FO"));
//    system.addRule(LRule("O", "FP"));
//    system.addRule(LRule("P", "[C][V]"));
//
//    system.addRule(LRule("C", "Z", 0.9, "L", 0.1));
//    system.addRule(LRule("V", "X", 0.9, "L", 0.1));
//
//    system.addRule(LRule("Z", "+FQ", 0.9, "-FL", 0.1));
//    system.addRule(LRule("X", "&FQ", 0.5, "^FQ", 0.5));
////
//    system.printRules();
    
    //SIMPLE RACEME
    system.setStart("HHHHA(5,0)GGGG");
//    system.addRule(LRule("a", "+F[L]a"));
//    system.addRule(LRule("A(t):t<30000", "C", "Blank"));
    system.addRule(LRule("A(x,y):y<=3", "A(x*2,x+y)", "Blank"));
    system.addRule(LRule("A(x,y):y>3", "B(x)A(x/y,0)", "Blank"));
    system.addRule(LRule("B(x):x>=1", "B(x-1)", "Blank"));
    system.addRule(LRule("B(x):x<1", "C", "Blank"));

    
    turtle = Turtle();
    
    length = 1;
    theta = 5;
    axiomLevel = 0;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    
    //Build out the sentances and store in into this vector.
    results = system.getLevels(maxAxiomLevel + 1);
    rotation = 0;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 1;
    ofLog() << "axiom - " << axiomLevel << " result : " << results[axiomLevel];

    
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
    turtle.draw(results[axiomLevel], 0, 0, 0); // input string, x, y, z

    ofPopMatrix();
    cam.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

//    results = system.getLevels(maxAxiomLevel + 1);

//    ofLog() << "axiom - " << axiomLevel << " result : " << results[axiomLevel];

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
