#include "ofApp.h"
#include "util.h"

#include "ofxComponent.h"
#include "Components.h"

#include "201801.hpp"
ofxComponentRef root;
shared_ptr<ofxComponentSerial> scenes;
shared_ptr<Selector> menu;

vector<string> items;


//struct A : enable_shared_from_this<A>{
//    string name;
//    shared_ptr<A> child;
//    
//    A(string name) : name(name) {
//    }
//    
//};
//
//template<class T>
//struct Scoped {
//    static vector<shared_ptr<T>> context;
//    shared_ptr<T> ptr;
//    
//    Scoped(string name) {
//        ofLog() << string(context.size(), '-') << "start " << name;
//        ptr = make_shared<T>(name);
//        if(context.size() > 0) context.back()->child = ptr;
//        context.push_back(ptr);
//    }
//    ~Scoped() {
//        context.pop_back();
//        ofLog() << string(context.size(), '-') << "end " << ptr->name;
//    }
//    shared_ptr<T> operator->() {
//        return ptr;
//    }
//};
//template<class T>
//vector<shared_ptr<T>> Scoped<T>::context;
//--------------------------------------------------------------
void ofApp::setup(){
//    Scoped<A> a("a");
//    {
//        Scoped<A> s("_a");
//        Scoped<A> b("_b");
//    }
//    ofLog() << "after " << a->name;
//    ofLog() << "after " << a->child->name;
    
    ofSetCircleResolution(50);
    auto c = ofGetWindowSize()/2;
    
    root = ofxComponent::createRoot();
    scenes = root->add<ofxComponentSerial>();
    add201801(scenes);
    items.clear();
    for(auto s : scenes->children) {
        items.push_back(s->name);
    }
    menu = root->add<Selector>(items);
    
    root->setupAll();
    scenes->setIndex(scenes->children.size() - 1);
    
    ofSetVerticalSync(true);
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    glitch.setup(&fbo);

}

//--------------------------------------------------------------
void ofApp::update(){
    root->updateAll();
    menu->idx = scenes->getIndex();
    
    fbo.begin();
    ofClear(0,0,0,255);
    root->drawAll();
    ofPushView();
    ofViewport(ofRectangle(0,0,300,200));
    ofSetupScreen();
    ofDrawCircle(0, 0, 100);
    ofPopView();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    int y = 0;
//    ofDrawBitmapStringHighlight(ofToString(root->time),        0,y+=20);
//    ofDrawBitmapStringHighlight(ofToString(scenes->getCurrent()->name),0,y+=20);
    ofSetColor(255);
    
    glitch.generateFx();
    fbo.draw(0,0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    root->keyPressedAll(key);
    if(key == OF_KEY_RETURN) { setup(); }
    if(key == OF_KEY_UP)  scenes->prev();
    if(key == OF_KEY_DOWN) scenes->next();
    
	if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
	if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW			, true);
	if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
	if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
	if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, true);
	if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
	if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, true);
	if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
	if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, true);
	if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, true);

	if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
	if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
	if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
	if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
	if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
	if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
	if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
	if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW			, false);
	if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
	if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
	if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, false);
	if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
	if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, false);
	if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
	if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, false);
	if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, false);

	if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
	if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
	if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
	if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
	if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
	if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
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
