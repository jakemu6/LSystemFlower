#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"
#include "ofxFXObject.h"
#include "Systems.hpp"
#include "ofxGui.h"

typedef enum {
    //MIXED ARRANGEMENTS
    arrangement_0,
    arrangement_1,
    arrangement_2,
    arrangement_3,
    arrangement_4,
    arrangement_5,
    arrangement_6,
    arrangement_7,
    arrangement_8,
    arrangement_9,
    arrangement_10,
    arrangement_11,
    arrangement_12,
    arrangement_13,
    arrangement_14,
    arrangement_15,
    arrangement_16,
    arrangement_17,
    arrangement_18,
    arrangement_19,
    
    //SINGLE PLANT IN SYSTEM
    arrangement_A,
    arrangement_S,
    arrangement_D,
    arrangement_F,
    arrangement_G,
    arrangement_H,
    arrangement_J,
    arrangement_K,
    arrangement_L,
    arrangement_SEMICOLON
    
} State;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void changeArrangement(int num);
        void generateArrangement(int num);
        void overwriteCol();
    
    string axiom;
    int count;
    
    Systems palms;
    Systems lavenders;
    Systems branches;
    Systems flowerBalls;
    Systems phyllos;
    Systems fans;
    Systems acros;
    Systems sigmas;
    Systems alphas;
    Systems betas;

    State arrangementNo;
    
    int currentArrangement;
    
    //TESTING GUI
//    ofxPanel gui;
//    ofxVec3Slider position1;
//    ofxVec3Slider position2;
//    ofxVec3Slider position3;
//    ofxVec3Slider position4;
//    ofxVec3Slider position5;
//
//    ofxVec3Slider angle1;
//    ofxVec3Slider angle2;
//    ofxVec3Slider angle3;
//    ofxVec3Slider angle4;
//    ofxVec3Slider angle5;

    float maxAxiomLevel = 30;
    int numPlants = 5;
    
    //for randomisation of the 
    int numArrangements = 6;
    
    //axiom level that is actually being drawn.
    float axiomLevel;
    
    ofEasyCam cam;

    bool rotate = true;
    float rotationSpeed = 0.05;
    float rotation = 0;
    
    float camDistance;
    float pitch;
    float shift_x, shift_y;
    //static - no movement max axiom level
    //loop - 0-max;
    //reverseLoop - back and forth boomerang
    //stepThrough - keyReleased to go up Axiom Level
    //capture - save image of the flowers and exit program, files are in bin/data

    string sequence = "reverseLoop";
    
    bool grow = true;
    float growthRate = 0.05;
    bool loop = true;
    
    bool dev = false;
    
    
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    ofVec3f randPos;
    ofVec3f randAng;
    vector<ofVec3f> positions;
    vector<ofVec3f> angles;

    ofFbo render_buffer;
    ofxFXObject fx;
    ofFbo final_buffer;

    ofImage img;
    ofPixels pix;

};
