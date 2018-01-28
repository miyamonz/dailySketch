#pragma once
namespace S20180128 {
    struct Node;
    using NodeRef = shared_ptr<Node>;
    struct GrabData {
        bool grabing = false;
        NodeRef node;
        GrabData(){}
        GrabData(NodeRef node) : grabing(true), node(node) {}
    };
    struct Node : enable_shared_from_this<Node>{
        ofPoint position;

        Node(){}
        Node(ofPoint p) : position(p)
        {}
        NodeRef getPtr() { return shared_from_this(); }

        float radius = 20;
        void draw() {
            ofPushStyle();
            ofSetColor( canGrab(getMouse()) ? ofColor::red : 255);
            ofDrawCircle(position, radius);
            ofPopStyle();
        }
        bool canGrab(ofPoint p) {
            return p.distance(position) < radius;
        }
        GrabData grab() {
            if(!canGrab(getMouse())) return;
            return {getPtr()};
        }
    };
    struct Link {
        NodeRef start;
        NodeRef end;
        Link(NodeRef start, NodeRef end) : start(start), end(end){}
        void draw() {
            auto s = start->position;
            auto e = end->position;
            auto vec = e-s;
            s +=  vec.getScaled(start->radius);
            e += -vec.getScaled(end->radius);
            ofDrawArrow(s,e, 10);
        }
    };
    constexpr int num = 10;
    
    vector<NodeRef> nodes;
    vector<Link> links;
    
    struct Sketch : ofxComponent {
        Sketch(){ name = "20180128"; }
        void setup() {
            children.clear();
            nodes.clear();
            links.clear();
            auto c = ofGetWindowSize()/2;
            for(int i=0; i<num; i++) {
                auto p = c + ofVec2f(200, 0).rotate(360.*i/num);
                nodes.emplace_back(make_shared<Node>(p));
            }
        }
        void update() {
        }
        void draw() {
            if(ofGetMousePressed()) {
                ScopedStyle s(255,100);
            }
            
            for(auto& n : nodes) n->draw();
            for(auto& l : links) l.draw();

            if(grab.grabing)
                ofDrawArrow( grab.node->position, getMouse(), 10);
        }
        GrabData grab;
        void mousePressed(int x, int y, int button) {
            for(auto& n : nodes) {
                auto b = n->canGrab(getMouse());
                if(!b) continue;
                grab = n->grab();
                break;
            }
        }
        void mouseReleased(int x, int y, int button) {
            grab.grabing = false;
            GrabData release;
            bool found = false;
            for(auto& n : nodes) {
                auto b = n->canGrab(getMouse());
                if(!b) continue;
                release = n->grab();
                found = true;
                break;
            }
            
            if(found) {
                links.emplace_back(grab.node, release.node);
            };
        }
    };
}
