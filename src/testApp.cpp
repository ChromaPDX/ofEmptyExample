#include "testApp.h"


#if TARGET_OS_IPHONE

//--------------------------------------------------------------
void testApp::setup(){
    if (!motionManager) {
        motionManager = [[CMMotionManager alloc] init];
        ofLogNotice("CORE_MOTION") << "INIT CORE MOTION";
    }
    if (motionManager){
        if(motionManager.isDeviceMotionAvailable){
            ofLogNotice("CORE_MOTION") << "MOTION MANAGER IS AVAILABLE";
            motionManager.deviceMotionUpdateInterval = 1.0/45.0;
            [motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:^(CMDeviceMotion *deviceMotion, NSError *error) {
             
             CMRotationMatrix a = deviceMotion.attitude.rotationMatrix;
             attitude = ofMatrix4x4(a.m11, a.m21, a.m31, 0.0f,
                                    a.m12, a.m22, a.m32, 0.0f,
                                    a.m13, a.m23, a.m33, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f);
             //                agent.updateOrientation(attitude, normalized);  // send data to game controller
             logSensorOrientation(attitude);
             }];
        }
    }
    else {
        ofLogError("MOTION NOT AVAILABLE");
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    
}

#endif


void testApp::logSensorOrientation(ofMatrix4x4 attitudeMatrix){
    static int timeIndex;
    timeIndex++;
    if(timeIndex % 30 == 0)
        ofLogNotice("ORIENTATION") <<
        "\n[ " << attitudeMatrix._mat[0].x << " " << attitudeMatrix._mat[1].x << " " << attitudeMatrix._mat[2].x << " ]" <<
        "\n[ " << attitudeMatrix._mat[0].y << " " << attitudeMatrix._mat[1].y << " " << attitudeMatrix._mat[2].y << " ]" <<
        "\n[ " << attitudeMatrix._mat[0].z << " " << attitudeMatrix._mat[1].z << " " << attitudeMatrix._mat[2].z << " ]" <<
        "\n++++++++++++++++++++++++++++++++";
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}


#ifdef TARGET_ANDROID

//--------------------------------------------------------------
void testApp::setup(){
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

//--------------------------------------------------------------
void testApp::pause(){

}

//--------------------------------------------------------------
void testApp::stop(){

}

//--------------------------------------------------------------
void testApp::resume(){

}

//--------------------------------------------------------------
void testApp::reloadTextures(){

}

//--------------------------------------------------------------
bool testApp::backPressed(){
	return false;
}

//--------------------------------------------------------------
void testApp::okPressed(){

}

//--------------------------------------------------------------
void testApp::cancelPressed(){

}

//--------------------------------------------------------------

void testApp::updateRotationMatrix(float m00,float m10,float m20,float m30,
                    			   float m01,float m11,float m21,float m31,
                    			   float m02,float m12,float m22,float m32,
                    			   float m03,float m13,float m23,float m33){

        attitude = ofMatrix4x4(m00, m10, m20, 0.0f,
        					   m01, m11, m21, 0.0f,
        					   m02, m12, m22, 0.0f,
        					   0.0f, 0.0f, 0.0f, 1.0f);
 //       agent.updateOrientation(attitude, normalized);
        logSensorOrientation(attitude);
}

extern "C"{
    void Java_cc_openframeworks_EmptyExample_OFActivity_updateRotationMatrix( JNIEnv*  env, jobject  thiz,
                                                                jfloat m00, jfloat m10, jfloat m20, jfloat m30,
                                                                jfloat m01, jfloat m11, jfloat m21, jfloat m31,
                                                                jfloat m02, jfloat m12, jfloat m22, jfloat m32,
                                                                jfloat m03, jfloat m13, jfloat m23, jfloat m33){

    	 ((testApp*)ofGetAppPtr())->updateRotationMatrix(m00, m10, m20, m30,
                 	 	 	 	 	 	 	 	 	 	 m01, m11, m21, m31,
                 	 	 	 	 	 	 	 	 	 	 m02, m12, m22, m32,
                 	 	 	 	 	 	 	 	 	 	 m03, m13, m23, m33);
    }
}


#endif
