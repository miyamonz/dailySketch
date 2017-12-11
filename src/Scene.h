#pragma once
class Scene;
using SceneRef = shared_ptr<Scene>;

class Scene {
public:
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
        scene->setup();
        children.emplace_back(scene);
    }
    
    // setup update draw
    virtual void baseSetup() { time = 0; setup(); }
    virtual void setup() {}
    
    virtual void baseUpdate() {
        time += ofGetLastFrameTime();
        for(auto child : children) child->baseUpdate();
        ofRemove(children, [](SceneRef scene){ return scene->isEnd(); });
        children.shrink_to_fit();
        update();
    }
    virtual void baseDraw() {
        for(auto child : children) child->baseDraw();
        draw();
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

using SceneRef = shared_ptr<Scene>;