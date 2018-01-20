#pragma once

namespace ofx {
    
struct Component;
using ComponentRef = shared_ptr<Component>;

struct Component : public ofBaseApp {
    string name;
    float time;
    Component() : time(0)
    {}
    
    static ComponentRef createRoot();
    
    Component* parent = nullptr;
    vector<ComponentRef> children;
    
    //add child
    template<typename S = Component, typename... Args>
    shared_ptr<S> add(Args... args) {
        auto com = make_shared<S>(args...);
        add((ComponentRef)com);
        return com;
    }
    void add(ComponentRef com) {
        children.emplace_back(com);
        com->parent = this;
    }
    
    //kaisou
    template<class Fn, typename... Args>
    void _repeat(Fn fn, Args... args) {
        fn(*this, args...);
        for(auto&& c : children) c->_repeat<Fn,Args...>(fn, args...);
    }
    
    template<class... Args>
    using FP = void(Component::*)(Args...);

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
    
    virtual void setup() { time = 0; }
    virtual void updateTime() {
        time += ofGetLastFrameTime();
    }
    virtual void removeChild() {
        ofRemove(children, [](ComponentRef com){ return com->isDone(); });
        children.shrink_to_fit();
    }
    virtual void setupAll()  {
        setup();
        for(auto&& c : children) c->setupAll();
//        recursiveCall(&Component::setup);
    }
    
    virtual void updateAll() {
        updateTime();
        update();
        removeChild();
        for(auto&& c : children) c->updateAll();
    }
    
    virtual void beforeDraw() {}
    virtual void afterDraw() {}
    virtual void drawAll() {
        beforeDraw();
        draw();
        for(auto&& c : children) c->drawAll();
        afterDraw();
    }
    virtual void keyPressedAll(int key) {
        keyPressed(key);
        for(auto&& c : children) c->keyPressedAll(key);
    }
    virtual void mousePressedAll(int x, int y, int button) {
        mousePressed(x, y, button);
        for(auto&& c : children) c->mousePressedAll(x,y,button);
    }
    virtual void mouseDraggedAll(int x, int y, int button) {
        mouseDragged(x, y, button);
        for(auto&& c : children) c->mouseDraggedAll(x,y,button);
    }
    
    bool bDone = false;
    virtual bool isDone() {
        return bDone;
    }
};

ComponentRef Component::createRoot() {
    auto com = make_shared<Component>();
    com->name = "root";
    return com;
}
    
struct ComponentSerial : virtual public Component {
private:
    int idx = 0;
public:
    ComponentRef getCurrent() {
        return children.at(idx);
    }
    
    void updateAll()                            { getCurrent()->updateAll(); }
    void drawAll()                              { getCurrent()->drawAll();   }
    void keyPressed(int key)                    {
        getCurrent()->keyPressed(key);
    }
    void mousePressed(int x, int y, int button) { getCurrent()->mousePressed(x, y, button); }
    void mouseDragged(int x, int y, int button) { getCurrent()->mouseDragged(x, y, button); }
    
    void setIndex(int i) {
        idx = ofClamp(i, 0, children.size()-1);
        getCurrent()->setupAll();
    }
    int getIndex() { return idx; }
    void next() { setIndex(idx+1); }
    void prev() { setIndex(idx-1); }
};
    
}

#include "Components.h"


//class SerialScene : public Scene {
//public:
//    int idx = 0;
//    SceneRef getCurrent() {
//        return children.at(idx);
//    }
//    void baseUpdate() override {
//        if(idx >= children.size()) return;
//        if(getCurrent()->isEnd()) return;
//        getCurrent()->baseUpdate();
//    }
//    void baseDraw() override {
//        if(idx >= children.size()) return;
//        getCurrent()->baseDraw();
//        
//        if(getCurrent()->isEnd() && bAutoPlay) next();
//            }
//    void checkIdx() {
//        if(idx < children.size()) return;
//        
//        if(bRepeat) {
//            idx = 0;
//            for(auto& c : children) c->baseSetup();
//        }
//        //else end();
//    }
//    void next() {
//        idx++;
//        checkIdx();
//    }
//    bool isEnd() override { return bEnd; }
//    
//    bool bRepeat = false;
//    void setRepeat(bool b = true){ bRepeat = b; }
//    bool bAutoPlay = false;
//    void setAutoPlay(bool b = true) { bAutoPlay = b; }
//};
//
//class SearchScene : public SerialScene {
//public:
//    vector<string> getNames() {
//        vector<string> names;
//        for(auto& c : children) {
//            names.push_back(c->name);
//        }
//        return names;
//    }
//};
//
//static float easeIn(float t, int n) {
//    return pow(t, n);
//}
//static float easeOut(float t, int n) {
//    return 1-pow(1-t, n);
//}
//
//
