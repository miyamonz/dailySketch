#pragma once
struct Scene;
using SceneRef = shared_ptr<Scene>;

struct Scene {
    string name;
    float time;
    Scene() : time(0)
    {}
    
    using SceneRef = shared_ptr<Scene>;
    vector<SceneRef> children;
    
    //add child
    template<typename S, typename... Args>
    shared_ptr<S> add(Args... args) {
        auto scene = make_shared<S>(args...);
        add(scene);
        return scene;
    }
    void add(SceneRef scene) {
        scene->baseSetup();
        children.emplace_back(scene);
    }
    
    // setup update draw
    virtual void baseSetup() {
        time = 0; bEnd = false;
        for(auto child : children) child->baseSetup();
        setup();
    }
    virtual void setup() {}
    
    virtual void beforeUpdate() {}
    virtual void beforeDraw() {}
    virtual void afterUpdate() {}
    virtual void afterDraw() {}
    
    virtual void baseUpdate() {
        time += ofGetLastFrameTime();
        for(auto child : children) child->baseUpdate();
        ofRemove(children, [](SceneRef scene){ return scene->isEnd(); });
        children.shrink_to_fit();
        
        beforeUpdate();
        update();
        afterUpdate();
    }
    virtual void baseDraw() {
        for(auto child : children) child->baseDraw();
        
        beforeDraw();
        draw();
        afterDraw();
    }
    virtual void update(){};
    virtual void draw(){}
    
    //end
    bool bEnd = false;
    void end() {
        bEnd = true;
    }
    virtual bool isEnd() {
        if(children.size() == 0) return bEnd;
        
        if(bEnd) return true;
        for(auto child : children) {
            if(!child->isEnd()) return false;
        }
        return true;
    }
};


class SerialScene : public Scene {
public:
    int idx = 0;
    SceneRef getCurrent() {
        return children.at(idx);
    }
    void baseUpdate() override {
        if(idx >= children.size()) return;
        if(getCurrent()->isEnd()) return;
        getCurrent()->baseUpdate();
    }
    void baseDraw() override {
        if(idx >= children.size()) return;
        getCurrent()->baseDraw();
        
        if(getCurrent()->isEnd() && bAutoPlay) next();
            }
    void checkIdx() {
        if(idx < children.size()) return;
        
        if(bRepeat) {
            idx = 0;
            for(auto& c : children) c->baseSetup();
        }
        //else end();
    }
    void next() {
        idx++;
        checkIdx();
    }
    bool isEnd() override { return bEnd; }
    
    bool bRepeat = false;
    void setRepeat(bool b = true){ bRepeat = b; }
    bool bAutoPlay = false;
    void setAutoPlay(bool b = true) { bAutoPlay = b; }
};

class SearchScene : public SerialScene {
public:
    vector<string> getNames() {
        vector<string> names;
        for(auto& c : children) {
            names.push_back(c->name);
        }
        return names;
    }
};

static float easeIn(float t, int n) {
    return pow(t, n);
}
static float easeOut(float t, int n) {
    return 1-pow(1-t, n);
}


