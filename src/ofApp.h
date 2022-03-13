#pragma once

#include "ofMain.h"
#include "Turtle.hpp"
#include "LSystem.h"

//This thread is using the Lsystem to get the axiom for all of the results.
//Set the rules in the thread the main thread will handle the turtle
class LevelRetriever: public ofThread{

public:
    void setup(int maxAxiomLevel){
        this->maxLevel = maxAxiomLevel;
    }

    void threadedFunction(){
        
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
        system.addRule(LRule("a(t):t=0", "vin", "parametric"));

        system.addRule(LRule("I(t):*", "F(t)", "parametric"));
        system.addRule(LRule("p(t):*", "&(10)%(t)", "parametric"));

        //Create a branch and then create a 1/2 chance of making a flower
        system.addRule(LRule("L(t):*", "[++(t)F(5)K(r,1_3)]", "parametric"));
  
        //Make the flower
        system.addRule(LRule("K(t):t=2", "YFX", "parametric"));
        system.addRule(LRule("Y", "[%(0)&(35)Q][%(72)&(35)Q][%(144)&(35)Q][%(216)&(35)Q][%(288)&(35)Q]", "rewrite"));
        system.addRule(LRule("X", "[%(0)&(75)W][%(60)&(80)W][%(120)&(75)W][%(180)&(80)W][%(240)&(75)W][%(300)&(80)W]", "rewrite"));
        
        system.addRule(LRule("Q", "{#[++GG#][GGG#][--GG#]}", "rewrite"));
        system.addRule(LRule("W", "<#[++++++G#][+++GGG#][GGGG#][---GGG#][------G#]>", "rewrite"));
        
        //Don't make the flower but make a stem
        system.addRule(LRule("K(t):t=1", "FT(t)", "parametric"));
        
        results = system.getLevels(maxLevel + 1);
    }
    
    int maxLevel;
    vector<string> results;
    LSys system;
};

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
    LSys system2;

    bool loading;
    LevelRetriever retrieveLvl;
    
    //the result of the rules are stored in here.
    vector<string> results;
    
    //length of segments
    float length = 3;
    
    //angle of segments
    float theta = 10;

    //axiom level that is actually being drawn.
    float axiomLevel;
    
    float maxAxiomLevel = 30;
    
    ofEasyCam cam;

    bool rotate = true;
    float rotationSpeed = 0.5;
    float rotation = 0;

    //static - no movement max axiom level
    //loop - 0 - max;
    //reverseLoop
    string sequence = "loop";
    
    bool grow = true;
    float growthRate = 0.1;
    
    bool loop = true;
    
    ofMesh sphere1;
    ofMesh sphere2;

};
