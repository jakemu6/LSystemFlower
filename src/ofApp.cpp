

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
               
    palms.createSystem(types::palm, 2, maxAxiomLevel);
    lavenders.createSystem(types::lavender, 4, maxAxiomLevel);
    branches.createSystem(types::branch, 1, maxAxiomLevel);

    axiomLevel = 0;
    cam.setDistance(500);
    ofEnableDepthTest();
    
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
        ofPushMatrix();
        ofRotateYDeg(rotation);
        ofBackground(252, 250, 242);
        ofNoFill();

        switch( arrangementNo )
        {
            case arrangement_1: {
                ofVec3f p1(-5,-10, 5);
                ofVec3f a1(45,-20, 30);
                palms.renderArrangement(p1, a1, 1, axiomLevel);
                
                ofVec3f p2(0, 10, -10);
                ofVec3f a2(-15, 180, 10);
                palms.renderArrangement(p2, a2, 0, axiomLevel);
                break;
            }
            case arrangement_2: {
                ofVec3f p1( 20, -40, 0);
                ofVec3f a1( 0, 0, 0);
                lavenders.renderArrangement(p1, a1, 0, axiomLevel);
                
                ofVec3f p2( 0, -20, -20);
                ofVec3f a2( 0, 90, 0);
                lavenders.renderArrangement(p2, a2, 1, axiomLevel);
                
                ofVec3f p3( -20, 10, 0);
                ofVec3f a3( 0, 180, 0);
                lavenders.renderArrangement(p3, a3, 2, axiomLevel);
                
                ofVec3f p4( 0, 30, 20);
                ofVec3f a4( 0, 270, 0);
                lavenders.renderArrangement(p4, a4, 3, axiomLevel);
                break;
            }
            case arrangement_3: {
                ofVec3f p1( 0, 30, 20);
                ofVec3f a1( 0, 270, 0);
                branches.renderArrangement(p1, a1, 0, axiomLevel);
                break;
            }
        }

        ofPopMatrix();
        cam.end();
    }
    render_buffer.end();
    fx << render_buffer;
    ofBackgroundGradient(ofColor(0), ofColor(255), OF_GRADIENT_LINEAR);

    fx.update();

    // Left side with original, right side with shader applied
    if (dev) {
        render_buffer.draw(0, 0, width/2, height);
        fx.draw(width/2, 0, width/2, height);
    } else {
        fx.draw(0, 0, width, height);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch ( key )
    {
        case 49: {
            arrangementNo = arrangement_1;
            break;
        }
        case 50: {
            arrangementNo = arrangement_2;
            break;
        }
        case 51: {
            arrangementNo = arrangement_3;
            break;
        }
    }
//    ofLog() << "axiom - " << axiomLevel << " result : " << resultsList3[0][axiomLevel];
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (sequence == "stepThrough") {
        axiomLevel++;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
