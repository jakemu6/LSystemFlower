

#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    ofDisableArbTex();

    render_buffer.allocate(width, height, GL_RGBA);
    img_buffer.allocate(width, height, GL_RGBA);
    img.load("rand.png");
    fx.allocate(width, height);
    fx.setPasses(1);
    //https://www.shadertoy.com/view/ltyGRV
    //ShaderToy translation key
    //resolution - iResolution (Gets the resolution of the window)
    //Res0 - size0 (Gets the resolution of the texture)
    //tex0 - iChannel (Gets the texture sample)
    
    fx.setCode("#version 120\n \
                        uniform sampler2D tex0; \n \
                        uniform vec2 resolution;    \n \
                        uniform vec2 size0; \n \
                        \
                        vec4 getCol(vec2 pos)   \n \
                        {   \n \
                            vec2 uv=pos/size0;   \n \
                            vec4 c1 = texture2D(tex0,uv);    \n \
                            vec4 c2 = vec4(.4);     \n \
                            float d = clamp(dot(c1.xyz,vec3(-0.5,0.0,-0.5)),0.0,1.0);   \n \
                            return mix(c1,c2,1.8*d);    \n \
                        }       \n \
                        \
                        vec4 getCol2(vec2 pos)   \n \
                        {    \n \
                           vec2 uv=pos/size0;     \n \
                           vec4 c1 = texture2D(tex0,uv);  \n \
                           vec4 c2 = vec4(1.5);  \n \
                           float d = clamp(dot(c1.xyz,vec3(-0.5,0.0,-0.5)),0.0,1.0);     \n \
                           return mix(c1,c2,1.8*d);  \n \
                        }    \n \
                        \
                        vec2 getGrad(vec2 pos,float delta)  \n \
                        {   \n \
                            vec2 d=vec2(delta,0.0);   \n \
                            return vec2(    \n \
                                dot((getCol(pos+d.xy)-getCol(pos-d.xy)).xyz,vec3(.333)),    \n \
                                dot((getCol(pos+d.yx)-getCol(pos-d.yx)).xyz,vec3(.333))     \n \
                            )/delta;    \n \
                        }   \n \
                        vec2 getGrad2(vec2 pos,float delta) \n \
                        {   \n \
                            vec2 d=vec2(delta,0);   \n \
                            return vec2(    \n \
                                dot((getCol2(pos+d.xy)-getCol2(pos-d.xy)).xyz,vec3(.333)),  \n \
                                dot((getCol2(pos+d.yx)-getCol2(pos-d.yx)).xyz,vec3(.333))   \n \
                            )/delta;    \n \
                        }   \n \
                        \
                        float htPattern(vec2 pos)   \n \
                        {   \n \
                            float p;    \n \
                            p=clamp((pow(.8,2.)-.45),0.,1.);    \n \
                            return p;   \n \
                        }   \n \
                        \
                        float getVal(vec2 pos, float level) \n \
                        {   \n \
                            return length(getCol(pos).xyz)+0.0001*length(pos-0.5*size0); \n \
                            return dot(getCol(pos).xyz,vec3(.333)); \n \
                        }   \n \
                        \
                        vec4 getBWDist(vec2 pos)    \n \
                        {   \n \
                            return vec4(smoothstep(.9,1.1,getVal(pos,0.)*.9+htPattern(pos*.7)));    \n \
                        }   \n \
                        \
                        #define SampNum 10\n \
                        \
                        \
                        void main(void) { \n \
                            vec2  st = gl_TexCoord[0].st;   \n \
                            vec2 pos = ((st.xy - resolution.xy * 0.5) / resolution.y * size0.y) + size0.xy * 0.5;   \n \
                            vec2 pos2=pos;  \n \
                            vec2 pos3=pos;  \n \
                            vec2 pos4=pos;  \n \
                            vec2 pos0=pos;  \n \
                            vec3 col=vec3(0);   \n \
                            vec3 col2=vec3(0);  \n \
                            float cnt=0.0;  \n \
                            float cnt2=0.;  \n \
                            for(int i=0;i<1*SampNum;i++)    \n \
                            {   \n \
                                vec2 gr =getGrad(pos, 2.0);     \n \
                                vec2 gr2=getGrad(pos2,2.0);     \n \
                                vec2 gr3=getGrad2(pos3,2.0);     \n \
                                vec2 gr4=getGrad2(pos4,2.0);     \n \
                                float grl=clamp(10.*length(gr),0.,1.);  \n \
                                float gr2l=clamp(10.*length(gr2),0.,1.);    \n \
                                pos +=1.0 *normalize((gr.yx*vec2(1,-1)));     \n \
                                pos2-=1.0 *normalize((gr2.yx*vec2(1,-1)));    \n \
                                float fact=1.-float(i)/float(SampNum);  \n \
                                col+=fact*mix(vec3(1.2),getBWDist(pos).xyz*2.,grl);     \n \
                                col+=fact*mix(vec3(1.2),getBWDist(pos2).xyz*2.,gr2l);   \n \
                                pos3+=.25*normalize(gr3)+.1;    \n \
                                pos4-=.5 *normalize(gr4);    \n \
                                float f1=3.*fact;   \n \
                                float f2=4.*(.7-fact);  \n \
                                col2+=f1*(getCol2(pos3).xyz+.25+.4);   \n \
                                col2+=f2*(getCol2(pos4).xyz+.25+.4);   \n \
                                cnt2+=f1+f2;    \n \
                                cnt+=fact;      \n \
                            }   \n \
                            col/=cnt*2.5;   \n \
                            col2/=cnt2*1.65;    \n \
                            \n \
                            col = clamp(clamp(col*.9+.6,0.,1.)*col2,0.,1.); \n \
                            \n \
                            vec4 y = texture2D(tex0, st); \n \
                            gl_FragColor = vec4(col, 1.0); \n \
                        }");
               
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
    // G(x,y) - Uses the x to determing the amount to move by, ignores y
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
    system.addRule(LRule("a(t):t=0", "C", "parametric"));

    system.addRule(LRule("I(t):*", "F(t)", "parametric"));
    system.addRule(LRule("p(t):*", "&(20)%(t)", "parametric"));

    //Create a branch and then create a 1/2 chance of making a flower
    system.addRule(LRule("L(t):*", "[++(t)F(5)K(r,1_5)]", "parametric"));

    //Make the flower
    system.addRule(LRule("K(t):*", "YFX(r,70_80)", "parametric"));

    system.addRule(LRule("Y", "[%(0)&(35)Q][%(72)&(35)Q][%(144)&(35)Q][%(216)&(35)Q][%(288)&(35)Q]", "rewrite"));
    system.addRule(LRule("X(t):*", "[%(0)&(t)W][%(30)&(t)W][%(60)&(t)W][%(90)&(t)W][%(120)&(t)W][%(150)&(t)W][%(180)&(t)W][%(210)&(t)W][%(240)&(t)W][%(270)&(t)W][%(300)&(t)W][%(330)&(t)W]", "parametric"));

    system.addRule(LRule("Q", "{#[++GG#][GGG#][--GG#]}", "rewrite"));
    system.addRule(LRule("W", "<#[++G(5)#][G(6)#][--G(5)#]>", "rewrite"));

    for (int i = 0; i < NumOfSys; i++) {
        vector<string> results;
        results = system.getLevels(maxAxiomLevel + 1);
        resultsList.push_back(results);
    }

    ofColor branchCol1;
    branchCol1.r=114;
    branchCol1.g=72;
    branchCol1.b=50;

    ofColor poly1Col1;
    poly1Col1.r=247;
    poly1Col1.g=194;
    poly1Col1.b=66;

    ofColor poly2Col1;
    poly2Col1.r=251;
    poly2Col1.g=226;
    poly2Col1.b=81;

    turtle.setup(theta, length, branchCol1, poly1Col1, poly2Col1);

    ofVec3f start;
    start.set(0, 0, 0);


    system2.setStart("a(r,0_360)");
    system2.addRule(LRule("a(t):*", "%(t)F(200)B(1)", "parametric"));

    system2.addRule(LRule("B(t):t>0", "&(2)F(100)B(t-1)", "parametric"));
    system2.addRule(LRule("B(t):t=0", "&(2)F(100)LB(1)", "parametric"));

    //set of leaves
    system2.addRule(LRule("L", "[H(10)[D(4)][C(4)]][I(10)[D(4)][C(4)]]", "rewrite"));

    //each leaf on either side
    // D and C is either side of the leaf
    system2.addRule(LRule("D(t):t>0", "[+(-3)D(t-1){#]#E(t-1)#}", "parametric"));
    system2.addRule(LRule("C(t):t>0", "[+(3)C(t-1){#]#E(t-1)#}", "parametric"));
    system2.addRule(LRule("E(t):t>0", "G(400)E(t-1)", "parametric"));
    system2.addRule(LRule("H(t):t>0", "+(t)H(t-1)", "parametric"));
    system2.addRule(LRule("I(t):t>0", "+(-t)I(t-1)", "parametric"));



