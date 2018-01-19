#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"

struct Circle : public Scene {
    ofPoint p;
    float radius = 100;
    Circle(ofPoint p) : p(p)
    {}
    Circle(float x,float y) : Circle(ofPoint(x,y))
    {}
    
    void draw() override {
        auto e = 1-pow(1-time, 5);
        
        if(e >= 1) {
            e = 1;
            bDone = true;
        }
        auto t = ofMap(e, 0, 1, 0, radius);
        auto r = ofClamp(t, 0, radius);
        ofDrawCircle(p, r);
        ofDrawBitmapString(ofToString(time), p);
    }
};

SceneRef root;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    ofNoFill();
    
    root = Scene::createRoot();
    
    auto c = ofGetWindowSize()/2;
    root->add<Circle>(c);
    
    root->setupAll();
}

//--------------------------------------------------------------
void ofApp::update(){
    root->updateAll();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    root->drawAll();
    int y = 0;
    ofDrawBitmapStringHighlight(ofToString(root->time), 0,y+=20);
    ofDrawBitmapStringHighlight(ofToString(root->children.size()), 0,y+=20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        setup();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    root->add<Circle>(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    root->add<Circle>(x,y);
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
