#include "ofxComponent_impl.h"


ofxComponentRef ofxComponent::createRoot() {
    auto com = make_shared<ofxComponent>();
    com->name = "root";
    return com;
}