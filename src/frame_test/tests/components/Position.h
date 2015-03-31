

#pragma once
#include <cstdio>
#include "frame/Component.h"

class Position : public frame::Component {
 public:
    Position() : x(0), y(0) {}
    virtual ~Position() {}
    float x;
    float y;
};
