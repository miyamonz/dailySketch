#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"

struct Circle : public Scene {
    float radius;
    Circle(float r = 100) : radius(r), Scene()
    {}
    void draw() override {
        ofDrawCircle(0, 0, radius);
    }
};

SceneRef root;
//--------------------------------------------------------------
void ofApp::setup(){
    root = Scene::createRoot();
    
    auto circle = make_shared<Circle>();
    root->add(circle);
    
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
