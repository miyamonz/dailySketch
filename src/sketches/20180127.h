#pragma once


namespace S20180127 {
    
    map<int,int> kumi;

    constexpr int num = 10;
    int current = 0;
    
    struct Sketch : ofxComponent {
        Sketch(){ name = "20180127"; }
        void setup() {
            children.clear();
            setKumi();
        }
        void setKumi() {
            array<int, num> arr;
            for(int i=0; i<num; i++) arr[i] = i;
            int i = num;
            while(i) {
                int m = ofRandom(num);
                int n = arr[--i];
                arr[i] = arr[m];
                arr[m] = n;
            }
            for(int i=0; i<num; i++) kumi[i] = arr[i];
        }

        void keyPressed(int key) {
            if(key == ' ') {
                setKumi();
                time = 0;
            }
        }
        ofRectangle rect;
        void update() {
            rect = ofRectangle(downPoint, upPoint);
            if(time > 1) {
                time -= 1;
                current = kumi[current];
            }

        }
        ofPoint in(int i) {
            return rect.position + ofPoint(rect.width*i/(num-1),0);
        }
        ofPoint out(int i) {
            return in(i) + ofPoint(0, rect.height);
        }
        void draw() {
            if(ofGetMousePressed()) {
                ScopedStyle s(255,100);
                ofDrawRectangle(ofRectangle(downPoint, getMouse()));
            }
            for(int i=0; i<num; i++) {
                ofDrawCircle( in(i), 10);
                ofDrawCircle(out(kumi[i]), 10);
                ofDrawLine(in(i), out(kumi[i]));
            }
            ofSetColor(255,0,0);
            auto t = time;
            auto p = in(current).getInterpolated(out(kumi[current]),t);
            ofDrawCircle(p , 15);
        }
        
        ofVec2f downPoint, upPoint;
        void mousePressed(int x, int y, int button) {
            downPoint = ofVec2f(x,y);
        }
        void mouseReleased(int x, int y, int button) {
            upPoint = ofVec2f(x,y);
        }
    };
}
