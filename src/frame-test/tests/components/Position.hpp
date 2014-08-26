#pragma once

#include "frame/Component.hpp"

class Position : public frame::Component {
public:
    Position() {}
    virtual ~Position() {}
    float x;
    float y;
};