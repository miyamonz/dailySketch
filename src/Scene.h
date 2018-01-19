#pragma once
struct Scene;
using SceneRef = shared_ptr<Scene>;

struct Scene : public ofBaseApp {
    string name;
    float time;
    Scene() : time(0)
    {}
    
    static SceneRef createRoot();
    
    Scene* parent = nullptr;
    vector<SceneRef> children;
    
    //add child
    template<typename S = Scene, typename... Args>
    shared_ptr<S> add(Args... args) {
        auto scene = make_shared<S>(args...);
        add((SceneRef)scene);
        return scene;
    }
    void add(SceneRef scene) {
        children.emplace_back(scene);
        scene->parent = this;
    }
    
    //kaisou
    template<class Fn, typename... Args>
    void _repeat(Fn fn, Args... args) {
        fn(*this, args...);
        for(auto&& c : children) c->_repeat<Fn,Args...>(fn, args...);
    }
    
    template<class... Args>
    using FP = void(Scene::*)(Args...);

    template<class... Args, class FP_ = FP<Args...>>
    void repeatMethod(FP_ ptr, Args... args) {
        auto fn = std::bind(ptr, this, args...);
        fn(args...);
        for(auto&& c : children) c->repeatMethod(ptr, args...);
    }
    virtual void setup() { time = 0; }
    virtual void update() {
        time += ofGetLastFrameTime();
    }
    virtual void removeChild() {
        ofRemove(children, [](SceneRef scene){ return scene->isDone(); });
        children.shrink_to_fit();
    }
    virtual void setupAll()  { repeatMethod(&Scene::setup); }
    virtual void updateAll() { repeatMethod(&Scene::update); repeatMethod(&Scene::removeChild); }
    virtual void drawAll()   { repeatMethod(&Scene::draw); }
    
    
    
    virtual void mousePressedAll(int x, int y, int button) { repeatMethod(&Scene::mousePressed, x, y, button); }
    
    bool bDone = false;
    virtual bool isDone() {
        return bDone;
    }
};

SceneRef Scene::createRoot() {
    auto scene = make_shared<Scene>();
    return scene;
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
