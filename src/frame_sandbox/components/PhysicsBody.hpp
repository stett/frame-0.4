

#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include "frame/Component.h"
using std::shared_ptr;

class PhysicsBody : public frame::Component {
 private:
    shared_ptr<b2Body> body;

 public:
    PhysicsBody() : body(0) {}
};
