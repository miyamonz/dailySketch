namespace S20180122 {
    
    struct Serial : virtual public ofx::ComponentSerial {
        ofPoint p;
        Serial(ofPoint p) : p(p){}
        void setup() {
            add<CircleExpand>(p);
            add<CircleExpand>(p);
        }
    };
    
    struct Sketch : ofx::Component {
        Sketch(){ name = "20180122"; }
        
        void setup() {
            children.clear();
        }
        void keyPressed(int key) {
            add<Serial>(getMouse())->setup();
        }
    };
}