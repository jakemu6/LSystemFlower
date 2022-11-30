#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    
    ofDisableArbTex();
    render_buffer.allocate(width, height, GL_RGBA);
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
               
    palms.createSystem(types::palm, numPlants, maxAxiomLevel);
    lavenders.createSystem(types::lavender, numPlants, maxAxiomLevel);
    flowerBalls.createSystem(types::flowerBall, numPlants, maxAxiomLevel);
    branches.createSystem(types::branch, numPlants, maxAxiomLevel);
    phyllos.createSystem(types::phyllotaxis, numPlants, maxAxiomLevel);
    fans.createSystem(types::fan, numPlants, maxAxiomLevel);
    acros.createSystem(types::acro, numPlants, maxAxiomLevel);
    sigmas.createSystem(types::sigma, numPlants, maxAxiomLevel);
    alphas.createSystem(types::alpha, numPlants, maxAxiomLevel);
    betas.createSystem(types::beta, numPlants, maxAxiomLevel);

    axiomLevel = 0;
    cam.setDistance(280);
    ofEnableDepthTest();
    //set init arrangement
    changeArrangement(2);
}

//--------------------------------------------------------------
void ofApp::update(){
//    cam.setDistance(ofGetMouseX());

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
            //TODO: make this call keypress instead to avoid multiple function calls
//            int num = (int)ofRandom(0,5);
//            changeArrangement(num);
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
        ofPushMatrix();
        ofRotateYDeg(rotation);
        ofBackground(252, 250, 242);
        ofNoFill();
        generateArrangement( arrangementNo );
        ofPopMatrix();
        cam.end();
    }
    render_buffer.end();
    fx << render_buffer;
    fx.update();

    // DEV setting is left side with original, right side with shader applied
    if (dev) {
        render_buffer.draw(0, 0, width/2, height);
        fx.draw(width/2, 0, width/2, height);
    } else {
        fx.draw(0, 0, width, height);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Change arrangement based on the number keys pressed
//    ofLog() << "key  = " << key;
    ofLog() << "distance  = " << cam.getDistance();


    switch( key )
    {
        case 48: {changeArrangement(0);break;}
        case 49: {changeArrangement(1);break;}
        case 50: {changeArrangement(2);break;}
        case 51: {changeArrangement(3);break;}
        case 52: {changeArrangement(4);break;}
        case 53: {changeArrangement(5);break;}
        case 54: {changeArrangement(6);break;}
        case 55: {changeArrangement(7);break;}
        case 56: {changeArrangement(8);break;}
        case 57: {changeArrangement(9);break;}

        //TESTER ARRANGEMENTS
        case 113: {changeArrangement(100);break;}
        case 119: {changeArrangement(101);break;}
        case 101: {changeArrangement(102);break;}
        case 114: {changeArrangement(103);break;}
        case 116: {changeArrangement(104);break;}
        case 121: {changeArrangement(105);break;}
        case 117: {changeArrangement(106);break;}
        case 105: {changeArrangement(107);break;}
        case 111: {changeArrangement(108);break;}
        case 112: {changeArrangement(109);break;}
            
        case 97: {changeArrangement(200);break;}
        case 115: {changeArrangement(201);break;}
        case 100: {changeArrangement(202);break;}
        case 102: {changeArrangement(203);break;}
        case 103: {changeArrangement(204);break;}
        case 104: {changeArrangement(205);break;}
        case 106: {changeArrangement(206);break;}
        case 107: {changeArrangement(207);break;}
        case 108: {changeArrangement(208);break;}
        case 59: {changeArrangement(209);break;}
    }
    

//    if (sequence == "stepThrough") {
//        axiomLevel++;
//    }
//    ofLog() << "axiom - " << axiomLevel << " result : " << phyllos.res[0][axiomLevel];
}

//--------------------------------------------------------------

