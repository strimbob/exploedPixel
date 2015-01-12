//
//  ofxLoadVideoImageFolder.h
//  load a folder of images/movs in to vectors
//
//  Created by strimbob on 06/11/2013.
//
//

#pragma once
#include "ofMain.h"

class ofxLoadVideoImageFolder {
	 public:
    
//////////////////////////////////////////////////////////////////////////////////
    
    vector<ofImage> loadImage(string path){
        
        vector<ofImage> tempImage;
        ofDirectory dir;
        dir.listDir(path);
        dir.sort();
        
        for(int i = 0; i < (int)dir.size(); i++){
            tempImage.push_back(ofImage());
            tempImage[i].loadImage(dir.getPath(i));
            
        }
        
        return tempImage;

    }
    
    
//////////////////////////////////////////////////////////////////////////////////
    
    vector<ofVideoPlayer> loadVideo(string path){
        
        vector<ofVideoPlayer> tempVideo;
        ofDirectory dir;
        dir.listDir(path);
        dir.sort();
        
        for(int i = 0; i < (int)dir.size(); i++){
            tempVideo.push_back(ofVideoPlayer());
            tempVideo[i].loadMovie(dir.getPath(i));
            
        }
        
        return tempVideo;
        
    }
//////////////////////////////////////////////////////////////////////////////////    
    vector<string> loadString(string path){
        
        vector<string> stringTemp;
        ofDirectory dir;
        dir.listDir(path);
        dir.sort();
        
        for(int i = 0; i < (int)dir.size(); i++){
            stringTemp.push_back(dir.getPath(i));
            
        }
        
        return stringTemp;
        
    }
    
   
};



