#pragma once
#include "frame/Component.h"

class Velocity : public frame::Component {
 public:
    Velocity() : x(0), y(0) {}// mask = 1 << 4; }
    virtual ~Velocity() {}
    float x;
    float y;
};
