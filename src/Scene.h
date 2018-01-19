#pragma once
struct Scene;
using SceneRef = shared_ptr<Scene>;

struct Scene {
    string name;
    float time;
    Scene() : time(0)
    {}
    
    static SceneRef createRoot();
    
    SceneRef parent = nullptr;
    vector<SceneRef> children;
    
    //add child
    template<typename S = Scene, typename... Args>
    shared_ptr<S> add(Args... args) {
        auto scene = make_shared<S>(args...);
        add(scene);
        return scene;
    }
    void add(SceneRef scene) {
        children.emplace_back(scene);
    }
    
    //kaisou
    template<class Fn, typename... Args>
    void _repeat(Fn fn, Args... args) {
        fn(*this, args...);
        for(auto&& c : children) c->_repeat<Fn,Args...>(fn, args...);
    }
    
    // setup update draw
    virtual void setup() {
        time = 0;
    }
    virtual void setupAll() {
        auto fn = std::bind(&Scene::setup, this);
        _repeat(fn);
    }
    virtual void update() {
        time += ofGetLastFrameTime();
        for(auto child : children) child->update();
//        ofRemove(children, [](SceneRef scene){ return scene->isEnd(); });
        children.shrink_to_fit();
    }
    virtual void updateAll() {
        auto fn = std::bind(&Scene::update, this);
        _repeat(fn);
    }
    virtual void draw() {}
    virtual void drawAll() {
        auto fn = std::bind(&Scene::draw, this);
        _repeat(fn);
    }
    
};

SceneRef Scene::createRoot() {
    return make_shared<Scene>();
}

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
