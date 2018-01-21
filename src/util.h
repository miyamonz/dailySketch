#pragma once
#include "ofMain.h"

static ofVec2f getMouse() {
    return ofVec2f(ofGetMouseX(), ofGetMouseY());
}

class ScopedStyle {
    bool engaged;
public:
    ofColor color;
    ScopedStyle() : engaged(true) {
        ofPushStyle();
    }
    ScopedStyle(ofColor color) : ScopedStyle() {
        ofSetColor(color);
    }
    template<class... Args>
    ScopedStyle(Args... args) : ScopedStyle(ofColor(args...))
    {}
    ~ScopedStyle() {
        ofPopStyle();
    }
};