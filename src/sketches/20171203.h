#pragma once
#include "Scene.h"
#include "20171126.h"

using namespace ofxChoreograph;

//takakukei
class Sketch_20171203 : public Scene {
    ofPoint pos;
    int num;
public:
    Sketch_20171203(ofPoint _pos, int num = 3) :num(num),  pos(_pos), Scene() {}
    Sketch_20171203() : Sketch_20171203(ofGetWindowSize()/2){}
    Sketch_20171203(int num) : Sketch_20171203(ofGetWindowSize()/2, num){}
    
    Output<float> inner, outer;
    ofVboMesh mesh;
    float time = .5;
    float radius = 50;
    
    void setup() {
        timeline->apply<float>(&inner)
        .set(0)
        .rampTo(radius, time, EaseOutQuad());
        
        timeline->apply<float>(&outer)
        .set(0)
        .rampTo(radius, time, EaseOutQuint());
        
        timeline->cue( [this]{
            for(int i=0; i<=num; i++) {
                ofPoint v = pos + ofVec2f(outer,0).rotate(360. * i / num);
                add<Sketch_20171116>(v);
            }
        }, timeline->getEndTime() );
        
        //timeline->setRemoveOnFinish(true);
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    void update() {
        mesh.clear();
        for(int i=0; i<=num; i++) {
            mesh.addVertex( pos + ofVec2f(inner,0).rotate(360. * i / num) );
            mesh.addVertex( pos + ofVec2f(outer,0).rotate(360. * i / num) );
        }
    }
    void draw() {
        mesh.draw();
    }
};