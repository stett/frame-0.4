// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <Box2D/Box2D.h>
#include "frame/Component.h"

class PhysicsWorld : public frame::Component {
 private:
    shared_ptr<b2World> world;
    shared_ptr<b2Body> world_edges;
    shared_ptr<b2Fixture> body_edges[4];

 public:
    PhysicsWorld() : world(0), world_edges(0) {}
};







