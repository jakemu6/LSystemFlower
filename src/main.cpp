#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//    if(1){
//        ofGLFWWindowSettings mainSetting;
//        mainSetting.setGLVersion(3,2);
//        mainSetting.setSize(1280, 720);
//        mainSetting.setPosition(ofVec2f(0, 0));
//        mainSetting.decorated = true;
//        mainSetting.windowMode = OF_FULLSCREEN;
//        mainSetting.numSamples = 8;
//
//        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSetting);
//        shared_ptr<ofApp> mainApp(new ofApp);
//        ofRunApp(mainWindow, mainApp);
//        ofRunMainLoop();
//    }else{
        ofSetupOpenGL(1280, 720, OF_FULLSCREEN);
        if(!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()){
            ofLogFatalError() << "geometry shaders not supported on this graphics card";
            return 1;
        }
        
        ofRunApp(new ofApp);
//    }
}
