#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"

struct Circle : public Scene {
    ofPoint p;
    float radius = 100;
    Circle(ofPoint p) : p(p)
    {
    }
    Circle(float x,float y) : Circle(ofPoint(x,y))
    {}
    
    ofColor color = ofRandom(255);
    void draw() override {
        auto e = 1-pow(1-time, 5);
        
        if(e >= 1) {
            e = 1;
            bDone = true;
        }
        auto t = ofMap(e, 0, 1, 0, radius);
        auto r = ofClamp(t, 0, radius);
        
        ofSetColor(color);
        ofDrawCircle(p, r);
//        ofSetColor(0);
//        ofDrawBitmapString(ofToString(time), p);
    }
};

struct Move : public Scene {
    ofPoint pos;
    ofPoint prev, next;
    
    Move(ofPoint p) : pos(p), prev(p), next(p)
    {}
    Move(float x, float y) : Move(ofPoint(x,y))
    {}
    void setup() {
        add<Circle>(next);
        setDirection();
    }
    void setDirection(float w = 100) {
        prev = next;
        auto d = 90 * (int)ofRandom(4);
        next = prev + ofVec2f(w, 0).rotate(d);
    }
    void update() {
        auto t = 1-pow(1-time, 5);
        auto r = ofClamp(t, 0, 1);
        pos = prev.getInterpolated(next, r);
        
        if(t >= 1) {
            add<Circle>(next);
            time = 0;
            setDirection();
        }
    }
    ofColor color = ofRandom(255);
    void draw() {
        ofSetColor(color);
//        ofDrawCircle(pos, 5);
    }
};

struct Viewport : public Scene {
    ofRectangle rect;
    Viewport(ofRectangle rect) : rect(rect)
    {}
    
    void beforeDraw() {
        ofPushStyle();
        ofNoFill();
//        ofSetColor(255);
//        ofDrawRectangle(rect);
        ofPopStyle();
        
        ofPushView();
        ofViewport(rect);
        ofSetupScreen();
    }
    void afterDraw() {
        ofPopView();
    }
    void keyPressed(int key) {
        int x = ofGetMouseX() - rect.x;
        int y = ofGetMouseY() - rect.y;
        if(x < 0 || y< 0 || x > rect.width || y > rect.height) return;
        
        if(key ==' ') {
            add<Move>(x,y);
        }
    }
};


SceneRef root;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    
    root = Scene::createRoot();
    
    auto c = ofGetWindowSize()/2;
    auto w = ofGetWindowWidth();
    auto h = ofGetWindowHeight();
    auto rect = ofRectangle(0,0,w/2, h/2);
    root->add<Viewport>(rect);
    rect.position += ofPoint(w/2,h/2);
    root->add<Viewport>(rect);
    
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
    ofDrawBitmapStringHighlight(ofToString(root->time),            0,y+=20);
    ofDrawBitmapStringHighlight(ofToString(root->children.size()), 0,y+=20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        setup();
    }
    root->keyPressedAll(key);
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
