

#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    cam.setDistance(800);
    
    ofEnableDepthTest();

  
    turtle = Turtle();
    
    axiomLevel = 0;
    
    turtle.setLength(length);
    turtle.setAngle(theta);
    
    //Build out the sentances and store in into this vector.
//    results = system.getLevels(maxAxiomLevel + 1);
//    rotation = 0;
    
    retrieveLvl.setup(maxAxiomLevel);
    loading = true;
    retrieveLvl.startThread();


}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if(loading==true && !retrieveLvl.isThreadRunning()){
        results = retrieveLvl.results;
        loading = false;
//        ofLog() << "axiom - " << axiomLevel << " result : " << results[axiomLevel];

    }

    if (rotate) {
        rotation += rotationSpeed;
    }

    if (sequence == "static") {
        axiomLevel = maxAxiomLevel;
    } else if (sequence == "loop") {
        axiomLevel += growthRate;
        if (axiomLevel > maxAxiomLevel) {
            axiomLevel = 0;
        }
    } else if (sequence == "reverseLoop") {
//        growthRate = 1;
//        cout << *p << endl;
        if (axiomLevel >= maxAxiomLevel) {
            growthRate = -growthRate;
        } else if (axiomLevel < 0) {
            growthRate = -growthRate;
        }
//        float * p = &growthRate;

        axiomLevel += growthRate;

    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    
    ofPushMatrix();
    ofRotateYDeg(rotation);
    ofBackground(252, 250, 242);
//    ofFill();
//    ofSetColor(0,0,255);
//    ofDrawSphere(0, 0, 5);
//    ofSetColor(255,0,0);
//
//    ofDrawSphere(2, 0, 5);

    ofNoFill();
    if (results.size() != 0) {
        turtle.draw(results[axiomLevel], 0, -200, 0); // input string, x, y, z
    }
    ofPopMatrix();
    cam.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    
//    results = system.getLevels(maxAxiomLevel + 1);

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
