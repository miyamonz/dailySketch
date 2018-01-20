#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"
#include "2018-01-19.h"
#include "2018-01-20.h"


ofx::ComponentRef root, menu;
shared_ptr<ofx::ComponentSerial> scenes;

vector<string> items;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    auto c = ofGetWindowSize()/2;
    
    root = ofx::Component::createRoot();
    scenes = root->add<ofx::ComponentSerial>();
    scenes->add<S20180119>();
    scenes->add<S20180120>();
    
//    items = {
//        "aaaa",
//        "iii",
//    };
    menu = root->add<Selector>(items);
    
    root->setupAll();
}

//--------------------------------------------------------------
void ofApp::update(){
    root->updateAll();
}

//--------------------------------------------------------------
void ofApp::draw(){
    int y = 0;
    ofDrawBitmapStringHighlight(ofToString(root->time),        0,y+=20);
    ofDrawBitmapStringHighlight(ofToString(scenes->getIndex()),0,y+=20);
    ofSetColor(255);
    root->drawAll();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        setup();
    }
    root->keyPressedAll(key);
    if(key == OF_KEY_RIGHT) scenes->next();
    if(key == OF_KEY_LEFT)  scenes->prev();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
