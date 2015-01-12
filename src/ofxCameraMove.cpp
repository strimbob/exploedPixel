/*  ofxCameraMove.cpp
//  Created by
╔═══════════════════════════════════════════════════════════════╗
║ █████████████████████╗ ██ ███╗   ███ ██████╗ ██████╗██████╗   ║
║ ██╔════╚══██╔══██╔══██ █2 █████╗ ███ ███╔══████╔═══████╔══██╗ ║
║ ███████╗  ██║  ██████╔ ██ ██╔████╔██ ██████╔██║   ████████╔╝  ║
║ ╚════██║  ██║  ██╔══██ ██ ██║╚
 ██╔╝██ ██╔══████║   ████╔══██╗  ║
║ ███████║  ██║  ██║  ██ ██ ██║ ╚═╝ ██ ██████╔╚██████╔██████╔╝  ║
║ ╚══════╝  ╚═╝  ╚═╝  ╚═ ╚═ ╚═╝     ╚═ ╚═════╝ ╚═════╝╚═════╝   ║
╚═══════════════════════════════════════════════════════════════╝
// on 14/08/2013.
*/

#include "ofxCameraMove.h"

//--------------------------------------------------------------
ofxCameraMove::ofxCameraMove(){
    dislayCam = 0;
    active = false;

}

//--------------------------------------------------------------
void ofxCameraMove::setup(ofEasyCam *_cam,string _folder) {
        folder = _folder;
    enableSave();
    cam = _cam;
    getNumberOfCamFormXML(_folder);

    
}


//--------------------------------------------------------------
void  ofxCameraMove::getNumberOfCamFormXML(string _folder){
    
    
    ofDirectory checkDir;
    checkDir.isDirectoryEmpty(_folder);
    
    vector<string> xmlPath = loadString(_folder);

    for(int a = 0;a< xmlPath.size();a++){
        ofQuaternion startQuat;
        ofVec3f startPos;
        ofxXmlSettings XML;
        XML.loadFile(xmlPath[a]);
        
        startPos.set(ofVec3f(XML.getValue("camera:getGlobalPositionX", 0.0),
                             XML.getValue("camera:getGlobalPositionY",0.0),
                             XML.getValue("camera:getGlobalPositionZ",  0.0)));

        float angle =  XML.getValue("camera:angle", 0.0);
        float x =      XML.getValue("camera:x",  0.0);
        float y =      XML.getValue("camera:y",  0.0);
        float z =      XML.getValue("camera:z",  0.0);

        startQuat.makeRotate(angle, x,y,z);
        target.push_back(&camArray[a]);
        target[a]->setGlobalPosition(startPos);
        target[a]->setGlobalOrientation(startQuat);

    }
//    if(xmlPath.size() != 0){
//
//            cutNow(0);
//    }
}
//--------------------------------------------------------------
vector<string> ofxCameraMove::loadString(string _folder){
    
    vector<string> stringTemp;
    ofDirectory dir;
    dir.listDir(_folder);
    dir.sort();
    
    for(int i = 0; i < (int)dir.size(); i++){
        stringTemp.push_back(dir.getPath(i));
        cout << " loading " << dir.getPath(i) << endl;
    }
    
    return stringTemp;
    
}

//--------------------------------------------------------------
void ofxCameraMove::update(){
    Tweener.update();
    if(start != pre){
        float tweenvalue = ofMap (start,0,1,0.,1.,true);
        ofQuaternion tweenedCameraQuaternion;
        tweenedCameraQuaternion.slerp(tweenvalue, startQuat, targetQuat);
        ofVec3f lerpPos;
        lerpPos = startPos + ((targetPos-startPos) * tweenvalue);
        cam->setOrientation(tweenedCameraQuaternion);
        cam->setGlobalPosition(lerpPos);
        pre = start;
    }
    
}

