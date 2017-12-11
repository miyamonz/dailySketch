#pragma once
#include "Scene.h"

using namespace ofxChoreograph;

//expand circle
class Sketch_20171116 : public Scene {
    ofVboMesh mesh;
public:
    ofPoint pos;
    float radius;
    
    Sketch_20171116(ofPoint _pos)               :  pos(_pos), radius(50),     Scene() {}
    Sketch_20171116(              float radius) :             radius(radius), Scene() {}
    Sketch_20171116(ofPoint _pos, float radius) :  pos(_pos), radius(radius), Scene() {}
    Sketch_20171116() : Sketch_20171116(ofPoint(100), 50){}
    
    Output<ofPoint> circlePos;
    Output<float> outer, inner;
    float time = 0.8;
    void setup() {
        timeline->apply<float>(&inner)
        .set(0)
        .rampTo(radius, time, EaseOutQuad());
        
        timeline->apply<float>(&outer)
        .set(0)
        .rampTo(radius, time, EaseOutQuint());
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    void update() {
        mesh.clear();
        int num = 30;
        for(int i=0; i<=num; i++) {
            mesh.addVertex( pos + ofVec2f(inner,0).rotate(360. * i / num) );
            mesh.addVertex( pos + ofVec2f(outer,0).rotate(360. * i / num) );
        }
    }
    void draw() {
        mesh.draw();
    }
};
