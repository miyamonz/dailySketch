#include "201801.hpp"

#include "util.h"

#include "Components.h"
#include "20180119.h"
#include "20180120.h"
#include "20180121.h"
#include "20180122.h"
#include "20180127.h"

void add201801(ofxComponentRef scenes) {
    scenes->add<S20180119::Sketch>();
    scenes->add<S20180120::Sketch>();
    scenes->add<S20180121::Sketch>();
    scenes->add<S20180122::Sketch>();
    scenes->add<S20180127::Sketch>();
}
