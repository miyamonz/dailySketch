namespace S20180120 {
    using S20180119::ClickableViewport;
    
    struct CircleRepeat : virtual Circle, virtual Repeat {
        using Circle::Circle;
        void setup() {
            radius = 0;
            length = .51;
        }
        void update() {
            radius++;
            Repeat::update();
        }
    };
    
    struct Sketch : ofx::Component {
        Sketch(){ name = "20180120"; }
        using Cir = CircleRepeat;
        void setup() {
            children.clear();
        }
        void keyPressed(int key) {
            if(key == ' ') {
                //            add<Cir>(getMouse())->setup();
            }
        }
        void draw() {
            if(ofGetMousePressed()) {
                ScopedStyle s(255,100);
                ofDrawRectangle(ofRectangle(downPoint, getMouse()));
            }
        }
        
        ofVec2f downPoint, upPoint;
        void mousePressed(int x, int y, int button) {
            downPoint = ofVec2f(x,y);
        }
        void mouseReleased(int x, int y, int button) {
            upPoint = ofVec2f(x,y);
            ofRectangle rect(downPoint, upPoint);
            auto view = add<ClickableViewport>(rect);
            view->bDrawViewport = true;
            view->hue = ofRandom(1.);
        }
    };
}
