struct Circle_ : public Circle {
    using Circle::Circle;
    void setup() {
        radius = 0;
    }
    void update() {
        if(time >= 1) return;
        radius++;
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

struct S20180120 : ofx::Component {
    using Cir = CircleRepeat;
    S20180120() {
        float w = ofGetWindowWidth();
        float h = ofGetWindowHeight();
        add<Cir>(w/2, h/2);
    }
};