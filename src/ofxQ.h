#pragma once

class ofxQ {
public:
    
    struct Arg {
        double time;
        bool next;
    };
    
    struct Anim {
        double time;
        std::function<void(Arg&)> func;
        std::function<void(Arg&)> drawFunc;
        bool isEnd;
    };
    
    double time;
    bool isEnd;
    deque<Anim> anims;
    
    void update() {
        Arg arg {time,false};
        update(arg);
        time += ofGetLastFrameTime();
        if(arg.next) isEnd = true;
    }
    void draw() {
        Arg arg {time,false};
        
        //anims
        auto found = find_if(anims.begin(), anims.end(), [](Anim& a){ return !a.isEnd; });
        if(found == anims.end()) {
            isEnd = true;
        }else{
            if(found->drawFunc) found->drawFunc(arg);
        }

        
    }
    
    void update(Arg& arg) {
        serial(arg);
    }
    
    void serial(Arg& arg) {
        auto found = find_if(anims.begin(), anims.end(), [](Anim& a){ return !a.isEnd; });
        if(found == anims.end()) {
            arg.next = true;
            return;
        }
        Arg subArg;
        subArg.time = found->time;
        subArg.next = false;
        if(found->func) found->func(arg);
        if(arg.next) {
            found->isEnd = true;
        }
    }
    
    void add(std::function<void(Arg&)> func) {
        Anim a;
        a.time = 0;
        a.func = func;
        a.drawFunc = nullptr;
        a.isEnd = false;
        anims.push_back(a);
    }
    
    template<class Drawable>
    void add(Drawable drawable) {
        Anim a;
        a.time = 0;
        a.func = nullptr;
        a.drawFunc = [=](Arg arg){
            drawable.draw();
        };
        a.isEnd = false;
        anims.push_back(a);
    }
    
    
    
    
};