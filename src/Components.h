#pragma once 

struct Circle : virtual public ofx::Component {
    ofPoint p;
    float radius = 100;
    Circle(ofPoint p) : p(p)
    {}
    Circle(float x,float y) : Circle(ofPoint(x,y))
    {}
    ofColor color;
    void draw() override {
        ofSetColor(color);
        ofDrawCircle(p, radius);
    }
};

struct Viewport : virtual public ofx::Component {
    ofRectangle rect;
    Viewport(ofRectangle rect) : rect(rect)
    {}
    void beforeDraw() {
        ofPushView();
        ofViewport(rect);
        ofSetupScreen();
    }
    void afterDraw() {
        ofPopView();
    }
};

struct ViewportRepeat : public ofx::Component {
    void setup() {
        float w = ofGetWindowWidth();
        float h = ofGetWindowHeight();
        
        int num = 3;
        for(int x=0; x<num; x++) {
            for(int y=0; y<num; y++) {
                auto ww = w/num;
                auto hh = h/num;
                ofRectangle rect(x*ww,y*hh, ww,hh);
//                add<>(rect);
            }
        }
    }
};

struct Repeat : virtual ofx::Component {
    float length;
    int count = 0;
    Repeat(float length = 1) : length(length)
    {}
    void update() {
        if(time > length) {
            time = 0;
            setup();
        }
    }
};

struct Selector : ofx::Component {
    ofPoint pos;
    vector<string> item;
    Selector(vector<string> item) : item(item)
    {}
    
    void beforeDraw() {
        ofPushMatrix();
        ofTranslate(pos);
    }
    void draw() {
        int y = 20;
        for(auto&& s : item)
            ofDrawBitmapStringHighlight(s, 0, y+=20);
    }
    void afterDraw() {
        ofPopMatrix();
    }
};