#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"
#include "201710.h"
#include "20171126.h"
#include "20171203.h"
#include "20171210.h"

using namespace ofxChoreograph;
using TimelineRef = shared_ptr<Timeline>;
SceneRef mainScene;
shared_ptr<Sketch_20171210> grid;

//--------------------------------------------------------------
void ofApp::setup(){
    mainScene = make_shared<Scene>();
    grid = make_shared<Sketch_20171210>();
    grid->finishFn = [=] {
        ofVec2f pos = (ofVec2f)grid->dot;
        int num = ofRandom(3,10);
        mainScene->add<Sketch_20171203>(pos,num);
//        mainScene->add<Sketch_20171116>(pos);
    };
    mainScene->add(grid);
    mainScene->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    mainScene->timeline->step(ofGetLastFrameTime());
    mainScene->baseUpdate();
    ofLog() << mainScene->children.size();
}


void drawTimeline(TimelineRef tl, ofVec2f pos) {
    ofPushMatrix();
    ofTranslate(pos);
    ofTranslate(tl->getStartTime(), 0);
    ofDrawRectangle(0, 0, tl->getDuration(), 9);
    ofSetColor(255,0,0);
    ofDrawRectangle(tl->getStartTime() + tl->time(), 0, 0.1, 9);
    ofPopMatrix();
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    mainScene->baseDraw();
    
    ofTranslate(ofGetWindowWidth()/2,0);
    ofScale(10,1);
    auto& tl = mainScene->timeline;
    int y = 0;
    ofSetColor(255);
    drawTimeline(tl, ofVec2f(0, 10 * y++));
    for(auto child : mainScene->children) {
        auto& tl = child->timeline;
        ofSetColor(240,255,255);
        drawTimeline(tl, ofVec2f(0, 10 * y++));
        for(auto mago : child->children) {
            auto& tl = mago->timeline;
            ofSetColor(255,230,255);
            drawTimeline(tl, ofVec2f(0, 10 * y++));
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        setup();
    }
    if(key == 'a') {
        int num = ofRandom(3,10);
        ofVec2f pos = grid->dot;
        for(int i=1; i<=3; i++) {
            auto scene = make_shared<Sketch_20171116>(pos, 50*i);
            scene->timeline->setStartTime(i * 1000);
            mainScene->add(scene);
        }
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
