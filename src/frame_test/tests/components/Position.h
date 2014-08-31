// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include "frame/Component.h"

class Position : public frame::Component {
 public:
    Position() : x(0), y(0) {
        mask = 1;
    }
    virtual ~Position() {}
    float x;
    float y;
};
