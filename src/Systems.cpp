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
//WARNING do not put any "Rand Int Value" in a parametric rule, only use these in rewrite rules

//DO NOT USE THESE LETTERS (CASE SENSITIVE) AS THE PREDECESSOR
//r
//G
//F
//f
//t
//and any of the punctuation used above for anything other than the pupose stated above


Systems::Systems(){
    
}

void Systems::createSystem(types select_types, int variations, int maxAxiomLevel){

    switch( select_types ){
        case types::palm: {
            sys.setStart("a");
            sys.addRule(LRule("a", "F(15)B(14)", "rewrite"));
            sys.addRule(LRule("B(t):t>0", "&(2)F(15)Q(t-1)", "parametric"));
            sys.addRule(LRule("Q(t):t>0", "&(2)L(t)B(t-1)", "parametric"));
            //set of leaves
            sys.addRule(LRule("L(t):*", "[H(t,0)[D(4)][C(4)]][I(t,0)[D(4)][C(4)]]", "parametric"));

            //each leaf on either side
            // D and C is either side of the leaf
            sys.addRule(LRule("D(t):t>0", "[+(-3)D(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("C(t):t>0", "[+(3)C(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("E(t):t>0", "G(30)E(t-1)", "parametric"));
            sys.addRule(LRule("H(t,d):t>0", "+(d)H(t-1,5)", "parametric"));
            sys.addRule(LRule("I(t,d):t>0", "+(-d)I(t-1,5)", "parametric"));
            
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
            sys.addRule(LRule("a(t):t>0", "P(r,0_360)I(r,1_50)L(r,10_60)a(t-1)", "parametric"));
            
            sys.addRule(LRule("I(t):*", "F(t)", "parametric"));
            sys.addRule(LRule("P(t):*", "&(20)%(t)", "parametric"));
            //Create a branch and then create a 1/2 chance of making a flower
            sys.addRule(LRule("L(t):*", "[++(t)F(5)K]", "parametric"));
            //Make the flower
            sys.addRule(LRule("K", "YX(r,50_80)", "rewrite"));
            sys.addRule(LRule("Y", "[%(0)&(35)Q][%(72)&(35)Q][%(144)&(35)Q][%(216)&(35)Q][%(288)&(35)Q]", "rewrite"));
            sys.addRule(LRule("X(t):*", "[%(0)&(t)W][%(60)&(t)W][%(120)&(t)W][%(180)&(t)W][%(240)&(t)W][%(300)&(t)W]", "parametric"));
            sys.addRule(LRule("Q", "{#[+(30)G(4)#][G(5)#][+(-30)G(4)#]}", "rewrite"));
            sys.addRule(LRule("W", "<#[+(29)G(9)#][G(10)#][+(-29)G(9)#]>", "rewrite"));
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
            sys.setStart("a(r,3_5)");
            sys.addRule(LRule("a(t):t>1", "I(t)[L(t)]a(t-1)", "parametric"));
            sys.addRule(LRule("a(t):t=1", "I(t)[L(t)]A(4)", "parametric"));
            sys.addRule(LRule("A(t):t>0", "I(t)[K]A(t-1)", "parametric"));
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
        case types::flowerBall: {
            sys.setStart("a(r,7_10)");
            sys.addRule(LRule("a(t):*", "cb(t)A", "parametric"));
            sys.addRule(LRule("b(t):t>0", "&(2)F(5)b(t-1)", "parametric"));
            sys.addRule(LRule("b(t):t=0", "&(2)F(5)", "parametric"));
            sys.addRule(LRule("c", "%(r,0_360)", "rewrite"));
            //Flowerball
            
//            sys.addRule(LRule("A", "[K(0)][K(30)][K(60)][K(90)][K(120)][K(150)][K(180)][K(210)][K(240)][K(270)][K(300)][K(330)]", "rewrite"));
//            sys.addRule(LRule("K(t):*", "%(t)[B(0)][&(-20)B(20)][&(-10)B(57)][B(90)][&(10)B(123)][&(20)B(160)][B(180)]", "parametric"));
            
            sys.addRule(LRule("A", "[K(0)][K(60)][K(120)][K(180)][K(240)][K(300)]", "rewrite"));
            sys.addRule(LRule("K(t):*", "%(t)[B(0)][&(-20)B(20)][&(-10)B(57)][B(90)][&(10)B(123)][&(20)B(160)][B(180)]", "parametric"));
            sys.addRule(LRule("B(t):*", "+(t)f(5)L(5)", "parametric"));
            sys.addRule(LRule("L(t):*", "<[+(30)G(6)#][G(6)#][+(-30)G(6)#]>%(90)<[+(30)G(6)#][G(6)#][+(-30)G(6)#]>", "parametric"));
//            sys.addRule(LRule("M(t):t>0", "G(4)", "parametric"));

            //Leaves

//            sys.addRule(LRule("M(x,y):*", "[C(x,y)]%(60)[C(x,y)]%(60)[C(x,y)]%(60)[C(x,y)]%(60)[C(x,y)]%(60)[C(x,y)]", "parametric"));
//            sys.addRule(LRule("C(x,y):*", "&(60){[+(y*3)G(x*6/8)#][+(y*2)G(x*7/8)#][G(x)#][+(-y*2)G(x*7/8)#][+(-y*3)G(x*6/8)#]}", "parametric"));

            branchCol.r=81;
            branchCol.g=110;
            branchCol.b=65;

            poly1Col.r=0;
            poly1Col.g=255;
            poly1Col.b=0;

            poly2Col.r=128;
            poly2Col.g=143;
            poly2Col.b=124;
            break;
        }
        case types::phyllotaxis: {
            sys.setStart("C(5)F(20)&(-90)A(0)");
            sys.addRule(LRule("C(t):t>0", "&(2)F(r,4_20)[E]C(t-1)", "parametric"));
            sys.addRule(LRule("E", "L(r,2_3)", "rewrite"));
            sys.addRule(LRule("L(t):t=3", "%(r,0_360)+(r,30_60)F&(r,45_135)P(5)", "parametric"));
            sys.addRule(LRule("P(t):t>0", "<[+(-110)M(5)#][+(-60)M(10)#][+(-50)M(12)#][M(20)#][+(50)M(12)#][+(60)M(10)#][+(110)M(5)#]>", "parametric"));
            sys.addRule(LRule("M(t):*", "G(t/5)N(4,t)", "parametric"));
            sys.addRule(LRule("N(t,d):t>0", "G(d/10)N(t-1,t)", "parametric"));

            //Simple Cymes structure
            sys.addRule(LRule("A(n):*", "+(137.5)&(n*10)[(n^0.5)D]A(n+1)", "parametric"));
            sys.addRule(LRule("D", "{[+(15)B(4)#][B(5)#][+(-15)B(4)#]}", "rewrite"));
            sys.addRule(LRule("B(t):t>0", "G(4)B(t-1)", "parametric"));

            branchCol.r=147;
            branchCol.g=150;
            branchCol.b=80;

            poly1Col.r=220;
            poly1Col.g=158;
            poly1Col.b=180;

            poly2Col.r=147;
            poly2Col.g=150;
            poly2Col.b=80;
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
