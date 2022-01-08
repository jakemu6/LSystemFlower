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
        
        //F - Forward
        // +
        // -
        // [
        // ]
        // &
        // ^
        // ?
        // /
        // |
  
        //Figure 1.25
        system.setStart("A");
        system.addRule(LRule("A", "[&FL!A]/////'[&FL!A]///////'[&FL!A]", "rewrite"));
        system.addRule(LRule("F", "S/////F", "rewrite"));
        system.addRule(LRule("S", "FL", "rewrite"));
        system.addRule(LRule("L", "['''^^{-f+f+f-|-f+f+f}]", "rewrite"));

        
        
        
//        //Figure 3.5
//        system.setStart("I(9)a(13)");
//        system.addRule(LRule("a(t):t>0", "[&(70)L]/(137.5)I(10)a(t-1)", "parametric"));
//        system.addRule(LRule("a(t):t=0", "[&(70)L]/(137.5)I(10)A", "parametric"));
//        system.addRule(LRule("A", "[&(18)u(4)FFI(10)I(5)X(5)KKKK]/(137.5)I(8)A", "rewrite"));
//
//        system.addRule(LRule("I(t):t>0", "FI(t-1)", "parametric"));
//        system.addRule(LRule("I(t):t=0", "F", "parametric"));
//        system.addRule(LRule("u(t):t>0", "&(9)u(t-1)", "parametric"));
//        system.addRule(LRule("u(t):t=0", "&(9)", "parametric"));
//
//        system.addRule(LRule("L", "[{.-FI(7)+FI(7)+FI(7)}][{.+FI(7)-FI(7)-FI(7)}]", "rewrite"));
//        system.addRule(LRule("K", "[&{.+FI(2)--FI(2)}][&{.-FI(2)++FI(2)}]/(90)", "rewrite"));
//
//        system.addRule(LRule("X(t):t>0", "X(t-1)", "parametric"));
//        system.addRule(LRule("X(t):t=0", "^(50)[[-GGGG++[GGG[++G{.].].].++GGGG.--GGG.__G.}]%", "parametric"));
//
        results = system.getLevels(maxLevel + 1);
    }
    
    int maxLevel;
    vector<string> results;
    LSys system;
};

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
    
    bool loading;
    LevelRetriever retrieveLvl;
    
    //the result of the rules are stored in here.
    vector<string> results;
    
    //length of segments
    float length;
    
    //angle of segments
    float theta;

    //axiom level that is actually being drawn.
    float axiomLevel;
    
    //always getting an exta level than what is written here. so for 31 levels you write 30
    float maxAxiomLevel = 7;
    
    ofEasyCam cam;
    float rotation;
    
    bool grow = true;
    float growthRate = 0.1;
    
    bool loop = true;
    

};
