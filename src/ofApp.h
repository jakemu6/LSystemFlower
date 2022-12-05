#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"
#include "ofxFXObject.h"
#include "Systems.hpp"
#include "ofxGui.h"

typedef enum {
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
    //ALL PLANTS IN SYSTEM
    arrangement_R,
    arrangement_T,
    arrangement_Y,
    arrangement_U,
    arrangement_I,
    arrangement_O,
    arrangement_P,
    
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
    
    ofxPanel gui;
    
    ofxVec3Slider position1;
    ofxVec3Slider position2;

    ofxVec3Slider angle1;
    ofxVec3Slider angle2;
    
//    ofxIntSlider intSlider;
//    ofxFloatSlider floatSlider;
//    
//    ofxToggle toggle;
//    ofxButton button;
//    ofxLabel label;
//    
//    ofxIntField intField;
//    ofxFloatField floatField;
//    ofxTextField textField;
//    
//    ofxVec2Slider vec2Slider;
//    ofxVec3Slider vec3Slider;
//    ofxVec4Slider vec4Slider;
    

    float maxAxiomLevel = 30;
    int numPlants = 5;
    
    //for randomisation of the 
    int numArrangements = 6;
    
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
    
    bool grow = true;
    float growthRate = 0.1;
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
};
