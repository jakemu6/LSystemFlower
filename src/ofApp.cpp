

#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
//    #ifdef TARGET_OPENGLES
//        shader.load("shadersES2/shader");
//    ofLog() << "ES2";
//
//    #else
//        if(ofIsGLProgrammableRenderer()){
//            shader.load("shadersGL3/shader");
//            ofLog() << "GL3";
//        }else{
//            shader.load("shadersGL2/shader");
//            ofLog() << "GL2";
//
//        }
//    #endif
//
//    doShader = true;
    
    // F - Forward (Custom)
    // f - Move Forward No Draw
    // + - Turn Right (Custom)
    // - - Turn Left
    // [ - Push Branch
    // ] - Return Branch
    // & - Pitch Down (Custom)
    // ^ - Pitch Up
    // ? - Roll Left
    // % - Roll Right (Custom)
    // | - Roll 180 Deg

    // G - Move Line Forward Not as edge
    // G(x,y) - Uses the x to determing the amount to move by, ignores y
    // # - Draw point at this position / Return to Origin Point (if Segment to be contained in "[]")
    // { - Fill Polygon Style 1
    // } - Close Polygon Style 1
    // < - Fill Polygon Style 2
    // > - Close Polygon Style 2
    //(r,0_1) - Rand Int Value between 0 and 1 (Can only do positive integers)



    //10 Segment branch
    system.setStart("a(10)");

    //for each branch have it rotate with p
    //I to make the branch grow
    //L to create a branch off
    //a to continue but shorten
    system.addRule(LRule("a(t):t>0", "p(r,0_360)I(r,1_100)L(r,10_60)a(t-1)", "parametric"));
    system.addRule(LRule("a(t):t=0", "C", "parametric"));

    system.addRule(LRule("I(t):*", "F(t)", "parametric"));
    system.addRule(LRule("p(t):*", "&(20)%(t)", "parametric"));

    //Create a branch and then create a 1/2 chance of making a flower
    system.addRule(LRule("L(t):*", "[++(t)F(5)K(r,1_5)]", "parametric"));

    //Make the flower
    system.addRule(LRule("K(t):t>2", "YFX", "parametric"));

    system.addRule(LRule("Y", "[%(0)&(35)Q][%(72)&(35)Q][%(144)&(35)Q][%(216)&(35)Q][%(288)&(35)Q]", "rewrite"));
    system.addRule(LRule("X", "[%(0)&(75)W][%(60)&(80)W][%(120)&(75)W][%(180)&(80)W][%(240)&(75)W][%(300)&(80)W]", "rewrite"));

    system.addRule(LRule("Q", "{#[++GG#][GGG#][--GG#]}", "rewrite"));
    system.addRule(LRule("W", "<#[++++++G#][+++GGG#][GGGG#][---GGG#][------G#]>", "rewrite"));

    for (int i = 0; i < NumOfSys; i++) {
        vector<string> results;
        results = system.getLevels(maxAxiomLevel + 1);
        resultsList.push_back(results);
    }

    ofColor branchCol1;
    branchCol1.r=114;
    branchCol1.g=72;
    branchCol1.b=50;

    ofColor poly1Col1;
    poly1Col1.r=247;
    poly1Col1.g=194;
    poly1Col1.b=66;

    ofColor poly2Col1;
    poly2Col1.r=251;
    poly2Col1.g=226;
    poly2Col1.b=81;

    turtle.setup(theta, length, branchCol1, poly1Col1, poly2Col1);

    ofVec3f start;
    start.set(0, 0, 0);


    system2.setStart("a(r,0_360)");
    system2.addRule(LRule("a(t):*", "%(t)F(200)B(1)", "parametric"));

    system2.addRule(LRule("B(t):t>0", "&(2)F(100)B(t-1)", "parametric"));
    system2.addRule(LRule("B(t):t=0", "&(2)F(100)LB(1)", "parametric"));

    //set of leaves
    system2.addRule(LRule("L", "[H(10)[D(4)][C(4)]][I(10)[D(4)][C(4)]]", "rewrite"));

    //each leaf on either side
    // D and C is either side of the leaf
    system2.addRule(LRule("D(t):t>0", "[+(-3)D(t-1){#]#E(t-1)#}", "parametric"));
    system2.addRule(LRule("C(t):t>0", "[+(3)C(t-1){#]#E(t-1)#}", "parametric"));
    system2.addRule(LRule("E(t):t>0", "G(400)E(t-1)", "parametric"));
    system2.addRule(LRule("H(t):t>0", "+(t)H(t-1)", "parametric"));
    system2.addRule(LRule("I(t):t>0", "+(-t)I(t-1)", "parametric"));



