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
    
    //the result of the rules are stored in here.
    vector<string> results;
    
    //length of segments
    float length;
    
    //angle of segments
    float theta;

    //axiom level that is actually being drawn.
    float axiomLevel;
    
    //always getting an exta level than what is written here. so for 31 levels you write 30
    float maxAxiomLevel = 11;
    
    ofEasyCam cam;
    float rotation;
    
    bool grow = true;
    float growthRate = 0.1;
    

};
