#pragma once
#include "ofMain.h"

struct ofxComponent;
using ofxComponentRef = shared_ptr<ofxComponent>;

struct ofxComponent : public ofBaseApp {
    string name;
    float time;
    ofxComponent() : time(0)
    {}
    
    static ofxComponentRef createRoot();
    
    ofxComponent* parent = nullptr;
    vector<ofxComponentRef> children;
    
    //add child
    template<typename S = ofxComponent, typename... Args>
    shared_ptr<S> add(Args... args) {
        auto com = make_shared<S>(args...);
        add((ofxComponentRef)com);
        return com;
    }
    void add(ofxComponentRef com) {
        children.emplace_back(com);
        com->parent = this;
    }
    vector<ofxComponentRef> addVec;
    template<typename S = ofxComponent, typename... Args>
    shared_ptr<S> addAfter(Args... args) {
        auto com = make_shared<S>(args...);
        addAfter((ofxComponentRef)com);
        return com;
    }
    void addAfter(ofxComponentRef com) {
        addVec.emplace_back(com);
        com->parent = this;
    }
    
    //kaisou
    template<class Fn, typename... Args>
    void _repeat(Fn fn, Args... args) {
        fn(*this, args...);
        for(auto&& c : children) c->_repeat<Fn,Args...>(fn, args...);
    }
    
    template<class... Args>
    using FP = void(ofxComponent::*)(Args...);
    
    template<class... Args, class FP_ = FP<Args...>>
    void recursiveCall(FP_ ptr, Args... args) {
        auto fn = std::bind(ptr, this, args...);
        fn(args...);
        for(auto&& c : children) c->recursiveCall(ptr, args...);
    }
    
    template<class... Args, class FP_ = FP<Args...>>
    void recursiveCall(array<FP_,2> ptrs, Args... args) {
        auto fn0 = std::bind(ptrs[0], this, args...);
        auto fn1 = std::bind(ptrs[1], this, args...);
        
        fn0(args...);
        for(auto&& c : children) c->recursiveCall(ptrs, args...);
        fn1(args...);
    }
    
    template<class... Args, class FP_ = FP<Args...>>
    void callChildren(FP_ ptr, Args... args) {
        for(auto&& c : children) {
            if(c.get() == nullptr) continue;
            auto fn = std::bind(ptr, c.get(), args...);
            fn(args...);
        }
    }
    virtual void setup() { time = 0; }
    virtual void updateTime() {
        time += ofGetLastFrameTime();
    }
    virtual void removeChild() {
        ofRemove(children, [](ofxComponentRef com){ return com->isDone(); });
        children.shrink_to_fit();
    }
    virtual void setupAll()  {
        setup();
        callChildren(&ofxComponent::setupAll);
    }
    void _moveChild() {
        if(addVec.size() > 0) {
            copy(addVec.begin(), addVec.end(), back_inserter(children));
            addVec.clear();
        }
        
    }
    virtual void updateAll() {
        updateTime();
        update();
        _moveChild();
        removeChild();
        callChildren(&ofxComponent::updateAll);
    }
    
    virtual void beforeDraw() {}
    virtual void afterDraw() {}
    virtual void drawAll() {
        beforeDraw();
        draw();
        callChildren(&ofxComponent::drawAll);
        afterDraw();
    }
    virtual void keyPressedAll(int key) {
        keyPressed(key);
        callChildren(&ofxComponent::keyPressedAll, key);
    }
    virtual void mousePressedAll(int x, int y, int button) {
        mousePressed(x, y, button);
        callChildren(&ofxComponent::mousePressedAll, x, y, button);
    }
    virtual void mouseReleasedAll(int x, int y, int button) {
        mouseReleased(x, y, button);
        callChildren(&ofxComponent::mouseReleasedAll, x, y, button);
    }
    virtual void mouseDraggedAll(int x, int y, int button) {
        mouseDragged(x, y, button);
        callChildren(&ofxComponent::mouseDraggedAll, x, y, button);
    }
    
    bool bDone = false;
    virtual bool isDone() {
        return bDone;
    }
};


struct ofxComponentSerialBase : virtual public ofxComponent {
private:
    int idx = 0;
public:
    ofxComponentRef getCurrent() {
        return children.at(idx);
    }
    
    void updateAll()                            { if(children.size() == 0) return; getCurrent()->updateAll(); }
    void drawAll()                              { if(children.size() == 0) return; getCurrent()->drawAll();   }
    void keyPressed(int key)                    { if(children.size() == 0) return; getCurrent()->keyPressed(key); }
    void mousePressed(int x, int y, int button) { if(children.size() == 0) return; getCurrent()->mousePressed(x, y, button); }
    void mouseDragged(int x, int y, int button) { if(children.size() == 0) return; getCurrent()->mouseDragged(x, y, button); }
    
    void setIndex(int i) {
        idx = ofClamp(i, 0, children.size()-1);
        getCurrent()->setupAll();
    }
    int getIndex() { return idx; }
    void next() { setIndex(idx+1); }
    void prev() { setIndex(idx-1); }
};

struct ofxComponentSerial : virtual public ofxComponentSerialBase {
    void update() {
        auto done = getCurrent()->bDone;
        if(done) {
            if(getIndex() < children.size()-1) next();
            else bDone = true;
        }
    }
    void updateAll() {
        if(children.size() == 0) return;
        update();
        ofxComponentSerialBase::updateAll();
        
    }
};