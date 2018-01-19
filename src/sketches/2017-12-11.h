#pragma once
#include "Scene.h"

struct LifeScene : virtual Scene {
    float life;
    float t;
    LifeScene(float t = 1) : life(t), Scene(){}
    void update() override {
        if(time > life) {
            time = life;
            end();
        }
        t = time/life;
    }
};

struct RectScene : virtual Scene {
    ofRectangle rect;
    
    float getWidth() {
        return rect.width;
    }
    float getHeight() {
        return rect.height;
    }
    void beforeUpdate() override {
        rect = ofRectangle(100,100,200,200);
    }
    void beforeDraw() override {
        ofNoFill();
        ofDrawRectangle(rect);
        
        ofPushMatrix();
        ofTranslate(rect.x, rect.y);
        ofScale( rect.width / ofGetWindowWidth(), rect.height / ofGetWindowHeight(), 1);
    }
    void afterDraw() override {
        ofPopMatrix();
    }
};

struct Circle : virtual LifeScene, virtual RectScene {
    ofVboMesh mesh;
    string name = "circle";
    ofVec2f pos;
    float width = 50;
    Circle(ofVec2f pos = ofGetWindowSize()/2) : pos(pos), LifeScene(){}
    
    void setup() override {
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    void update() override {
        LifeScene::update();
        
        mesh.clear();
        
        float inner = width * easeOut(t, 3);
        float outer = width * easeOut(t, 5);
        
        int num = 30;
         for(int i=0; i<=num; i++) {
            mesh.addVertex(pos + ofVec2f(inner, 0).rotate(360. * i / num));
            mesh.addVertex(pos + ofVec2f(outer, 0).rotate(360. * i / num));
        }
    }
    
    void draw() override {
        mesh.draw();
    }
};