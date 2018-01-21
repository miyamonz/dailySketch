#pragma once
namespace S20180119 {
    struct CircleExpand : virtual public Circle {
        using Circle::Circle;
        
        void draw() override {
            auto e = 1-pow(1-time, 5);
            if(e >= 1) {
                e = 1;
                bDone = true;
            }
            auto t = ofMap(e, 0, 1, 0, radius);
            auto r = ofClamp(t, 0, radius);
            
            ofSetColor(color);
            ofDrawCircle(p, r);
        }
    };
    
    struct Move : public ofxComponent {
        ofPoint pos;
        ofPoint prev, next;
        
        Move(ofPoint p) : pos(p), prev(p), next(p)
        {}
        Move(float x, float y) : Move(ofPoint(x,y))
        {}
        ofColor color;
        void setup() {
            auto c = add<CircleExpand>(next);
            c->color = color += ofRandom(-50,50);
            c->setup();
            
            setDirection();
            ofSetColor(color);
        }
        void setDirection(float w = 100) {
            prev = next;
            auto d = 90 * (int)ofWrap(ofGetElapsedTimef()*100.124, 0, 4);
            next = prev + ofVec2f(w, 0).rotate(d);
        }
        void update() {
            auto t = 1-pow(1-time, 5);
            auto r = ofClamp(t, 0, 1);
            pos = prev.getInterpolated(next, r);
            
            if(t >= 1) {
                time = 0;
                setup();
            }
        }
    };
    
    struct ClickableViewport : public Viewport {
        using Viewport::Viewport;
        float hue;
        void keyPressed(int key) {
            ofPoint mouse(ofGetMouseX(), ofGetMouseY());
            
            if(key ==' ') {
                auto mo = make_shared<Move>(mouse - rect.position);
                mo->color = ofColor::fromHsb(hue * 255,100,255);
                mo->setup();
                add((ofxComponentRef)mo);
            }
        }
    };
    
    struct Sketch : ofxComponent {
        Sketch(){ name = "20180119"; }
        virtual void setup() {
            children.clear();
            float w = ofGetWindowWidth();
            float h = ofGetWindowHeight();
            
            int num = 3;
            for(int x=0; x<num; x++) {
                for(int y=0; y<num; y++) {
                    auto ww = w/num;
                    auto hh = h/num;
                    ofRectangle rect(x*ww,y*hh, ww,hh);
                    auto view = add<ClickableViewport>(rect);
                    view->hue = float(x+num*y)/num/num;
                }
            }
            
        }
    };
}