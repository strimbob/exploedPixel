#include "ofApp.h"
long  numberPoints = 0;
int startup = 0;
bool donmousething = false;
int mouseX;
//--------------------------------------------------------------
void ofApp::setup(){
    
     ofEnableDepthTest();
        saveCam.setup(&cam,"xml"); // add you ofeasycam and the folder where the xmls are
    saveCam.enableSave();
    ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 50, 50);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	
	shader.setGeometryInputType(GL_LINES);
	shader.setGeometryOutputType(GL_POINT);
	shader.setGeometryOutputCount(24);
	shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");
	
	printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
	
	// create a bunch of random points
    vbo.getVertices().resize(100);
    vbo.getNormals().resize(100,ofVec3f(0));
	float r = ofGetHeight()/2;
	for(int i=0; i<100; i++) {
		points.push_back(ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r));
  //      vbo.setVertex(i ,ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r ));
    //    vbo.setNormal(i ,ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r ));
	}
	
	doShader = true;
	ofEnableDepthTest();
    ///////////
    
    
    //img.loadImage("IMG_0038.JPG");
    
    img.loadImage("IMG_1229.JPG");
    //img.loadImage("TNR_Tree_Down_RT.tif");
    int imgWidth = img.getWidth()-1;
    int imgHeight = img.getHeight()-1;
    int totalSizeImg =  imgWidth * imgHeight;
    
    
    cout << totalSizeImg << " totalSizeImg " << endl;
    
    
	numberPoints = totalSizeImg;
	vbo.getVertices().resize(numberPoints);
	vbo.getColors().resize(numberPoints);
	vbo.getNormals().resize(numberPoints,ofVec3f(0));
    
    int totalNu = 0;
	for(int x =1;x<=imgWidth;x++){
        for(int y = 1;y<=imgHeight;y++){
            //            float xx = ofMap(x, 0, imgWidth, -700, 70);
            //            float yy = ofMap(y, 0, imgHeight, -35, 35);
            float xx = x;
            float yy = y;
            
            vbo.getVertices()[totalNu].set(xx,yy,totalNu); // i the id of billboard
            //cout << x << " " << y << endl;
            vbo.getColors()[totalNu].set(img.getColor(x, y));
            //shaderizeTarget[totalNu] = 1;
            //shader.setNormal(totalNu,ofVec3f(9,0,0));
            totalNu ++;
            
            
        }
        
    }
    
    vbo.setUsage( GL_DYNAMIC_DRAW );
    
    vbo.setMode(OF_PRIMITIVE_LINE_LOOP);
     // saveCam.update();
   // saveCam.cutNow(1);

}

//--------------------------------------------------------------
void ofApp::update(){
    

      saveCam.update();
    

}


//--------------------------------------------------------------
void ofApp::draw(){

    saveCam.draw();
    ofPushMatrix();
    
	if(doShader) {
		shader.begin();
		
		// set thickness of ribbons
		shader.setUniform1f("thickness", 2);
        
     //   if(donmousething ){
           shader.setUniform1f("explodeAmount", mouseX);
        shader.setUniform1f("rotateMount", (float) ofGetMouseY()/100.0);
               mouseX = ofGetMouseX();
            donmousething = false;
            
       // }
		
		// make light direction slowly rotate
		shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/10), cos(ofGetElapsedTimef()/10), 0);
	}
    
	ofColor(255);


//	ofRotateX(mouseY);
//	ofRotateY(mouseX);
    ofEnableDepthTest();
    cam.begin();
    //	ofTranslate(0,0, -10);
//	for(unsigned int i=1; i<points.size(); i++) {
//		ofLine(points[i-1], points[i]);
//	}
	vbo.draw();
    cam.end();
	if(doShader) shader.end();
	
	ofPopMatrix();
	
	ofDrawBitmapString("fps: " + ofToString((int)ofGetFrameRate()) + "\nPress 's' to toggle shader: " + (doShader ? "ON" : "OFF"), 20, 20);
    
    
    if  (startup < 100){
       saveCam.cutNow(1);
        startup ++;
//        saveCam.cutNow(1);
//        saveCam.cutNow(1);
//        startup = !startup;
    }
    
 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 's' ){
		doShader = !doShader;
	}
    if(key == 'b'){
 saveCam.cutNow(1);
    }
    
    if(key == 'm'){
        shader.unload();
        shader.setGeometryInputType(GL_LINES);
        shader.setGeometryOutputType(GL_POINT);
        shader.setGeometryOutputCount(8);
        donmousething = true;
        	shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");
        	printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
    }
    
    if(key == 'p'){
        donmousething = true;
    }
     //
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    donmousething = false;
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}