void ofApp::generateArrangement(int num){
    switch( num )
    {
        case arrangement_0: {
            phyllos.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            phyllos.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            phyllos.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            phyllos.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            phyllos.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            phyllos.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            phyllos.renderArrangement(positions[6], angles[6], 1, axiomLevel);
            phyllos.renderArrangement(positions[7], angles[7], 2, axiomLevel);
            phyllos.renderArrangement(positions[8], angles[8], 3, axiomLevel);
            phyllos.renderArrangement(positions[9], angles[9], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[10], angles[10], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[11], angles[11], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[12], angles[12], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[13], angles[13], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[14], angles[14], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[15], angles[15], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[16], angles[16], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_1: {
            lavenders.renderArrangement(ofVec3f(0, 0, -20), angles[0], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, 0, -20), angles[1], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, 0, -20), angles[2], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(20, -50, 20), angles[3], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(20, -50, 20), angles[4], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(20, -50, 20), angles[5], 2, axiomLevel);
            palms.renderArrangement(positions[1], angles[6], 0, axiomLevel);
            palms.renderArrangement(positions[2], angles[7], 1, axiomLevel);
            break;
        }
        case arrangement_2: {
            flowerBalls.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[6], angles[6], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[7], angles[7], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[8], angles[8], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[9], angles[9], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[10], angles[10], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[11], angles[11], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[12], angles[12], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[13], angles[13], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[14], angles[14], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[15], angles[15], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[16], angles[16], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_3: {
            phyllos.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            phyllos.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            phyllos.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            phyllos.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            phyllos.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            phyllos.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            phyllos.renderArrangement(positions[6], angles[6], 1, axiomLevel);
            phyllos.renderArrangement(positions[7], angles[7], 2, axiomLevel);
            phyllos.renderArrangement(positions[8], angles[8], 3, axiomLevel);
            phyllos.renderArrangement(positions[9], angles[9], 4, axiomLevel);
            phyllos.renderArrangement(positions[10], angles[10], 0, axiomLevel);
            phyllos.renderArrangement(positions[11], angles[11], 1, axiomLevel);
            phyllos.renderArrangement(positions[12], angles[12], 2, axiomLevel);
            phyllos.renderArrangement(positions[13], angles[13], 3, axiomLevel);
            phyllos.renderArrangement(positions[14], angles[14], 4, axiomLevel);
            phyllos.renderArrangement(positions[15], angles[15], 0, axiomLevel);
            phyllos.renderArrangement(positions[16], angles[16], 1, axiomLevel);
            phyllos.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            phyllos.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            phyllos.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_4: {
            branches.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            branches.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            branches.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            break;
        }
        case arrangement_5: {
            phyllos.renderArrangement(ofVec3f(-20, 10, 0), angles[0], 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -20, -20), angles[1], 1, axiomLevel);
            phyllos.renderArrangement(ofVec3f(20, -50, 0), angles[2], 2, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -80, 20), angles[3], 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(-20, -110, 0), angles[4], 1, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -140, -20), angles[5], 2, axiomLevel);
            break;
        }
        case arrangement_6: {
            palms.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            palms.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            palms.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            palms.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            palms.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            palms.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            palms.renderArrangement(positions[6], angles[6], 1, axiomLevel);
            palms.renderArrangement(positions[7], angles[7], 2, axiomLevel);
            palms.renderArrangement(positions[8], angles[8], 3, axiomLevel);
            palms.renderArrangement(positions[9], angles[9], 4, axiomLevel);
            phyllos.renderArrangement(positions[10], angles[10], 0, axiomLevel);
            phyllos.renderArrangement(positions[11], angles[11], 1, axiomLevel);
            phyllos.renderArrangement(positions[12], angles[12], 2, axiomLevel);
            phyllos.renderArrangement(positions[13], angles[13], 3, axiomLevel);
            phyllos.renderArrangement(positions[14], angles[14], 4, axiomLevel);
            phyllos.renderArrangement(positions[15], angles[15], 0, axiomLevel);
            phyllos.renderArrangement(positions[16], angles[16], 1, axiomLevel);
            phyllos.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            phyllos.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            phyllos.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_7: {
            alphas.renderArrangement(ofVec3f(150, -100, 0), angles[0], 0, axiomLevel);
            alphas.renderArrangement(ofVec3f(0, -100, 150), angles[1], 1, axiomLevel);
            alphas.renderArrangement(ofVec3f(0, -100, -150), angles[2], 2, axiomLevel);
            alphas.renderArrangement(ofVec3f(-150, -100, 0), angles[3], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[2], angles[2], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[3], angles[3], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[4], angles[4], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[5], angles[5], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[6], angles[6], 4, axiomLevel);
            flowerBalls.renderArrangement(positions[7], angles[7], 0, axiomLevel);
            flowerBalls.renderArrangement(positions[8], angles[8], 1, axiomLevel);
            flowerBalls.renderArrangement(positions[9], angles[9], 2, axiomLevel);
            flowerBalls.renderArrangement(positions[10], angles[10], 3, axiomLevel);
            flowerBalls.renderArrangement(positions[11], angles[11], 4, axiomLevel);

            break;
        }
        case arrangement_8: {
            sigmas.renderArrangement(ofVec3f(0, -80, 0), ofVec3f(0, 0, 0), 0, axiomLevel);
            break;
        }
        case arrangement_9: {
            betas.renderArrangement(ofVec3f(0, -20, 0), ofVec3f(0, 0, 0), 0, axiomLevel);
            betas.renderArrangement(ofVec3f(0, -20, -50), ofVec3f(0, 0, 0), 1, axiomLevel);
            betas.renderArrangement(ofVec3f(0, -20, 50), ofVec3f(0, 0, 0), 2, axiomLevel);
            betas.renderArrangement(ofVec3f(-50, -20, 0), ofVec3f(0, 0, 0), 3, axiomLevel);
            betas.renderArrangement(ofVec3f(-50, -20, -50), ofVec3f(0, 0, 0), 4, axiomLevel);
            betas.renderArrangement(ofVec3f(-50, -20, 50), ofVec3f(0, 0, 0), 0, axiomLevel);
            betas.renderArrangement(ofVec3f(50, -20, -50), ofVec3f(0, 0, 0), 1, axiomLevel);
            betas.renderArrangement(ofVec3f(50, -20, 0), ofVec3f(0, 0, 0), 2, axiomLevel);
            betas.renderArrangement(ofVec3f(50, -20, 50), ofVec3f(0, 0, 0), 3, axiomLevel);
            break;
        }

        //TESTERS
        case arrangement_10: {
            lavenders.renderArrangement(ofVec3f(0, -20, 0), angles[0], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -20, 50), angles[1], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -20, 100), angles[2], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -20, -50), angles[3], 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -20, -100), angles[4], 4, axiomLevel);
            
            lavenders.renderArrangement(ofVec3f(50, -20, 0), angles[5], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(50, -20, 50), angles[6], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(50, -20, 100), angles[7], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(50, -20, -50), angles[8], 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(50, -20, -100), angles[9], 4, axiomLevel);
            
            lavenders.renderArrangement(ofVec3f(100, -20, 0), angles[10], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(100, -20, 50), angles[11], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(100, -20, 100), angles[12], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(100, -20, -50), angles[13], 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(100, -20, -100), angles[14], 4, axiomLevel);
            
            lavenders.renderArrangement(ofVec3f(-50, -20, 0), angles[15], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-50, -20, 50), angles[16], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-50, -20, 100), angles[17], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-50, -20, -50), angles[18], 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-50, -20, -100), angles[19], 4, axiomLevel);
            
            lavenders.renderArrangement(ofVec3f(-100, -20, 0), angles[15], 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-100, -20, 50), angles[16], 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-100, -20, 100), angles[17], 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-100, -20, -50), angles[18], 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-100, -20, -100), angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_11: {
            acros.renderArrangement(positions[5] + ofVec3f(0, 200, 0), angles[5], 0, axiomLevel);
            acros.renderArrangement(positions[6] + ofVec3f(0, 200, 0), angles[6], 1, axiomLevel);
            acros.renderArrangement(positions[7] + ofVec3f(0, 200, 0), angles[7], 2, axiomLevel);
            acros.renderArrangement(positions[8] + ofVec3f(0, 200, 0), angles[8], 3, axiomLevel);
            branches.renderArrangement(positions[10] + ofVec3f(0, -100, 0), angles[10], 0, axiomLevel);
            branches.renderArrangement(positions[11] + ofVec3f(0, -100, 0), angles[11], 1, axiomLevel);
            branches.renderArrangement(positions[12] + ofVec3f(0, -100, 0), angles[12], 2, axiomLevel);
            branches.renderArrangement(positions[13] + ofVec3f(0, -100, 0), angles[13], 3, axiomLevel);
            break;
        }
        case arrangement_12: {
            fans.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            fans.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            fans.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            fans.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            fans.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            fans.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            fans.renderArrangement(positions[6], angles[6], 1, axiomLevel);
            fans.renderArrangement(positions[7], angles[7], 2, axiomLevel);
            fans.renderArrangement(positions[8], angles[8], 3, axiomLevel);
            fans.renderArrangement(positions[9], angles[9], 4, axiomLevel);
            betas.renderArrangement(positions[10], angles[10], 0, axiomLevel);
            betas.renderArrangement(positions[11], angles[11], 1, axiomLevel);
            betas.renderArrangement(positions[12], angles[12], 2, axiomLevel);
            betas.renderArrangement(positions[13], angles[13], 3, axiomLevel);
            betas.renderArrangement(positions[14], angles[14], 4, axiomLevel);
            betas.renderArrangement(positions[15], angles[15], 0, axiomLevel);
            betas.renderArrangement(positions[16], angles[16], 1, axiomLevel);
            betas.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            betas.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            betas.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_R: {for (int i = 0; i < numPlants; i++) {flowerBalls.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_T: {for (int i = 0; i < numPlants; i++) {phyllos.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_Y: {for (int i = 0; i < numPlants; i++) {fans.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_U: {for (int i = 0; i < numPlants; i++) {acros.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_I: {for (int i = 0; i < numPlants; i++) {sigmas.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_O: {for (int i = 0; i < numPlants; i++) {alphas.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}
        case arrangement_P: {for (int i = 0; i < numPlants; i++) {betas.renderArrangement(positions[i], angles[i], i, axiomLevel);}break;}

        case arrangement_A: {palms.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_S: {lavenders.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_D: {branches.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_F: {flowerBalls.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_G: {phyllos.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_H: {fans.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_J: {acros.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_K: {sigmas.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_L: {alphas.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_SEMICOLON: {betas.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}

    }
}

void ofApp::changeArrangement(int num){
    //change the colours of all the arrangements into one of the three preset colours
    overwriteCol();
    
    //create new positions and angles
    positions.clear();
    angles.clear();
    randPos.set(ofRandom(0.001,2), ofRandom(0.001,0.9), ofRandom(0.001,2));
    randAng.set(ofRandom(0.001,0.9), ofRandom(0.001,0.9), ofRandom(0.001,0.9));
    for(int i = 1; i < 20 + 1; i++) {
        ofVec3f position(-300 + (600 * ofNoise(i * randPos.x)), -300 + (400 * ofNoise(i * randPos.y)), -300 + (600 * ofNoise(i * randPos.z)));
        ofVec3f angle(-80 + (160 * ofNoise(i * randAng.x)), 360 * ofNoise(i * randAng.y), -80 + (160 * ofNoise(i * randAng.z)));
        positions.push_back(position);
        angles.push_back(angle);
    }
    
    //change arrangement based on number sent
    switch ( num )
    {
        case 0: {arrangementNo = arrangement_0;break;}
        case 1: {arrangementNo = arrangement_1;break;}
        case 2: {arrangementNo = arrangement_2;break;}
        case 3: {arrangementNo = arrangement_3;break;}
        case 4: {arrangementNo = arrangement_4;break;}
        case 5: {arrangementNo = arrangement_5;break;}
        case 6: {arrangementNo = arrangement_6;break;}
        case 7: {arrangementNo = arrangement_7;break;}
        case 8: {arrangementNo = arrangement_8;break;}
        case 9: {arrangementNo = arrangement_9;break;}
            
        case 100: {arrangementNo = arrangement_10;break;}
        case 101: {arrangementNo = arrangement_11;break;}
        case 102: {arrangementNo = arrangement_12;break;}
        case 103: {arrangementNo = arrangement_R;break;}
        case 104: {arrangementNo = arrangement_T;break;}
        case 105: {arrangementNo = arrangement_Y;break;}
        case 106: {arrangementNo = arrangement_U;break;}
        case 107: {arrangementNo = arrangement_I;break;}
        case 108: {arrangementNo = arrangement_O;break;}
        case 109: {arrangementNo = arrangement_P;break;}
            
        case 200: {arrangementNo = arrangement_A;break;}
        case 201: {arrangementNo = arrangement_S;break;}
        case 202: {arrangementNo = arrangement_D;break;}
        case 203: {arrangementNo = arrangement_F;break;}
        case 204: {arrangementNo = arrangement_G;break;}
        case 205: {arrangementNo = arrangement_H;break;}
        case 206: {arrangementNo = arrangement_J;break;}
        case 207: {arrangementNo = arrangement_K;break;}
        case 208: {arrangementNo = arrangement_L;break;}
        case 209: {arrangementNo = arrangement_SEMICOLON;break;}
    }
}

void ofApp::overwriteCol(){
    
    ofColor palmsBranchCol;
    int palmsBranchNum = ofRandom(0,3);
    switch ( palmsBranchNum )
    {
        case 0: { palmsBranchCol.set(108, 96, 36); break; }
        case 1: { palmsBranchCol.set(91, 98, 46); break; }
        case 2: { palmsBranchCol.set(100, 106, 88); break; }
    }
    
    ofColor palmsPoly1Col;
    int palmsPoly1Num = ofRandom(0,3);
    switch ( palmsPoly1Num )
    {
        case 0: { palmsPoly1Col.set(162, 140, 55); break; }
        case 1: { palmsPoly1Col.set(131, 138, 45); break; }
        case 2: { palmsPoly1Col.set(66, 96, 45); break; }
    }
    
    ofColor palmsPoly2Col;
    int palmsPoly2Num = 0;
    switch ( palmsPoly2Num )
    {
        case 0: { palmsPoly2Col.set(0, 0, 0); break; }
    }
    palms.overwriteCol(palmsBranchCol, palmsPoly1Col, palmsPoly2Col);
    
    ofColor lavenderBranchCol;
    int lavenderBranchNum = ofRandom(0,3);
    switch ( lavenderBranchNum )
    {
        case 0: { lavenderBranchCol.set(66, 96, 45); break; }
        case 1: { lavenderBranchCol.set(9, 97, 72); break; }
        case 2: { lavenderBranchCol.set(54, 86, 60); break; }
    }
    
    ofColor lavenderPoly1Col;
    int lavenderPoly1Num = ofRandom(0,3);
    switch ( lavenderPoly1Num )
    {
        case 0: { lavenderPoly1Col.set(66, 96, 45); break; }
        case 1: { lavenderPoly1Col.set(9, 97, 72); break; }
        case 2: { lavenderPoly1Col.set(54, 86, 60); break; }
    }
    
    ofColor lavenderPoly2Col;
    int lavenderPoly2Num = ofRandom(0,3);
    switch ( lavenderPoly2Num )
    {
        case 0: { lavenderPoly2Col.set(152, 109, 178); break; }
        case 1: { lavenderPoly2Col.set(171, 59, 58); break; }
        case 2: { lavenderPoly2Col.set(246, 197, 85); break; }
    }
    lavenders.overwriteCol(lavenderBranchCol, lavenderPoly1Col, lavenderPoly2Col);
    
    ofColor branchBranchCol;
    int branchBranchNum = ofRandom(0,3);
    switch ( branchBranchNum )
    {
        case 0: { branchBranchCol.set(66, 96, 45); break; }
        case 1: { branchBranchCol.set(9, 97, 72); break; }
        case 2: { branchBranchCol.set(54, 86, 60); break; }
    }
    
    ofColor branchPoly1Col;
    int branchPoly1Num = ofRandom(0,3);
    switch ( branchPoly1Num )
    {
        case 0: { branchPoly1Col.set(66, 96, 45); break; }
        case 1: { branchPoly1Col.set(9, 97, 72); break; }
        case 2: { branchPoly1Col.set(54, 86, 60); break; }
    }
    
    ofColor branchPoly2Col;
    int branchPoly2Num = ofRandom(0,3);
    switch ( branchPoly2Num )
    {
        case 0: { branchPoly2Col.set(143, 119, 181); break; }
        case 1: { branchPoly2Col.set(171, 59, 58); break; }
        case 2: { branchPoly2Col.set(247, 217, 76); break; }
    }
    branches.overwriteCol(branchBranchCol, branchPoly1Col, branchPoly2Col);
    
    ofColor flowerBallBranchCol;
    int flowerBallBranchNum = ofRandom(0,3);
    switch ( flowerBallBranchNum )
    {
        case 0: { flowerBallBranchCol.set(66, 96, 45); break; }
        case 1: { flowerBallBranchCol.set(9, 97, 72); break; }
        case 2: { flowerBallBranchCol.set(54, 86, 60); break; }
    }
    
    ofColor flowerBallPoly1Col;
    int flowerBallPoly1Num = 0;
    switch ( flowerBallPoly1Num )
    {
        case 0: { flowerBallPoly1Col.set(0, 0, 0); break; }
    }
    
    ofColor flowerBallPoly2Col;
    int flowerBallPoly2Num = ofRandom(0,3);
    switch ( flowerBallPoly2Num )
    {
        case 0: { flowerBallPoly2Col.set(181, 202, 160); break; }
        case 1: { flowerBallPoly2Col.set(189, 192, 186); break; }
        case 2: { flowerBallPoly2Col.set(215, 185, 142); break; }
    }
    flowerBalls.overwriteCol(flowerBallBranchCol, flowerBallPoly1Col, flowerBallPoly2Col);
    
    ofColor phyllotaxisBranchCol;
    int phyllotaxisBranchNum = ofRandom(0,3);
    switch ( phyllotaxisBranchNum )
    {
        case 0: { phyllotaxisBranchCol.set(66, 96, 45); break; }
        case 1: { phyllotaxisBranchCol.set(9, 97, 72); break; }
        case 2: { phyllotaxisBranchCol.set(54, 86, 60); break; }
    }
    
    ofColor phyllotaxisPoly1Col;
    int phyllotaxisPoly1Num = ofRandom(0,3);
    switch ( phyllotaxisPoly1Num )
    {
        case 0: { phyllotaxisPoly1Col.set(66, 96, 45); break; }
        case 1: { phyllotaxisPoly1Col.set(9, 97, 72); break; }
        case 2: { phyllotaxisPoly1Col.set(54, 86, 60); break; }
    }
    
    ofColor phyllotaxisPoly2Col;
    int phyllotaxisPoly2Num = ofRandom(0,3);
    switch ( phyllotaxisPoly2Num )
    {
        case 0: { phyllotaxisPoly2Col.set(251, 153, 102); break; }
        case 1: { phyllotaxisPoly2Col.set(171, 59, 58); break; }
        case 2: { phyllotaxisPoly2Col.set(254, 223, 225); break; }
    }
    phyllos.overwriteCol(phyllotaxisBranchCol, phyllotaxisPoly1Col, phyllotaxisPoly2Col);
    
    ofColor fansBranchCol;
    int fansBranchNum = ofRandom(0,3);
    switch ( fansBranchNum )
    {
        case 0: { fansBranchCol.set(108, 96, 36); break; }
        case 1: { fansBranchCol.set(91, 98, 46); break; }
        case 2: { fansBranchCol.set(100, 106, 88); break; }
    }
    
    ofColor fansPoly1Col;
    int fansPoly1Num = ofRandom(0,3);
    switch ( fansPoly1Num )
    {
        case 0: { fansPoly1Col.set(162, 140, 55); break; }
        case 1: { fansPoly1Col.set(131, 138, 45); break; }
        case 2: { fansPoly1Col.set(66, 96, 45); break; }
    }
    
    ofColor fansPoly2Col;
    int fansPoly2Num = 0;
    switch ( fansPoly2Num )
    {
        case 0: { fansPoly2Col.set(0, 0, 0); break; }
    }
    palms.overwriteCol(fansBranchCol, fansPoly1Col, fansPoly2Col);
}
