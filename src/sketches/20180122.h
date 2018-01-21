namespace S20180122 {
    using S20180119::CircleExpand;
    
    struct Serial : virtual public ofxComponentSerial {
        ofPoint p;
        Serial(ofPoint p) : p(p){}
        void setup() {
            add<CircleExpand>(p);
            add<CircleExpand>(p);
        }
    };
    
    struct Sketch : ofxComponent {
        Sketch(){ name = "20180122"; }
        
        void setup() {
            children.clear();
        }
        void keyPressed(int key) {
            add<Serial>(getMouse())->setup();
        }
    };
}