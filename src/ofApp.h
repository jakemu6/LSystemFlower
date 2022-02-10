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
        
        // F - Forward
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
        
        // G - Draw Line Not as edge
        // # - Return to Origin Point (Last "[" Branch)
        // { - Fill Polygon Style 1
        // } - Close Polygon Style 1
        // < - Fill Polygon Style 2
        // > - Close Polygon Style 2

        
////        Figure 3.5
//        system.setStart("I(9)a(13)");
//        system.addRule(LRule("a(t):t>0", "[&(70)L]/(137.5)I(10)a(t-1)", "parametric"));
//        system.addRule(LRule("a(t):t=0", "[&(70)L]/(137.5)I(10)A", "parametric"));
//        system.addRule(LRule("A", "[&(18)u(4)FFI(10)I(5)X(5)KKKK]/(137.5)I(8)A", "rewrite"));
////
//        system.addRule(LRule("I(t):t>0", "FI(t-1)", "parametric"));
//        system.addRule(LRule("I(t):t=0", "F", "parametric"));
//        system.addRule(LRule("u(t):t>0", "&(9)u(t-1)", "parametric"));
//        system.addRule(LRule("u(t):t=0", "&(9)", "parametric"));
//
//        system.addRule(LRule("L", "[{.-FI(7)+FI(7)+FI(7)}][{.+FI(7)-FI(7)-FI(7)}]", "rewrite"));
//        system.addRule(LRule("K", "[&<.+FI(2)--FI(2)>][&<.-FI(2)++FI(2)>]/(90)", "rewrite"));
//
//        system.addRule(LRule("X(t):t>0", "X(t-1)", "parametric"));
//        system.addRule(LRule("X(t):t=0", "^(50)[[-GGGG++[GGG[++G{.].].].++GGGG.--GGG.__G.}]%", "parametric"));
        
        //Fig 5.5
//        system.setStart("[A][B]");
////        system.addRule(LRule("I", "F(1)+(0.5)I", "rewrite"));
//        system.addRule(LRule("A", "[+A{.].C.}", "rewrite"));
//        system.addRule(LRule("B", "[-B{.].C.}", "rewrite"));
//        system.addRule(LRule("C", "GC", "rewrite"));

//Fig 3.14
//        system.setStart("A(7)");
//        system.addRule(LRule("A(t):t=7", "FI(20)[&(60)~L(0)]/(90)[&(45)A(0)]/(90)[&(60)~L(0)]/(90)[&(45)A(4)]FI(10)~K(0)", "parametric"));
//        system.addRule(LRule("A(t):t<7", "A(t+1)", "parametric"));
//        system.addRule(LRule("I(t):t>0", "FFI(t-1)", "parametric"));
//        system.addRule(LRule("L(t):*", "L(t+1)", "parametric"));
//        system.addRule(LRule("K(t):*", "K(t+1)", "parametric"));

//        system.setStart("F(1){.A(0)}");
//        system.addRule(LRule("A(t):*", "[-B(t).][A(t+1)][+B(t).]F", "parametric"));
//        system.addRule(LRule("B(t):t>0", "G(1,1)B(t-0.1)", "parametric"));
////        system.addRule(LRule("G(s,r):s=0", "G (5,1)", "parametric"));
//        system.addRule(LRule("G(s,r):*", "G(s*r,r)", "parametric"));

        system.setStart("T(0)");
        //DECIMAL PLACES ARE IN THE SUBSTRING DETECT
        
        //STEM
        system.addRule(LRule("T(t):t>0", "T(t-1)", "parametric"));
        system.addRule(LRule("T(t):t=0", "%(140)[&(10)P(1)L]T(5)", "parametric"));

        system.addRule(LRule("P(t):*", "F(t/5)P(t+1)", "parametric"));
//        system.addRule(LRule("P(t):t=0", "FL", "parametric"));

        
        //LEAF
        system.addRule(LRule("L", "&(120){#A(0)}", "rewrite"));
        system.addRule(LRule("A(t):*", "G(3,1.1)[-B(t)#][A(t+1)][+B(t)#]", "parametric"));
        system.addRule(LRule("B(t):t>0", "G(1,0.9)B(t-0.1)", "parametric"));
        system.addRule(LRule("G(s,r):s<2", "G(s*r,r)", "parametric"));
        
//        system.setStart("L");
//        system.addRule(LRule("L", "F{A}", "rewrite"));
//        system.addRule(LRule("A", "[+G.][-G.]", "rewrite"));


//        system.setStart("[A][B]");
////        system.addRule(LRule("I", "F(1)+(0.5)I", "rewrite"));
//        system.addRule(LRule("A", "{.B[++G.]}", "rewrite"));
//        system.addRule(LRule("B", "[G.][+GG.]", "rewrite"));

//        system.addRule(LRule("B", "[-B{.].C.}", "rewrite"));
//        system.addRule(LRule("C", "G(2,1.2)C", "rewrite"));
//        system.addRule(LRule("G(s,r):*", "G(s*r,r)", "parametric"));

        
        
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
    float length = 100;
    
    //angle of segments
    float theta = 60;

    //axiom level that is actually being drawn.
    float axiomLevel;
    
    float maxAxiomLevel = 40;
    
    ofEasyCam cam;
    //TODO SET THIS
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
    

};
