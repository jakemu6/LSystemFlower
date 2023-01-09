#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    

    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    
    ofDisableArbTex();
    render_buffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    final_buffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    pix.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR_ALPHA);
    fx.allocate(ofGetWidth(), ofGetHeight());
    ofLog() << ofGetWidth();
    ofLog() << ofGetHeight();

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
                        }"
    );
    

    if (!dev) {
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
    }
               
    camDistance = 400;
    axiomLevel = 0;
    //set init arrangement
    currentArrangement = 0;
    changeArrangement(currentArrangement);
    shift_x = 0;
    shift_y = 0;
    
    //GUI FOR TESTING
//    gui.setup();
//    gui.add(position1.setup("pos 1", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(angle1.setup("ang 1", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(position2.setup("pos 2", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(angle2.setup("ang 2", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(position3.setup("pos 3", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(angle3.setup("ang 3", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(position4.setup("pos 4", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(angle4.setup("ang 4", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(position5.setup("pos 5", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
//    gui.add(angle5.setup("ang 5", ofVec3f(0, 0, 0), ofVec3f(-180, -180, -180), ofVec3f(180, 180, 180)));
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.setDistance(camDistance);
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
            int num = (int)ofRandom(0,20);
            changeArrangement(num);
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
        ofEnableDepthTest();
        ofTranslate(shift_x, shift_y, 0);
//        ofRotateZDeg(90);
        ofRotateXDeg(pitch);
        ofRotateYDeg(rotation);
        ofBackground(252, 250, 242);
        ofNoFill();
        generateArrangement( arrangementNo );
        ofDisableDepthTest();
        ofPopMatrix();
        cam.end();
    }
    render_buffer.end();
    fx << render_buffer;
    fx.update();
    ofFill();
    ofSetColor(255, 255, 255);
