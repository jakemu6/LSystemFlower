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
            sys.addRule(LRule("a", "F(10)B(14)", "rewrite"));
            sys.addRule(LRule("B(t):t>0", "&(2)F(10)Q(t-1)", "parametric"));
            sys.addRule(LRule("Q(t):t>0", "&(2)L(t)B(t-1)", "parametric"));
            //set of leaves
            sys.addRule(LRule("L(t):*", "[H(t,0)[D(4)][C(4)]][I(t,0)[D(4)][C(4)]]", "parametric"));

            //each leaf on either side
            // D and C is either side of the leaf
            sys.addRule(LRule("D(t):t>0", "[+(-3)D(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("C(t):t>0", "[+(3)C(t-1){#]#E(t-1)#}", "parametric"));
            sys.addRule(LRule("E(t):t>0", "G(30)E(t-1)", "parametric"));
            sys.addRule(LRule("H(t,d):t>0", "+(d)H(t-1,14-t)", "parametric"));
            sys.addRule(LRule("I(t,d):t>0", "+(-d)I(t-1,14-t)", "parametric"));
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
            sys.addRule(LRule("Y", "[%(0)&(55)Q][%(72)&(55)Q][%(144)&(55)Q][%(216)&(55)Q][%(288)&(55)Q]", "rewrite"));
            sys.addRule(LRule("X(t):*", "[%(0)&(t)W][%(60)&(t)W][%(120)&(t)W][%(180)&(t)W][%(240)&(t)W][%(300)&(t)W]", "parametric"));
            sys.addRule(LRule("Q", "{#[+(30)G(1)#][G(2)#][+(-30)G(1)#]}", "rewrite"));
            sys.addRule(LRule("W", "<#[+(25)G(8)#][+(20)G(9)#][G(10)#][+(-20)G(9)#][+(-25)G(8)#]>", "rewrite"));
            break;
        }
        case types::lavender: {
            sys.setStart("a(r,3_5)");
            sys.addRule(LRule("a(t):t>1", "I(t)[L(t)]a(t-1)", "parametric"));
            sys.addRule(LRule("a(t):t=1", "I(t)[L(t)]A", "parametric"));
            sys.addRule(LRule("A", "[K(6)]", "rewrite"));

            sys.addRule(LRule("I(t):*", "+(3-t)C(4)", "parametric"));
            sys.addRule(LRule("L(t):*", "%(t*180)&(90){#[+(20)&(-60)B(2)#][+(30)&(-40)B(4)#][&(-20)B(6)#][+(-30)&(-40)B(4)#][+(-20)&(-60)B(2)#]}", "parametric"));
            sys.addRule(LRule("B(t):t>1", "G(t)B(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t>1", "F(t)C(t-1)", "parametric"));
            sys.addRule(LRule("K(t):t>0", "%(45*t)F(5)[%(0)&(80-t*10)D(t/3)][%(90)&(80-t*10)D(t/3)][%(180)&(80-t*10)D(t/3)][%(270)&(80-t*10)D(t/3)][K(t-1)]", "parametric"));
            sys.addRule(LRule("D(t):*", "&(-90)C(t)<#[+(30)B(4)#][B(5)#][+(-30)B(4)#]>", "parametric"));
            break;
        }
        case types::flowerBall: {
            sys.setStart("a(r,7_10)");
            sys.addRule(LRule("a(t):*", "%(3)b(t)A(r,5_8)", "parametric"));
            sys.addRule(LRule("b(t):t>0", "&(2)F(5)b(t-1)", "parametric"));
            sys.addRule(LRule("b(t):t=0", "&(2)F(5)", "parametric"));
            //Flowerball
            sys.addRule(LRule("A(n):*", "[K(0,n)][K(60,n)][K(120,n)][K(180,n)][K(240,n)][K(300,n)]", "parametric"));
            sys.addRule(LRule("K(t,n):*", "%(t)[B(0,n)][&(-20)B(20,n)][&(-10)B(57,n)][B(90,n)][&(10)B(123,n)][&(20)B(160,n)][B(180,n)]", "parametric"));
            sys.addRule(LRule("B(t,n):*", "+(t)f(n)L(n)", "parametric"));
            sys.addRule(LRule("L(t):*", "<[+(30)G(t)#][G(t)#][+(-30)G(t)#]>%(90)<[+(30)G(t)#][G(t)#][+(-30)G(t)#]>", "parametric"));
            break;
        }
        case types::phyllotaxis: {
            sys.setStart("C(5)F(20)&(-90)R(r,3_6)");
            sys.addRule(LRule("C(t):t>0", "&(2)F(r,5_10)[E]C(t-1)", "parametric"));
            sys.addRule(LRule("E", "L(r,2_3)", "rewrite"));
            sys.addRule(LRule("L(t):t=3", "%(r,0_360)+(r,30_60)F&(r,45_135)P(5)", "parametric"));
            sys.addRule(LRule("P(t):t>0", "{[+(-110)M(5)#][+(-60)M(10)#][+(-50)M(12)#][M(20)#][+(50)M(12)#][+(60)M(10)#][+(110)M(5)#]}", "parametric"));
            sys.addRule(LRule("M(t):*", "G(t/5)N(4,t)", "parametric"));
            sys.addRule(LRule("N(t,d):t>0", "G(d/10)N(t-1,t)", "parametric"));

            //Simple Cymes structure
            sys.addRule(LRule("R(p):*", "A(0,p)", "parametric"));

            sys.addRule(LRule("A(n,p):n<16", "+(137.5)&(n*10)[(n^0.5)D(p)A(n+1,p)", "parametric"));
            sys.addRule(LRule("D(p):*", "<[+(15)B(4,p)#][B(5,p)#][+(-15)B(4,p)#]>", "parametric"));
            sys.addRule(LRule("B(t,p):t>0", "G(p)B(t-1,p)", "parametric"));
            break;
        }
        case types::fan: {
            sys.setStart("C(r,6_9)%(90)A(0)");
            sys.addRule(LRule("C(t):t>0", "&(5)F(15)C(t-1)", "parametric"));
            //Simple Cymes structure
            sys.addRule(LRule("A(n):*", "+(180)&(180-n*10)[(n^0.5)D]A(n+1)", "parametric"));
            sys.addRule(LRule("D", "%(80)<[+(5)B(4)#][B(5)#][+(-5)B(4)#]>", "rewrite"));
            sys.addRule(LRule("B(t):t>0", "G(14)B(t-1)", "parametric"));
            break;
        }
        case types::acro: {
//              Stem
            sys.setStart("&(180)C(3)A(0)");
            sys.addRule(LRule("C(t):t>1", "&(2)F(10)C(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t=1", "&(2)Q(r,1_3)F(10)C(t-1)", "parametric"));
            
//              Fork
            sys.addRule(LRule("Q(t):t=1", "[%(r,0_360)+(r,-60_60)C(r,4_5)A(0)][%(r,0_360)+(r,-60_60)C(r,4_5)A(0)]", "parametric"));
            sys.addRule(LRule("Q(t):t=2", "[%(r,0_360)+(r,-60_60)C(r,4_5)A(0)]", "parametric"));
            sys.addRule(LRule("Q(t):t=3", "[%(r,0_360)+(r,-60_60)C(r,4_5)A(0)][%(r,0_360)+(r,-60_60)C(r,4_5)A(0)][%(r,0_360)+(r,-60_60)C(r,4_5)A(0)]", "parametric"));

//              Flowers
            sys.addRule(LRule("A(n):n<8", "+(137.5)&(n*10)[(n^0.5)[D][E]]A(n+1)", "parametric"));
            sys.addRule(LRule("D", "<[+(40)B(2)#][+(20)B(4)#][B(6)#][+(-20)B(4)#][+(-40)B(1)#]>", "rewrite"));
            sys.addRule(LRule("E", "&(1){[+(38)B(1)#][+(20)B(2)#][B(3)#][+(-20)B(2)#][+(-38)B(1)#]}", "rewrite"));
            sys.addRule(LRule("B(t):t>0", "G(2)B(t-1)", "parametric"));
            break;
        }
        case types::sigma: {
//              Stem
            sys.setStart("C(5)");
            sys.addRule(LRule("C(t):t>0", "&(2)%(2)PC(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t=0", "&(2)F(20)T(10)", "parametric"));
            
//              Creating Leaves
            sys.addRule(LRule("P", "F(10)[+(50)%(180)F(4)%(90)D(3)]F(4)[+(-50)F(4)%(90)D(3)]", "rewrite"));
            sys.addRule(LRule("D(t):t>0", "<[+(40)B(1)#][+(20)B(2)#][B(3)#][+(-20)B(2)#][+(-40)B(1)#]>f(10)&(-5)D(t-1)", "parametric"));
            sys.addRule(LRule("D(t):t=0", "<[+(40)B(1)#][+(20)B(2)#][B(3)#][+(-20)B(2)#][+(-40)B(1)#]>", "parametric"));
            sys.addRule(LRule("B(t):t>0", "G(10)B(t-1)", "parametric"));
            
//              Flower
            sys.addRule(LRule("T(t):t>0", "&(2)%(2)F(r,0_16)[&(r,40_140)+(r,90_270)F(4)S]T(t-1)", "parametric"));
            sys.addRule(LRule("S", "[%(60)&(80)U(4)][%(110)&(80)U(4)][%(180)&(80)U(4)][%(-110)&(80)U(4)][%(-60)&(80)U(4)]", "rewrite"));
            sys.addRule(LRule("U(t):*", "{[+(40)G(t)#][+(20)G(t*2)#][G(t*5/2)#][+(-20)G(t*2)#][+(-40)G(t)#]}", "parametric"));
            break;
        }
        case types::alpha: {
//              Stem
            sys.setStart("C(3)");

            sys.addRule(LRule("C(t):t>0", "&(2)%(2)F(9)[%(r,0_360)+(r,0_80)F(2)A(4)]C(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t=0", "&(2)%(2)F(9)[P(r,1_3)]", "parametric"));

            sys.addRule(LRule("P(t):t=1", "[+(r,0_80)%(r,0_360)C(3)]", "parametric"));
            sys.addRule(LRule("P(t):t=2", "[+(r,0_80)%(r,0_360)C(3)][+(r,0_80)%(r,0_360)C(3)]", "parametric"));
            sys.addRule(LRule("P(t):t=3", "[+(r,0_80)%(r,0_360)C(3)][+(r,0_80)%(r,0_360)C(3)][+(r,0_80)%(r,0_360)C(3)]", "parametric"));

            sys.addRule(LRule("A(t):*", "{[+(45)G(t)#][G(t*3/2)#][+(-45)G(t)#]}%(90){[+(45)G(t)#][G(t*3/2)#][+(-45)G(t)#]}", "parametric"));
            break;
        }
        case types::beta: {
//              Stem
            sys.setStart("O");
            
            sys.addRule(LRule("D", "F(15)OOO", "rewrite"));
            sys.addRule(LRule("O", "[+(10)%(r,0_360)C(r,3_5)]", "rewrite"));

            sys.addRule(LRule("C(t):t>0", "%(90)F(15)[[+(r,40_60)F(4)A(4)]][%(180)[+(r,40_60)F(4)A(4)]]C(t-1)", "parametric"));
            sys.addRule(LRule("C(t):t=0", "&(2)%(2)F(6)[Q(90)][Q(60)][Q(30)]", "parametric"));
            sys.addRule(LRule("Q(t):*", "[%(0)&(t)[P]][%(30)&(t)[P]][%(60)&(t)[P]][%(90)&(t)[P]][%(120)&(t)[P]][%(150)&(t)[P]][%(180)&(t)[P]][%(210)&(t)[P]][%(240)&(t)[P]][%(270)&(t)[P]][%(300)&(t)[P]][%(330)&(t)[P]]", "parametric"));

            sys.addRule(LRule("P", "<[+(5)G(20)#][+(-5)G(20)#]>f(19.8)&(40)<[+(-90)G(1.8)#][G(4)#][+(90)G(1.8)#]>", "rewrite"));
            sys.addRule(LRule("A(t):*", "+(90)%(90){[+(40)G(t)#][+(30)G(t*2)#][G(t*5)#][+(-30)G(t*2)#][+(-40)G(t)#]}", "parametric"));
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

void Systems::overwriteCol(ofColor & lineCol, ofColor & poly1Col, ofColor & poly2Col) {
    turt.overwriteCol(lineCol, poly1Col, poly2Col);
}
