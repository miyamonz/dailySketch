#include "ofApp.h"
#include "util.h"

#include "ofxQ.h"

#include "Scene.h"
#include "2018-01-19.h"
#include "2018-01-20.h"
#include "2018-01-21.h"
#include "2018-01-22.h"

ofx::ComponentRef root;
shared_ptr<ofx::ComponentSerial> scenes;
shared_ptr<Selector> menu;

vector<string> items;

struct A : enable_shared_from_this<A>{
    string name;
    shared_ptr<A> child;
    
    A(string name) : name(name) {
    }
    
};

template<class T>
struct Scoped {
    static vector<shared_ptr<T>> context;
    shared_ptr<T> ptr;
    
    Scoped(string name) {
        ofLog() << string(context.size(), '-') << "start " << name;
        ptr = make_shared<T>(name);
        if(context.size() > 0) context.back()->child = ptr;
        context.push_back(ptr);
    }
    ~Scoped() {
        context.pop_back();
        ofLog() << string(context.size(), '-') << "end " << ptr->name;
    }
    shared_ptr<T> operator->() {
        return ptr;
    }
};
template<class T>
vector<shared_ptr<T>> Scoped<T>::context;
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
    
    root = ofx::Component::createRoot();
    scenes = root->add<ofx::ComponentSerial>();
    scenes->add<S20180119::Sketch>();
    scenes->add<S20180120::Sketch>();
    scenes->add<S20180121::Sketch>();
    scenes->add<S20180122::Sketch>();
    
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
    root->keyPressedAll(key);
    if(key == 'r') { setup(); }
    if(key == OF_KEY_UP)  scenes->prev();
    if(key == OF_KEY_DOWN) scenes->next();
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