//    gui.draw();
    
    // DEV setting is left side with original, right side with shader applied
    if (dev) {
        render_buffer.draw(0, 0, ofGetWidth()/2, ofGetHeight());
        fx.draw(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
    } else {
        final_buffer.begin();
        fx.draw(0, 0, ofGetWidth(), ofGetHeight());
        final_buffer.end();
    }
    //REDRAW OVER THE FINAL BUFFER
    fx.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Change arrangement based on the number keys pressed
//    ofLog() << "key  = " << key;
    switch( key )
    {
        //KEY 0 1 2 3 4 5 6 7 8 9
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
        //KEY Q W E R T Y U I O P
        case 113: {changeArrangement(10);break;}
        case 119: {changeArrangement(11);break;}
        case 101: {changeArrangement(12);break;}
        case 114: {changeArrangement(13);break;}
        case 116: {changeArrangement(14);break;}
        case 121: {changeArrangement(15);break;}
        case 117: {changeArrangement(16);break;}
        case 105: {changeArrangement(17);break;}
        case 111: {changeArrangement(18);break;}
        case 112: {changeArrangement(19);break;}
        //KEY A S D F G H J K L ;
        case 97: {changeArrangement(20);break;}
        case 115: {changeArrangement(21);break;}
        case 100: {changeArrangement(22);break;}
        case 102: {changeArrangement(23);break;}
        case 103: {changeArrangement(24);break;}
        case 104: {changeArrangement(25);break;}
        case 106: {changeArrangement(26);break;}
        case 107: {changeArrangement(27);break;}
        case 108: {changeArrangement(28);break;}
        case 59: {changeArrangement(29);break;}
           
//        //SCREENSHOT CONTROLS
//        case 122: {
//            currentArrangement--;
//            if (currentArrangement < 0) {currentArrangement = 29;}
//            changeArrangement(currentArrangement);
//            break;
//        }
//        case 120: {
//            currentArrangement++;
//            if (currentArrangement > 29) {currentArrangement = 0;}
//            changeArrangement(currentArrangement);
//            break;
//        }
//            //SCREENSHOT FX TO IMG USE 'C'
//        case 99: {
//            final_buffer.readToPixels(pix);
//            string time = ofGetTimestampString();
//            ofSaveImage(pix, "A3_" + time + ".png", OF_IMAGE_QUALITY_BEST);
//            break;
//        }
//        //use arrows to rotate scene
//        case 57356: {rotation += 10;break;}
//        case 57358: {rotation -= 10;break;}
//        case 57357: {pitch += 10;break;}
//        case 57359: {pitch -= 10;break;}
//        // + - to zoom in and out
//        case 49: {shift_y += 10;break;}
//        case 51: {shift_y -= 10;break;}
//        // num pad 1 2 3 5 to move scene
//        case 50: {shift_x -= 10;break;}
//        case 53: {shift_x += 10;break;}
//        case 45: {camDistance += 30;break;}
//        case 43: {camDistance -= 30;break;}
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
            //FOR TESTING WITH GUI
            //            flowerBalls.renderArrangement(ofVec3f(position1->x, position1->y, position1->z), ofVec3f(angle1->x, angle1->y, angle1->z), 0, axiomLevel);
            //            flowerBalls.renderArrangement(ofVec3f(position2->x, position2->y, position2->z), ofVec3f(angle2->x, angle2->y, angle2->z), 1, axiomLevel);
            //            betas.renderArrangement(ofVec3f(position3->x, position3->y, position3->z), ofVec3f(angle3->x, angle3->y, angle3->z), 2, axiomLevel);
            //            betas.renderArrangement(ofVec3f(position4->x, position4->y, position4->z), ofVec3f(angle4->x, angle4->y, angle4->z), 3, axiomLevel);
            //            betas.renderArrangement(ofVec3f(position5->x, position5->y, position5->z), ofVec3f(angle5->x, angle5->y, angle5->z), 4, axiomLevel);
            break;
        }
        case arrangement_1: {
            fans.renderArrangement(ofVec3f(0, -75, 0), ofVec3f(0, 35, 0), 0, axiomLevel);
            fans.renderArrangement(ofVec3f(-15, -44, -24), ofVec3f(0, -82, 0), 1, axiomLevel);
            acros.renderArrangement(ofVec3f(-37, 4, 0), ofVec3f(180, 0, 0), 3, axiomLevel);
            acros.renderArrangement(ofVec3f(29, -60, 0), ofVec3f(180, 0, 0), 4, axiomLevel);
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
            acros.renderArrangement(positions[17], angles[17] + ofVec3f(180, 0, 0), 2, axiomLevel);
            acros.renderArrangement(positions[18], angles[18] + ofVec3f(180, 0, 0), 3, axiomLevel);
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
            branches.renderArrangement(positions[17], angles[17], 2, axiomLevel);
            branches.renderArrangement(positions[18], angles[18], 3, axiomLevel);
            branches.renderArrangement(positions[19], angles[19], 4, axiomLevel);
            break;
        }
        case arrangement_4: {
            branches.renderArrangement(positions[0], angles[0], 0, axiomLevel);
            branches.renderArrangement(positions[1], angles[1], 1, axiomLevel);
            branches.renderArrangement(positions[2], angles[2], 2, axiomLevel);
            alphas.renderArrangement(positions[3], angles[3], 3, axiomLevel);
            alphas.renderArrangement(positions[4], angles[4], 4, axiomLevel);
            alphas.renderArrangement(positions[5], angles[5], 0, axiomLevel);
            break;
        }
        case arrangement_5: {
            phyllos.renderArrangement(ofVec3f(4, -40, 0), ofVec3f(0, 0, 0), 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -10, 0), ofVec3f(0, 0, 0), 1, axiomLevel);
            phyllos.renderArrangement(ofVec3f(-2, 30, 0), ofVec3f(0, 0, 0), 2, axiomLevel);
            alphas.renderArrangement(ofVec3f(0, -80, 0), ofVec3f(0, 0, 0), 0, axiomLevel);
            break;
        }
        case arrangement_6: {
            palms.renderArrangement(ofVec3f(0, -37, 0), ofVec3f(-37, 118, 50), 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(-6, -44, 0), ofVec3f(-13, 0, -11), 1, axiomLevel);
            betas.renderArrangement(ofVec3f(17, -58, 26), ofVec3f(0, 0, 0), 2, axiomLevel);
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
            phyllos.renderArrangement(ofVec3f(2, -59, 30), ofVec3f(26, -125, -11), 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -60, -5), ofVec3f(22, -11, 18), 1, axiomLevel);
            fans.renderArrangement(ofVec3f(-13, -91, 0), ofVec3f(4, 156, 24), 2, axiomLevel);
            betas.renderArrangement(ofVec3f(-7, -14, 0), ofVec3f(39, -7, -24), 3, axiomLevel);
            break;
        }
        case arrangement_9: {
            alphas.renderArrangement(ofVec3f(11, -20, 31), ofVec3f(-42, 7, 0), 0, axiomLevel);
            betas.renderArrangement(ofVec3f(50, -11, 22), ofVec3f(0, -4, 22), 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -30, 0), ofVec3f(37, 0, 0), 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, 9, 9), ofVec3f(61, 0, 0), 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(7, -39, 35), ofVec3f(-22, 0, -17), 2, axiomLevel);
            break;
        }

        //TESTERS
        case arrangement_10: {
            betas.renderArrangement(ofVec3f(0, -33, 0), ofVec3f(-28, -16, 0), 0, axiomLevel);
            betas.renderArrangement(ofVec3f(-20, -34, 0), ofVec3f(9, -4, 0), 1, axiomLevel);
            betas.renderArrangement(ofVec3f(0, -28, 0), ofVec3f(0, 0, 0), 2, axiomLevel);
            betas.renderArrangement(ofVec3f(0, -50, 0), ofVec3f(-2, 0, -17), 3, axiomLevel);
            betas.renderArrangement(ofVec3f(-13, -59, 0), ofVec3f(-6, -2, 15), 4, axiomLevel);
            betas.renderArrangement(ofVec3f(-4, -33, 0), ofVec3f(57, -40, 28), 0, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(-11, -2, -11), ofVec3f(-11, -180, -7), 0, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(-9, 1, 0), ofVec3f(31, 0, 0), 1, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(0, -59, -15), ofVec3f(33, 2, 0), 2, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(0, -33, 0), ofVec3f(-15, -125, 15), 3, axiomLevel);
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
        case arrangement_13: {
            phyllos.renderArrangement(ofVec3f(9, -90, 0), ofVec3f(26, 0, -4), 1, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -77, 0), ofVec3f(4, 6, 9), 2, axiomLevel);
            acros.renderArrangement(ofVec3f(0, -65, 18), ofVec3f(0, -60, 180), 0, axiomLevel);
            break;
        }
        case arrangement_14: {
            palms.renderArrangement(ofVec3f(24, -100, 4), ofVec3f(-68, -25, -42), 2, axiomLevel);
            palms.renderArrangement(ofVec3f(31, -144, 85), ofVec3f(35, 160, -10), 0, axiomLevel);
            phyllos.renderArrangement(ofVec3f(20, -50, 0), ofVec3f(-20, 10, 0), 2, axiomLevel);
            phyllos.renderArrangement(ofVec3f(0, -80, 20), ofVec3f(20, 60, 0), 0, axiomLevel);
            break;
        }
        case arrangement_15: {
            flowerBalls.renderArrangement(ofVec3f(2, -47, 42), ofVec3f(7, -11, 18), 0, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(-7, -28, 15), ofVec3f(-26, 180, 13), 1, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(4, -12, 24), ofVec3f(33, 55, -48), 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -30, 0), ofVec3f(37, 0, 0), 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, 9, 9), ofVec3f(61, 0, 0), 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(17, -58, 108), ofVec3f(-31, 40, -4), 2, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(35, -23, 64), ofVec3f(29, 2, 0), 0, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(6, 28, 39), ofVec3f(13, 0, 17), 1, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(-9, -56, 0), ofVec3f(0, 0, 0), 2, axiomLevel);
            branches.renderArrangement(ofVec3f(26, -45, 17), ofVec3f(0, 0, 0), 2, axiomLevel);
            break;
        }
        case arrangement_16: {
            flowerBalls.renderArrangement(ofVec3f(24, -8, 0), ofVec3f(0, 180, 0), 0, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(33, -21, 0), ofVec3f(0, 20, 0), 1, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(31, -39, 20), ofVec3f(0, -66, 0), 2, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(18, -30, 0), ofVec3f(0, -86, 0), 3, axiomLevel);
            flowerBalls.renderArrangement(ofVec3f(24, -10, 42), ofVec3f(0, -180, 0), 4, axiomLevel);
            phyllos.renderArrangement(ofVec3f(50, -10, 0), ofVec3f(12, -86, 0), 4, axiomLevel);
            acros.renderArrangement(ofVec3f(-30, -30, 0), ofVec3f(180, 0, 0), 4, axiomLevel);
            break;
        }
        case arrangement_17: {
            lavenders.renderArrangement(ofVec3f(7, -23, 0), ofVec3f(0, 0, -17), 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, -26, 24), ofVec3f(7, -49, -9), 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-13, -33, 0), ofVec3f(13, 40, 9), 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-2, -5, 0), ofVec3f(5, -24, -7), 3, axiomLevel);
            lavenders.renderArrangement(ofVec3f(4, -51, 0), ofVec3f(17, 0, -29), 0, axiomLevel);
            lavenders.renderArrangement(ofVec3f(6, -15, -26), ofVec3f(-2, -96, 0), 1, axiomLevel);
            lavenders.renderArrangement(ofVec3f(-24, -6, -4), ofVec3f(-13, 149, 0), 2, axiomLevel);
            lavenders.renderArrangement(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), 3, axiomLevel);
            alphas.renderArrangement(ofVec3f(0, -51, 0), ofVec3f(0, 0, 0), 4, axiomLevel);
            break;
        }
        case arrangement_18: {
            sigmas.renderArrangement(ofVec3f(0, -53, 0), ofVec3f(0, 29, 0), 0, axiomLevel);
            fans.renderArrangement(ofVec3f(-15, -29, 0), ofVec3f(0, 180, 0), 1, axiomLevel);

            break;
        }
        case arrangement_19: {
            sigmas.renderArrangement(ofVec3f(0, -67, 0), ofVec3f(0, -37, 0), 0, axiomLevel);
            acros.renderArrangement(ofVec3f(0, -60, 0), ofVec3f(29, 90, 180), 1, axiomLevel);
            alphas.renderArrangement(ofVec3f(-22, -79, 0), ofVec3f(-11, 0, 0), 2, axiomLevel);
            break;
        }
        case arrangement_A: {palms.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_S: {lavenders.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_D: {branches.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_F: {flowerBalls.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_G: {phyllos.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_H: {fans.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_J: {acros.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_K: {sigmas.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_L: {alphas.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
        case arrangement_SEMICOLON: {betas.renderArrangement(ofVec3f(0, -70, 0), ofVec3f(0, 0, 0), 0, axiomLevel);break;}
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
        ofVec3f position(-300 + (600 * ofNoise(i * randPos.x)), -300 + (500 * ofNoise(i * randPos.y)), -300 + (600 * ofNoise(i * randPos.z)));
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
            
        case 10: {arrangementNo = arrangement_10;break;}
        case 11: {arrangementNo = arrangement_11;break;}
        case 12: {arrangementNo = arrangement_12;break;}
        case 13: {arrangementNo = arrangement_13;break;}
        case 14: {arrangementNo = arrangement_14;break;}
        case 15: {arrangementNo = arrangement_15;break;}
        case 16: {arrangementNo = arrangement_16;break;}
        case 17: {arrangementNo = arrangement_17;break;}
        case 18: {arrangementNo = arrangement_18;break;}
        case 19: {arrangementNo = arrangement_19;break;}
            
        case 20: {arrangementNo = arrangement_A;break;}
        case 21: {arrangementNo = arrangement_S;break;}
        case 22: {arrangementNo = arrangement_D;break;}
        case 23: {arrangementNo = arrangement_F;break;}
        case 24: {arrangementNo = arrangement_G;break;}
        case 25: {arrangementNo = arrangement_H;break;}
        case 26: {arrangementNo = arrangement_J;break;}
        case 27: {arrangementNo = arrangement_K;break;}
        case 28: {arrangementNo = arrangement_L;break;}
        case 29: {arrangementNo = arrangement_SEMICOLON;break;}
    }
    

}

void ofApp::overwriteCol(){
    
    ofColor palmsBranchCol;
    ofColor palmsPoly1Col;
    ofColor palmsPoly2Col;
    int palmsNum = ofRandom(0,3);
    //NO 2ND COLOUR IN USE
    switch ( palmsNum ) {
        case 0: { palmsBranchCol.set(108, 96, 36); break; }
        case 1: { palmsBranchCol.set(91, 98, 46); break; }
        case 2: { palmsBranchCol.set(100, 106, 88); break; }
    }
    switch ( palmsNum ) {
        case 0: { palmsPoly1Col.set(91, 98, 46); break; }
        case 1: { palmsPoly1Col.set(131, 138, 45); break; }
        case 2: { palmsPoly1Col.set(66, 96, 45); break; }
    }
    palms.overwriteCol(palmsBranchCol, palmsPoly1Col, palmsPoly2Col);
    
    ofColor lavenderBranchCol;
    ofColor lavenderPoly1Col;
    ofColor lavenderPoly2Col;
    int lavenderNum = ofRandom(0,3);
    switch ( lavenderNum ) {
        case 0: { lavenderBranchCol.set(66, 96, 45); break; }
        case 1: { lavenderBranchCol.set(9, 97, 72); break; }
        case 2: { lavenderBranchCol.set(54, 86, 60); break; }
    }
    switch ( lavenderNum ) {
        case 0: { lavenderPoly1Col.set(66, 96, 45); break; }
        case 1: { lavenderPoly1Col.set(9, 97, 72); break; }
        case 2: { lavenderPoly1Col.set(54, 86, 60); break; }
    }
    switch ( lavenderNum ) {
        case 0: { lavenderPoly2Col.set(106, 76, 156); break; }
        case 1: { lavenderPoly2Col.set(171, 59, 58); break; }
        case 2: { lavenderPoly2Col.set(233, 139, 42); break; }
    }
    lavenders.overwriteCol(lavenderBranchCol, lavenderPoly1Col, lavenderPoly2Col);
    
    
    ofColor branchBranchCol;
    ofColor branchPoly1Col;
    ofColor branchPoly2Col;
    int branchNum = ofRandom(0,3);
    switch ( branchNum ) {
        case 0: { branchBranchCol.set(143, 90, 60); break; }
        case 1: { branchBranchCol.set(143, 90, 60); break; }
        case 2: { branchBranchCol.set(143, 90, 60); break; }
    }
    switch ( branchNum ) {
        case 0: { branchPoly1Col.set(255, 196, 8); break; }
        case 1: { branchPoly1Col.set(255, 196, 8); break; }
        case 2: { branchPoly1Col.set(255, 196, 8); break; }
    }
    switch ( branchNum ) {
        case 0: { branchPoly2Col.set(208, 90, 110); break; }
        case 1: { branchPoly2Col.set(102, 50, 124); break; }
        case 2: { branchPoly2Col.set(247, 217, 76); break; }
    }
    branches.overwriteCol(branchBranchCol, branchPoly1Col, branchPoly2Col);
    
    
    ofColor flowerBallBranchCol;
    ofColor flowerBallPoly1Col;
    ofColor flowerBallPoly2Col;
    int flowerBallNum = ofRandom(0,3);
    switch ( flowerBallNum ) {
        case 0: { flowerBallBranchCol.set(66, 96, 45); break; }
        case 1: { flowerBallBranchCol.set(66, 97, 72); break; }
        case 2: { flowerBallBranchCol.set(54, 86, 60); break; }
    }
    switch ( flowerBallNum ) {
        case 0: { flowerBallPoly2Col.set(181, 202, 160); break; }
        case 1: { flowerBallPoly2Col.set(189, 192, 186); break; }
        case 2: { flowerBallPoly2Col.set(247, 217, 76); break; }
    }
    flowerBalls.overwriteCol(flowerBallBranchCol, flowerBallPoly1Col, flowerBallPoly2Col);
    
    
    ofColor phyllotaxisBranchCol;
    ofColor phyllotaxisPoly1Col;
    ofColor phyllotaxisPoly2Col;
    int phyllotaxisNum = ofRandom(0,3);
    switch ( phyllotaxisNum ) {
        case 0: { phyllotaxisBranchCol.set(66, 96, 45); break; }
        case 1: { phyllotaxisBranchCol.set(9, 97, 72); break; }
        case 2: { phyllotaxisBranchCol.set(54, 86, 60); break; }
    }
    switch ( phyllotaxisNum ) {
        case 0: { phyllotaxisPoly1Col.set(66, 96, 45); break; }
        case 1: { phyllotaxisPoly1Col.set(9, 97, 72); break; }
        case 2: { phyllotaxisPoly1Col.set(54, 86, 60); break; }
    }
    switch ( phyllotaxisNum ) {
        case 0: { phyllotaxisPoly2Col.set(251, 153, 102); break; }
        case 1: { phyllotaxisPoly2Col.set(171, 59, 58); break; }
        case 2: { phyllotaxisPoly2Col.set(168, 73, 122); break; }
    }
    phyllos.overwriteCol(phyllotaxisBranchCol, phyllotaxisPoly1Col, phyllotaxisPoly2Col);
    
    
    ofColor fansBranchCol;
    //NO 1ST COLOUR IN USE
    ofColor fansPoly1Col;
    ofColor fansPoly2Col;
    int fansNum = ofRandom(0,3);
    switch ( fansNum ) {
        case 0: { fansBranchCol.set(108, 96, 36); break; }
        case 1: { fansBranchCol.set(91, 98, 46); break; }
        case 2: { fansBranchCol.set(100, 106, 88); break; }
    }
    switch ( fansNum ) {
        case 0: { fansPoly2Col.set(91, 98, 46); break; }
        case 1: { fansPoly2Col.set(131, 138, 45); break; }
        case 2: { fansPoly2Col.set(66, 96, 45); break; }
    }
    fans.overwriteCol(fansBranchCol, fansPoly1Col, fansPoly2Col);
    
    
    ofColor acrosBranchCol;
    ofColor acrosPoly1Col;
    ofColor acrosPoly2Col;
    int acrosNum = ofRandom(0,3);
    switch ( acrosNum ) {
        case 0: { acrosBranchCol.set(143, 90, 60); break; }
        case 1: { acrosBranchCol.set(143, 90, 60); break; }
        case 2: { acrosBranchCol.set(143, 90, 60); break; }
    }
    switch ( acrosNum ) {
        case 0: { acrosPoly1Col.set(215, 84, 85); break; }
        case 1: { acrosPoly1Col.set(34, 125, 81); break; }
        case 2: { acrosPoly1Col.set(152, 109, 178); break; }
    }
    switch ( acrosNum ) {
        case 0: { acrosPoly2Col.set(171, 59, 58); break; }
        case 1: { acrosPoly2Col.set(45, 109, 75); break; }
        case 2: { acrosPoly2Col.set(119, 66, 141); break; }
    }
    acros.overwriteCol(acrosBranchCol, acrosPoly1Col, acrosPoly2Col);
    
    
    ofColor sigmasBranchCol;
    ofColor sigmasPoly1Col;
    ofColor sigmasPoly2Col;
    int sigmasNum = ofRandom(0,3);
    switch ( sigmasNum ) {
        case 0: { sigmasBranchCol.set(54, 86, 60); break; }
        case 1: { sigmasBranchCol.set(81, 110, 65); break; }
        case 2: { sigmasBranchCol.set(54, 86, 60); break; }
    }
    switch ( sigmasNum ) {
        case 0: { sigmasPoly1Col.set(203, 27, 69); break; }
        case 1: { sigmasPoly1Col.set(255, 196, 8); break; }
        case 2: { sigmasPoly1Col.set(235, 122, 119); break; }
    }
    switch ( sigmasNum ) {
        case 0: { sigmasPoly2Col.set(54, 86, 60); break; }
        case 1: { sigmasPoly2Col.set(81, 110, 65); break; }
        case 2: { sigmasPoly2Col.set(54, 86, 60); break; }
    }
    sigmas.overwriteCol(sigmasBranchCol, sigmasPoly1Col, sigmasPoly2Col);
    
    
    ofColor alphasBranchCol;
    ofColor alphasPoly1Col;
    //NO 2ND COLOUR IN USE
    ofColor alphasPoly2Col;
    int alphasNum = ofRandom(0,3);

    switch ( alphasNum ) {
        case 0: { alphasBranchCol.set(143, 90, 60); break; }
        case 1: { alphasBranchCol.set(96, 55, 62); break; }
        case 2: { alphasBranchCol.set(54, 86, 60); break; }
    }
    switch ( alphasNum ) {
        case 0: { alphasPoly1Col.set(208, 90, 110); break; }
        case 1: { alphasPoly1Col.set(208, 90, 110); break; }
        case 2: { alphasPoly1Col.set(119, 66, 141); break; }
    }
    alphas.overwriteCol(alphasBranchCol, alphasPoly1Col, alphasPoly2Col);
    
    
    ofColor betasBranchCol;
    ofColor betasPoly1Col;
    ofColor betasPoly2Col;
    int betasNum = ofRandom(0,3);

    switch ( betasNum ) {
        case 0: { betasBranchCol.set(54, 86, 60); break; }
        case 1: { betasBranchCol.set(81, 110, 65); break; }
        case 2: { betasBranchCol.set(66, 96, 45); break; }
    }
    switch ( betasNum ) {
        case 0: { betasPoly1Col.set(54, 86, 60); break; }
        case 1: { betasPoly1Col.set(81, 110, 65); break; }
        case 2: { betasPoly1Col.set(66, 96, 45); break; }
    }
    switch ( betasNum ) {
        case 0: { betasPoly2Col.set(221, 165, 45); break; }
        case 1: { betasPoly2Col.set(219, 77, 109); break; }
        case 2: { betasPoly2Col.set(251, 150, 110); break; }
    }
    betas.overwriteCol(betasBranchCol, betasPoly1Col, betasPoly2Col);
}
