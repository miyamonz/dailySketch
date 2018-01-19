#include "ofApp.h"
#include "ofxQ.h"

#include "Scene.h"

#include "2017-12-11.h"

shared_ptr<SearchScene> mainScene;

struct Kaisou;
using KaisouRef = shared_ptr<Kaisou>;
struct Kaisou {
    using Self = Kaisou;
    vector<KaisouRef> children;
    
public:
    string name = "";
    //add child
    template<typename S, typename... Args>
    KaisouRef add(Args... args) {
        auto scene = make_shared<Kaisou>(args...);
        add(scene);
        return scene;
    }
    void add(KaisouRef scene) {
        children.emplace_back(scene);
    }
    
    template<class Fn, typename... Args>
    void update(Fn fn, Args... args) {
        fn(*this, args...);
        for(auto&& c : children) c->update<Fn,Args...>(fn, args...);
    }
};
class DailyScene : public Scene {
public:
    DailyScene(string _name) {
        name = _name;
    }
    void baseUpdate() override {
        for(auto c : children) c->baseUpdate();
    }
};


KaisouRef a, b;
//--------------------------------------------------------------
void ofApp::setup(){
    mainScene = make_shared<SearchScene>();
    mainScene->setRepeat();
    mainScene->setAutoPlay();
    
    mainScene->add<DailyScene>("1211")->add<Circle>();
    mainScene->add<DailyScene>("1212")->add<Circle>();
    
    mainScene->baseSetup();
    
    a = make_shared<Kaisou>();
    b = make_shared<Kaisou>();
    a->name = "aaa";
    b->name = "bbb";
    a->add(b);
    
    auto fn = [](Kaisou& k, string& str){
        ofLog() << k.name;
        str += k.name;
    };
    string s = "0";
    a->update<decltype(fn), string&>(fn, s);
    ofLog() << "s: " << s;
}

//--------------------------------------------------------------
void ofApp::update(){
    mainScene->baseUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    mainScene->baseDraw();
    
    int y = 0;
    for(auto name : mainScene->getNames()) {
        ofDrawBitmapString(name, 20, ++y * 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        setup();
    }
    if(key == 'x') mainScene->next();
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
