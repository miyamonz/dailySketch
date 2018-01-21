namespace S20180121 {
    struct CircleRect : virtual public Circle {
        using Circle::Circle;
        void setup() {
            radius = 0;
        }
        void update() {
            radius += 30 * time;
        }
    };
    
    struct Drag : virtual public ofx::Component {
        using Fn = function<void()>;
        
        bool bDown = false;
        ofPoint downPoint, upPoint;
        
        void down(int x, int y) {
            bDown = true;
            downPoint.set(x,y);
        }
        Fn onUpFn = nullptr;
        void up(int x, int y) {
            bDown = false;
            upPoint.set(x,y);
            
            if(onUpFn) onUpFn();
        }
        void onUp(Fn fn) {
            onUpFn = fn;
        }
        ofRectangle getRect() {
            return ofRectangle(downPoint, upPoint);
        }
        
        void mousePressed (int x, int y, int button) { down(x,y); }
        void mouseReleased(int x, int y, int button) { up(x,y); }
    };
    
    struct Sketch : ofx::Component {
        Sketch(){ name = "20180121"; }
        
        shared_ptr<Drag> drag;
        
        void setup() {
            children.clear();
            drag = add<Drag>();
            drag->onUp([this]{ appendViewport(); });
        }
        void afterDraw() {
            if(drag->bDown) {
                ScopedStyle s(255,100);
                ofDrawRectangle(ofRectangle(drag->downPoint, getMouse()));
            }
        }
        
        int hue = 0;
        void appendViewport() {
            auto rect = drag->getRect();
            
            auto view = addAfter<Viewport>(rect);
            view->bDrawViewport = true;
            auto c = ofVec2f(rect.width, rect.height) /2;
            auto circle = view->addAfter<CircleRect>(c);
            circle->color = ofColor::fromHsb(hue, 100, 255, 200);
            circle->setup();
            
            hue = ofWrap( hue + 100, 0, 255);
        }
    };
}