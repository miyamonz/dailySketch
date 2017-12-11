#pragma once
#include "Scene.h"

using namespace ofxChoreograph;

//grid
class Sketch_20171210 : public Scene {
public:
    Output<ofVec2f> dot;
    float width = 100;
    function<void()> finishFn;
    void setup() {
        timeline->setDefaultRemoveOnFinish(false);
        timeline->apply(&dot)
        .set(ofGetWindowSize()/2)
        .rampTo(ofGetWindowSize()/2, 0.01)
        ;
        
        auto repeatFn = [this]{
            auto& seq = dot.inputPtr()->getSequence();
            auto now = seq.getEndValue();
            auto deg = 90 * (int)ofRandom(4);
            auto next = now + ofVec2f(width,0).rotate(deg);
            seq.then<RampTo>( next, 2, EaseOutQuint() );
            
            if(finishFn != nullptr) finishFn();
        };
        
        timeline->setFinishFn(repeatFn);
    }
    void draw() {
        for(int i = -10; i < 10; i++) {
            ofVec2f c = ofGetWindowSize()/2;
            ofVec2f x( ofGetWidth() , 0);
            ofVec2f y( 0, ofGetHeight());
            ofVec2f dx(i * width, 0);
            ofVec2f dy(0, i * width);
            ofDrawLine(dy + c - x, dy + c + x);
            ofDrawLine(dx + c - y, dx + c + y);
        }
        ofDrawCircle( (ofVec2f)dot, 3);
    }
};