#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(100);
  
    
    //Figure 3.5
    system.setStart("I(9)a(13)");
    system.addRule(LRule("a(t):t>0", "[&(70)L]/(137.5)I(10)a(t-1)", "parametric"));
    system.addRule(LRule("a(t):t=0", "[&(70)L]/(137.5)I(10)A", "parametric"));
    system.addRule(LRule("A", "[&(18)u(4)FFI(10)I(5)X(5)KKKK]/(137.5)I(8)A", "rewrite"));

    system.addRule(LRule("I(t):t>0", "FI(t-1)", "parametric"));
    system.addRule(LRule("I(t):t=0", "F", "parametric"));
    system.addRule(LRule("u(t):t>0", "&(9)u(t-1)", "parametric"));
    system.addRule(LRule("u(t):t=0", "&(9)", "parametric"));
    
    system.addRule(LRule("L", "[{.-FI(7)+FI(7)+FI(7)}][{.+FI(7)-FI(7)-FI(7)}]", "rewrite"));
    system.addRule(LRule("K", "[&{.+FI(2)--FI(2)}][&{.-FI(2)++FI(2)}]/(90)", "rewrite"));
    
    system.addRule(LRule("X(t):t>0", "X(t-1)", "parametric"));
    system.addRule(LRule("X(t):t=0", "^(50)[[-GGGG++[GGG[++G{.].].].++GGGG.--GGG.__G.}]%", "parametric"));

    
    
    turtle = Turtle();
    
    length = 1;
    theta = 18;
    axiomLevel = 0;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    
    //Build out the sentances and store in into this vector.
    results = system.getLevels(maxAxiomLevel + 1);
    rotation = 0;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 2;
//    ofLog() << "axiom - " << axiomLevel << " result : " << results[axiomLevel];

    
    if (grow) {
        axiomLevel += 1;
    }

    if (loop) {
        if (axiomLevel > maxAxiomLevel) {
            axiomLevel = 0;
        }
    } else {
        if (axiomLevel > maxAxiomLevel) {
            axiomLevel = maxAxiomLevel;
        }
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
