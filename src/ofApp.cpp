#include "ofApp.h"
static ofVec2f getMouse() {
    return ofVec2f(ofGetMouseX(), ofGetMouseY());
}
#include "ofxQ.h"

#include "Scene.h"
#include "2018-01-19.h"
#include "2018-01-20.h"

ofx::ComponentRef root;
shared_ptr<ofx::ComponentSerial> scenes;
shared_ptr<Selector> menu;

vector<string> items;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    auto c = ofGetWindowSize()/2;
    
    root = ofx::Component::createRoot();
    scenes = root->add<ofx::ComponentSerial>();
    scenes->add<S20180119>();
    scenes->add<S20180120>();
    
    items.clear();
    for(auto s : scenes->children) {
        items.push_back(s->name);
    }
    menu = root->add<Selector>(items);
    
    root->setupAll();
    scenes->setIndex(scenes->children.size() - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    root->updateAll();
    menu->idx = scenes->getIndex();
}

//--------------------------------------------------------------
void ofApp::draw(){
    int y = 0;
//    ofDrawBitmapStringHighlight(ofToString(root->time),        0,y+=20);
//    ofDrawBitmapStringHighlight(ofToString(scenes->getCurrent()->name),0,y+=20);
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
    root->mouseDraggedAll(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    root->mousePressedAll(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    root->mouseReleasedAll(x,y,button);
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