//    system2.addRule(LRule("c(t):*", "G(5,1)[-d(t)#][c(t+1)][+d(t)#]", "parametric"));
//    system2.addRule(LRule("d(t):t>0", "G(1,1)B(t-1)", "parametric"));
//    system2.addRule(LRule("G(s,r):*", "G(s*r,r)", "parametric"));



    for (int i = 0; i < NumOfSys2; i++) {
        vector<string> results;
        results = system2.getLevels(maxAxiomLevel + 1);
        resultsList2.push_back(results);

        float xPos = ofRandom(-20,20);
        xPositions.push_back(xPos);
    }


    ofColor branchCol2;
    branchCol2.r=162;
    branchCol2.g=140;
    branchCol2.b=55;

    ofColor poly1Col2;
    poly1Col2.r=66;
    poly1Col2.g=96;
    poly1Col2.b=45;

    ofColor poly2Col2;
    poly2Col2.r=251;
    poly2Col2.g=226;
    poly2Col2.b=81;

    turtle2.setup(theta, length, branchCol2, poly1Col2, poly2Col2);

    axiomLevel = 0;
    cam.setDistance(5000);
    ofEnableDepthTest();
    

    
//    fbo.allocate(ofGetWidth(),ofGetHeight());
//    fbo.begin();
//    ofClear(255);
//    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){



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
        if (axiomLevel >= maxAxiomLevel) {
            growthRate = -growthRate;
        } else if (axiomLevel < 0) {
            growthRate = -growthRate;
        }
        axiomLevel += growthRate;
    } else if (sequence == "stepThrough") {
        if (axiomLevel >= maxAxiomLevel) {
            axiomLevel = 0;
        } else if (axiomLevel < 0) {
            axiomLevel = maxAxiomLevel;
        }
    }
    


}

//--------------------------------------------------------------
void ofApp::draw(){
//    fbo.begin();
//
//    if (doShader) {
//        shader.begin();
//        shader.setUniformTexture("fboTexture", fbo.getTexture(), 1);
//        shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
////        shader.setUniform1f("blurAmnt", blur);
//    }
    cam.begin();
    ofPushMatrix();
    ofRotateYDeg(rotation);
    ofBackground(252, 250, 242);
    ofNoFill();
    for(int i = 0; i < resultsList.size(); i++) {
            turtle.draw(resultsList[i][axiomLevel], 0, -50, 0); // input string, x, y, z
    }
    for(int i = 0; i < resultsList2.size(); i++) {
            turtle2.draw(resultsList2[i][axiomLevel], xPositions[i], -60, 0); // input string, x, y, z
    }
    ofPopMatrix();
    cam.end();
//    if (doShader) {
//        shader.end();
//    }
//    fbo.end();
//    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    if( key == 's' ){
//        #ifdef TARGET_OPENGLES
//            shader.load("shadersES2/shader");
//        ofLog() << "ES2";
//
//        #else
//            if(ofIsGLProgrammableRenderer()){
//                shader.load("shadersGL3/shader");
//                ofLog() << "GL3";
//            }else{
//                shader.load("shadersGL2/shader");
//                ofLog() << "GL2  " << doShader;
//
//            }
//        #endif
//        doShader = !doShader;
//    }
    
    if (sequence == "stepThrough") {
        axiomLevel++;
    }
//    resultsList.clear();

//    for (int i = 0; i < NumOfSys; i++) {
//        vector<string> results;
//        results = system.getLevels(maxAxiomLevel + 1);
//        resultsList.push_back(results);
//    }

//    ofLog() << "axiom - " << axiomLevel << " result : " << resultsList[0][axiomLevel];

    ofLog() << "axiom - " << axiomLevel << " result : " << resultsList2[0][axiomLevel];

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
