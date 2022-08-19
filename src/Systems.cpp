//
//  arrangements.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 14/8/2022.
//

#include "Systems.hpp"

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

// G - Move Line Forward Not as edge (Custom)
// G(x,y) - Uses the x to determing the amount to move by, ignores y
// # - Draw point at this position / Return to Origin Point (if Segment to be contained in "[]")
// { - Fill Polygon Style 1
// } - Close Polygon Style 1
// < - Fill Polygon Style 2
// > - Close Polygon Style 2
//(r,0_1) - Rand Int Value between 0 and 1 (Can only do positive integers & is inclusive of values)
//DO NOT USE THESE LETTERS (CASE SENSITIVE) AS THE PREDECESSOR
//r
//G
//F
//f
//and any of the punctuation used above for anything other than the pupose stated above

Systems::Systems(){
    
}

void Systems::createSystem(types select_types, int variations, int maxAxiomLevel){

    switch( select_types ){
        case types::palm: {
            sys.setStart("a(r,0_45)");
            sys.addRule(LRule("a(t):*", "%(t)F(20)B(1)", "parametric"));
            sys.addRule(LRule("B(t):t>0", "&(2)F(10)B(t-1)", "parametric"));
            sys.addRule(LRule("B(t):t=0", "&(2)F(10)LB(1)", "parametric"));
            //set of leaves
            sys.addRule(LRule("L", "[H(10)[D(4)][C(4)]][I(10)[D(4)][C(4)]]", "rewrite"));
            //each leaf on either side
            // D and C is either side of the leaf
            sys.addRule(LRule("D(t):t>0", "[+(-3)D(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("C(t):t>0", "[+(3)C(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("E(t):t>0", "G(40)E(t-1)", "parametric"));
            sys.addRule(LRule("H(t):t>0", "+(t)H(t-1)", "parametric"));
            sys.addRule(LRule("I(t):t>0", "+(-t)I(t-1)", "parametric"));
            
            branchCol.r=162;
            branchCol.g=140;
            branchCol.b=55;
            
            poly1Col.r=66;
            poly1Col.g=96;
            poly1Col.b=45;
            
            poly2Col.r=251;
            poly2Col.g=226;
            poly2Col.b=81;
            break;
        }
        case types::branch: {
            sys.setStart("a(10)");
            //for each branch have it rotate with p
            //I to make the branch grow
            //L to create a branch off
            //a to continue but shorten
            sys.addRule(LRule("a(t):t>0", "p(r,0_360)I(r,1_100)L(r,10_60)a(t-1)", "parametric"));
            sys.addRule(LRule("a(t):t=0", "C", "parametric"));
            sys.addRule(LRule("I(t):*", "F(t)", "parametric"));
            sys.addRule(LRule("p(t):*", "&(20)%(t)", "parametric"));
            //Create a branch and then create a 1/2 chance of making a flower
            sys.addRule(LRule("L(t):*", "[++(t)F(5)K(r,1_5)]", "parametric"));
            //Make the flower
            sys.addRule(LRule("K(t):*", "YFX(r,70_80)", "parametric"));
            sys.addRule(LRule("Y", "[%(0)&(35)Q][%(72)&(35)Q][%(144)&(35)Q][%(216)&(35)Q][%(288)&(35)Q]", "rewrite"));
            sys.addRule(LRule("X(t):*", "[%(0)&(t)W][%(30)&(t)W][%(60)&(t)W][%(90)&(t)W][%(120)&(t)W][%(150)&(t)W][%(180)&(t)W][%(210)&(t)W][%(240)&(t)W][%(270)&(t)W][%(300)&(t)W][%(330)&(t)W]", "parametric"));
            sys.addRule(LRule("Q", "{#[++GG#][GGG#][--GG#]}", "rewrite"));
            sys.addRule(LRule("W", "<#[++G(5)#][G(6)#][--G(5)#]>", "rewrite"));
            branchCol.r=114;
            branchCol.g=72;
            branchCol.b=50;
            
            poly1Col.r=247;
            poly1Col.g=194;
            poly1Col.b=66;
            
            poly2Col.r=251;
            poly2Col.g=226;
            poly2Col.b=81;
            break;
        }
        case types::lavender: {
            sys.setStart("a(r,4_8)");
            sys.addRule(LRule("a(t):t>1", "I(t)[L(t)]a(t-1)", "parametric"));
            sys.addRule(LRule("a(t):t=1", "I(t)[L(t)]A(4)", "parametric"));
            sys.addRule(LRule("A(t):*", "I(t)[K]A(4)", "parametric"));
            sys.addRule(LRule("I(t):*", "+(3-t)C(4)", "parametric"));
            sys.addRule(LRule("L(t):*", "%(t*180)&(90){#[+(20)&(-60)B(2)#][+(30)&(-40)B(4)#][&(-20)B(6)#][+(-30)&(-40)B(4)#][+(-20)&(-60)B(2)#]}", "parametric"));
            sys.addRule(LRule("B(t):t>1", "G(t)B(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t>1", "F(t)C(t-1)", "parametric"));
            sys.addRule(LRule("K", "[%(0)&(120)C(r,1_3)D][%(45)&(120)C(r,1_3)D][%(90)&(120)C(r,1_3)D][%(135)&(120)C(r,1_3)D][%(180)&(120)C(r,1_3)D][%(225)&(120)C(r,1_3)D][%(270)&(120)C(r,1_3)D][%(315)&(120)C(r,1_3)D]", "rewrite"));
            sys.addRule(LRule("D", "&(-90)<#[+(20)B(4)#][B(6)#][+(-20)B(4)#]>", "rewrite"));
            branchCol.r=9;
            branchCol.g=97;
            branchCol.b=72;

            poly1Col.r=77;
            poly1Col.g=81;
            poly1Col.b=57;

            poly2Col.r=171;
            poly2Col.g=59;
            poly2Col.b=58;
            break;
        }
    }
    for (int i = 0; i < variations; i++) {
        vector<string> results;
        results = sys.getLevels(maxAxiomLevel + 1);
        res.push_back(results);
    }
    turt.setup(theta, length, branchCol, poly1Col, poly2Col);
}

void Systems::renderArrangement(ofVec3f startPos, ofVec3f angle, int varNum, float axiomLevel) {
    ofPushMatrix();
    ofTranslate(startPos);
    ofRotateXDeg(angle.x);
    ofRotateYDeg(angle.y);
    ofRotateZDeg(angle.z);
    turt.draw(res[varNum][axiomLevel], 0, 0, 0);
    ofPopMatrix();
}