//--------------------------------------------------------------
void ofxCameraMove::tweenNow(int cameraNumber,float time) {

    startPos.set(cam->getGlobalPosition());
    whater = cam->getOrientationQuat() ;
    float angle;
    float xa;
    float ya;
    float za;
    whater.getRotate(angle, xa,ya,za);
    startQuat.makeRotate(angle, xa,ya,za);
    targetPos.set(target[cameraNumber]->getGlobalPosition());
    targetQu = target[cameraNumber]->getOrientationQuat() ;
    
    float angleEnd;
    float x;
    float y;
    float z;
    targetQu.getRotate(angleEnd, x,y,z);
    targetQuat.makeRotate(angleEnd, x,y,z);
    start = 0;
    end = 1;
    if(tweenType == 0){
        
        
    Tweener.addTween(start, end, time,&ofxTransitions::easeOutExpo);
    }
    if(tweenType == 1){
      Tweener.addTween(start, end, time,&ofxTransitions::easeInOutExpo);
        
    }

}
//--------------------------------------------------------------
void ofxCameraMove::cutNow(int cameraNumber){
    if(cameraNumber<target.size()){
    cam->setGlobalOrientation(target[cameraNumber]->getOrientationQuat());
    cam->setGlobalPosition(target[cameraNumber]->getGlobalPosition());
    }
    
} 

//--------------------------------------------------------------
void ofxCameraMove::keyPressed(ofKeyEventArgs &args) {
  cout << " ofxCameraMove keyPressed lisistor is active " << endl;

    if(args.key== OF_KEY_SHIFT){
        shift = true;
    }
    
    
    //if(shift){
    if(args.key =='z'){
        xmlSave(1);
    }
    
    if(args.key =='x'){
        xmlSave(2);
    }
    
    if(args.key =='c'){
        xmlSave(3);
    }
    
    if(args.key =='v'){
        cout << " save 4 " << endl;
        xmlSave(4);
    }
    
    if(args.key == 'Z'){
        drawCamNumber = !drawCamNumber;
    }
    
    if(args.key =='a'){
        
        
        for(int x = 0;x<numberSaveFiles;x++){
            
            cam =  &camArray[x];
            xmlSave(x);
        }
    }
    
    
    if(args.key == OF_KEY_CONTROL){
        
        cutNow(dislayCam);
        dislayCam ++;
        if(dislayCam > target.size()){
            dislayCam = 0;
        }
    }
    
    

  //  }
    
}
//--------------------------------------------------------------
void ofxCameraMove::xmlSave(int cameraNumber){
    ofxXmlSettings XML;
    ofQuaternion startQuat;
    ofQuaternion targetQuat;
    ofVec3f startPos;
    ofVec3f targetPos;
    ofQuaternion whater;
    startPos.set(cam->getGlobalPosition());
    whater = cam->getOrientationQuat() ;
    float angle;float xb;float yb;float zb;
    whater.getRotate(angle, xb,yb,zb);
    startQuat.makeRotate(angle, xb,yb,zb);
    XML.setValue("camera:angle", angle);
    XML.setValue("camera:x",  xb);
    XML.setValue("camera:y",  yb);
    XML.setValue("camera:z",  zb);
    XML.setValue("camera:getGlobalPositionX",  cam->getGlobalPosition().x);
    XML.setValue("camera:getGlobalPositionY",  cam->getGlobalPosition().y);
    XML.setValue("camera:getGlobalPositionZ",  cam->getGlobalPosition().z);
    XML.saveFile(folder+"/camera"+ofToString(cameraNumber)+".xml");
    cout << folder+"/camera"+ofToString(cameraNumber)+".xml" << endl;
}
//--------------------------------------------------------------
void ofxCameraMove::keyReleased(ofKeyEventArgs &args) {
    if(args.key == OF_KEY_SHIFT){
        shift = false;
    }
    
}

//--------------------------------------------------------------
void ofxCameraMove::draw(){
    if(drawCamNumber){
        cout << " drawing" << endl;
        ofPushMatrix();
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ofToString(dislayCam), 400,400);
        ofPopMatrix();
    }
    
}
//--------------------------------------------------------------
void ofxCameraMove::setTweenType(int _tweenType){
    tweenType = _tweenType;
    
    
}
//--------------------------------------------------------------
void ofxCameraMove::enableSave(){
    if(!active){
        
        ofAddListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &ofxCameraMove::keyReleased);
        active = true;
        cout << "save is enable " << active << endl;
    }
    
}
//--------------------------------------------------------------
void ofxCameraMove::disableSave(){
    if(active){
        ofRemoveListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
        ofRemoveListener(ofEvents().keyReleased, this, &ofxCameraMove::keyReleased);
        active = false;
        cout << "save is disable " << active << endl;
    }
}
//--------------------------------------------------------------
ofxCameraMove::~ofxCameraMove(){
    disableSave();
}





