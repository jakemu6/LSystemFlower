#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"
//#include "ofxLSystemGrammar.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    string axiom;
    int count;
    
    Turtle turtle;
    
    LSys system;
    
//    //write all the rules in here
//    vector<string> systemRules {
////        "0.99 -> A -> FB",
////        "0.99 -> B -> FC",
////        "0.99 -> C -> FD",
////        "0.99 -> D -> FE",
////        "E -> [Z][Z][Z][Z]",
//        "0.25 -> Z -> +FA",
//        "0.25 -> Z -> -FA",
//        "0.25 -> Z -> &FA",
//        "0.25 -> Z -> ^FA"
//    };
//
//    //the result of the rules are stored in here.
    vector<string> results;
    
    
    float length;
    float theta;

    float axiomLevel;
    
    //always getting an exta level than what is written here. so for 31 levels you write 30
    float maxAxiomLevel = 30;
    
    ofEasyCam cam;
    float rotation;
    
    bool grow = true;
    float growthRate = 0.1;
};
