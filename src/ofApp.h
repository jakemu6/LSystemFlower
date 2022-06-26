#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"
#include "ofxFXObject.h"



//This thread is using the Lsystem to get the axiom for all of the results.
//Set the rules in the thread the main thread will handle the turtle

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
    

//    bool loading;
//    LevelRetriever retrieveLvl;
    
    LSys system;
    LSys system2;

    
    //the result of the rules are stored in here.
    vector<vector <string> > resultsList;
    vector<vector <string> > resultsList2;
    
    int NumOfSys = 1;
    int NumOfSys2 = 1;
    
    Turtle turtle;
    Turtle turtle2;
    
    float maxAxiomLevel = 30;
    
    //length of segments
    float length = 7;
    
    //angle of segments
    float theta = 10;

    //axiom level that is actually being drawn.
    float axiomLevel;
    
    
    ofEasyCam cam;

    bool rotate = true;
    float rotationSpeed = 0.1;
    float rotation = 0;

    //static - no movement max axiom level
    //loop - 0 - max;
    //reverseLoop
    string sequence = "reverseLoop";
    
    bool grow = true;
    float growthRate = 0.1;
    
    bool loop = true;
    
    vector<float> xPositions;
    
    int width = 1000;
    int height = 1000;
    
    ofFbo render_buffer;
    ofFbo img_buffer;
    ofImage img;
    ofxFXObject fx;
    
    //    ofxFileBlur fx_file;
    
//    ofFbo fbo;
//    ofShader shader;
//    bool doShader;
};
