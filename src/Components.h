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
struct Square : virtual public ofx::Component {
    ofPoint p;
    float radius = 100;
    Square(ofPoint p) : p(p)
    {}
    Square(float x,float y) : Square(ofPoint(x,y))
    {}
    ofColor color;
    void draw() override {
        ofSetColor(color);
        auto ne = p - ofPoint(radius/2, radius/2);
        ofDrawRectangle(ne, radius, radius);
    }
};
struct Rectangle : virtual public ofx::Component {
    ofRectangle rect;
    Rectangle(ofRectangle rect) : rect(rect)
    {}
    Rectangle(ofVec2f LU, ofVec2f RD) : rect(ofRectangle(LU,RD))
    {}
    
    ofColor color;
    void draw() override {
        ofSetColor(color);
        ofDrawRectangle(rect);
    }
};

struct Viewport : virtual public ofx::Component {
    ofRectangle rect;
    Viewport(ofRectangle rect) : rect(rect)
    {}
    bool bDrawViewport = false;
    void drawViewport() {
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(rect);
        ofPopStyle();
    }
    void beforeDraw() {
        if(bDrawViewport) drawViewport();
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
    int idx = 0;
    int height = 20;
    Selector(vector<string> item) : item(item)
    {}
    
    void beforeDraw() {
        ofPushMatrix();
        ofTranslate(pos);
    }
    void draw() {
        int y = 14;
        for(auto&& s : item) {
            ofDrawBitmapStringHighlight(s, 0, y);
            y+=height;
        }
        ofPushStyle();
        ofSetColor(255,0,0,100);
        // 8 moji * 8 + 4
        ofDrawRectangle(0, idx*height, 68,height);
        ofPopStyle();
    }
    void afterDraw() {
        ofPopMatrix();
    }
};