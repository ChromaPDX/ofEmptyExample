#pragma once

#include "ofMain.h"

#if TARGET_OS_IPHONE

#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#import <CoreMotion/CoreMotion.h>
class testApp : public ofxiOSApp{
private:
    CMMotionManager *motionManager;
public:
    void exit();
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
#endif
    
#ifdef TARGET_ANDROID
    
#include "ofxAndroid.h"
    class testApp : public ofxAndroidApp{
    public:
        void updateRotationMatrix(float m00, float m10,float m20,float m30,
                                  float m01,float m11,float m21,float m31,
                                  float m02,float m12,float m22,float m32,
                                  float m03,float m13,float m23, float m33);
        void keyPressed(int key);
        void keyReleased(int key);
        void windowResized(int w, int h);
        void swipe(ofxAndroidSwipeDir swipeDir, int id);
        
        void pause();
        void stop();
        void resume();
        void reloadTextures();
        
        bool backPressed();
        void okPressed();
        void cancelPressed();
        
#endif
        
    public:
        void setup();
        void update();
        void draw();
        
        
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);
        
        // --------------------------
        
        ofMatrix4x4 attitude;
        
        void logSensorOrientation(ofMatrix4x4 attitudeMatrix);
    };
    
    
    static testApp theApp;