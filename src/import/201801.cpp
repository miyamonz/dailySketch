#include "201801.hpp"

#include "util.h"

#include "Components.h"
#include "2018-01-19.h"
#include "2018-01-20.h"
#include "2018-01-21.h"
#include "2018-01-22.h"

void add201801(ofxComponentRef scenes) {
    scenes->add<S20180119::Sketch>();
    scenes->add<S20180120::Sketch>();
    scenes->add<S20180121::Sketch>();
    scenes->add<S20180122::Sketch>();
}