//    system2.addRule(LRule("c(t):*", "G(5,1)[-d(t)#][c(t+1)][+d(t)#]", "parametric"));
//    system2.addRule(LRule("d(t):t>0", "G(1,1)B(t-1)", "parametric"));
//    system2.addRule(LRule("G(s,r):*", "G(s*r,r)", "parametric"));



    for (int i = 0; i < NumOfSys2; i++) {
        vector<string> results;
        results = system2.getLevels(maxAxiomLevel + 1);
        resultsList2.push_back(results);

        float xPos = ofRandom(-20,20);
        xPositions.push_back(xPos);
    }


    ofColor branchCol2;
    branchCol2.r=162;
    branchCol2.g=140;
    branchCol2.b=55;

    ofColor poly1Col2;
    poly1Col2.r=66;
    poly1Col2.g=96;
    poly1Col2.b=45;

    ofColor poly2Col2;
    poly2Col2.r=251;
    poly2Col2.g=226;
    poly2Col2.b=81;

    turtle2.setup(theta, length, branchCol2, poly1Col2, poly2Col2);

    axiomLevel = 0;
    cam.setDistance(1000);
    ofEnableDepthTest();
    

    
//    fbo.allocate(ofGetWidth(),ofGetHeight());
//    fbo.begin();
//    ofClear(255);
//    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (rotate) {
        rotation += rotationSpeed;
    }

    if (sequence == "static") {
        axiomLevel = maxAxiomLevel;
    } else if (sequence == "loop") {
        axiomLevel += growthRate;
        if (axiomLevel > maxAxiomLevel) {
            axiomLevel = 0;
        }
    } else if (sequence == "reverseLoop") {
        if (axiomLevel >= maxAxiomLevel) {
            growthRate = -growthRate;
        } else if (axiomLevel < 0) {
            growthRate = -growthRate;
        }
        axiomLevel += growthRate;
    } else if (sequence == "stepThrough") {
        if (axiomLevel >= maxAxiomLevel) {
            axiomLevel = 0;
        } else if (axiomLevel < 0) {
            axiomLevel = maxAxiomLevel;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    render_buffer.begin();
    {
        cam.begin();
//        ofPushStyle();
        ofPushMatrix();
        ofRotateYDeg(rotation);
        ofBackground(252, 250, 242);
        ofNoFill();
        for(int i = 0; i < resultsList.size(); i++) {
                turtle.draw(resultsList[i][axiomLevel], 0, -50, 0); // input string, x, y, z
        }
        for(int i = 0; i < resultsList2.size(); i++) {
                turtle2.draw(resultsList2[i][axiomLevel], xPositions[i], -60, 0); // input string, x, y, z
        }
        ofPopMatrix();
//        ofPopStyle();
        cam.end();
    }
    render_buffer.end();
//    img_buffer.begin();
//    {
//        img.draw(0, 0, ofGetWidth(), ofGetHeight());
//    }
//    img_buffer.end();

//
    fx << render_buffer;
//    fx << img_buffer;
    
    ofBackgroundGradient(ofColor(0), ofColor(255), OF_GRADIENT_LINEAR);


    

    // Left side with original, right side with shader applied
    render_buffer.draw(0, 0, width, height);
    fx.update();
    fx.draw(width, 0, width, height);
    
//    fx.draw(0, 0, width, height);


//    fx.begin();
//    ofClear(255, 255);
//    fx.draw();
//    fx.end();
//    fx.update();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    if( key == 's' ){
//        #ifdef TARGET_OPENGLES
//            shader.load("shadersES2/shader");
//        ofLog() << "ES2";
//
//        #else
//            if(ofIsGLProgrammableRenderer()){
//                shader.load("shadersGL3/shader");
//                ofLog() << "GL3";
//            }else{
//                shader.load("shadersGL2/shader");
//                ofLog() << "GL2  " << doShader;
//
//            }
//        #endif
//        doShader = !doShader;
//    }
    
    if (sequence == "stepThrough") {
        axiomLevel++;
    }
//    resultsList.clear();

//    for (int i = 0; i < NumOfSys; i++) {
//        vector<string> results;
//        results = system.getLevels(maxAxiomLevel + 1);
//        resultsList.push_back(results);
//    }

//    ofLog() << "axiom - " << axiomLevel << " result : " << resultsList[0][axiomLevel];

    ofLog() << "axiom - " << axiomLevel << " result : " << resultsList2[0][axiomLevel];

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
