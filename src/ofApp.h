#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"
#include "ofxFXObject.h"
#include "Systems.hpp"


typedef enum {
arrangement_1,
arrangement_2,
arrangement_3,
arrangement_4,
arrangement_5
} State;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		
    string axiom;
    int count;
    
    Systems palms;
    Systems lavenders;
    Systems branches;
    Systems flowerBalls;
    Systems phyllos;

    State arrangementNo;

    float maxAxiomLevel = 30;
    
    //axiom level that is actually being drawn.
    float axiomLevel;
    
    ofEasyCam cam;

    bool rotate = true;
    float rotationSpeed = 0.1;
    float rotation = 0;
    //static - no movement max axiom level
    //loop - 0-max;
    //reverseLoop - back and forth boomerang
    //stepThrough - keyReleased to go up Axiom Level

    string sequence = "reverseLoop";
    
    //counter is for reverseLoop only
    int counter;
    
    bool grow = true;
    float growthRate = 0.1;
    bool loop = true;
    
    bool dev = false;
    
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    int numPlants = 20;
    ofVec3f randPos;
    ofVec3f randAng;
    vector<ofVec3f> positions;
    vector<ofVec3f> angles;
    
    ofFbo render_buffer;
    ofxFXObject fx;
};
