// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include "frame/Component.h"

class PhysicsBody : public frame::Component {
 private:
    shared_ptr<b2Body> body;

 public:
    PhysicsBody() : body(0) {}
};
