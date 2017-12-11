#pragma once
#include "ofxChoreograph.h"

class Scene;
using SceneRef = shared_ptr<Scene>;

class Scene {
public:
    Scene() {
        timeline = make_shared<ofxChoreograph::Timeline>();
//        timeline->setRemoveOnFinish(false);
    }
    shared_ptr<ofxChoreograph::Timeline> timeline;
    vector<SceneRef> children;
    
    template<typename S, class... Args>
    void add(Args... args) {
        auto scene = make_shared<S>(args...);
        add(scene);
    }
    void add(SceneRef scene) {
        scene->setup();
        scene->timeline->update();
        auto& tl = scene->timeline;
//        tl->setStartTime( 2*timeline->getStartTime() + timeline->time());
        timeline->addShared(tl).removeOnFinish(tl->getRemoveOnFinish());
        children.emplace_back(scene);
    }
    virtual void setup(){};
    virtual void baseUpdate() {
        for(auto& child : children) child->baseUpdate();
        ofRemove(children, [](SceneRef& scene){ return scene->isEnd(); });
        children.shrink_to_fit();
        update();
    }
    virtual void baseDraw() {
        for(auto& child : children) child->baseDraw();
        draw();
    }
    virtual void update(){};
    virtual void draw(){};
    
    bool bEnd = false;
    virtual bool isEnd(){
        if(bEnd) return true;
        return timeline->empty();
    };
    void end() {
        bEnd = true;
    }
};



template<typename S, class... Args>
static SceneRef makeLoopScene(Args... args) {
    auto scene = make_shared<Scene>();
    auto timeline = scene->timeline;
//    timeline->setRemoveOnFinish(false);
    timeline->setDefaultRemoveOnFinish(false);
    timeline->cue([=]{
        scene->template add<S>(args...);
    }, 0);
    timeline->cue([]{}, 1);
    timeline->setFinishFn([=]{
        timeline->resetTime();
    });
    return scene;
}