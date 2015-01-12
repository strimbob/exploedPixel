//
//  ofxCameraMove.h
//
//
//  Created by strimbob on 14/08/2013.
//
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTweener.h"

#define numberSaveFiles 9 // this is problem want to make is so a can set the array in code can you help!!???




class ofxCameraMove {
	
public:
    ofxCameraMove();
    ~ofxCameraMove();
	void setup(ofEasyCam *_cam,string folder);
    void update();
    void draw();
    void tweenNow(int cameraNumber,float time);
    void cutNow(int cameraNumber);
    void getNumberOfCamFormXML(string folder);
    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args);
    void setTweenType(int _tweenType); // not good how to change???
    vector<string> loadString(string path);
    void disableSave();
    void enableSave();
    
    float start;
  //  double start;
    float end;
    float pre;
private:
    string  folder;
    bool active;
    int tweenType;
    ofEasyCam camArray[numberSaveFiles];
    vector<ofEasyCam *> target;
	ofEasyCam *cam;
    ofVec3f startPos;
    ofQuaternion startQuat;
    ofQuaternion targetQuat;
    ofQuaternion whater;
    ofQuaternion targetQu;
    ofVec3f targetPos;
    int dislayCam;
    bool drawCamNumber;
    bool shift;
    void xmlSave(int cameraNumber);

};

