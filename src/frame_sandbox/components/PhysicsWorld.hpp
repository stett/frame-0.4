// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include "frame/Component.h"
using std::shared_ptr;

class PhysicsWorld : public frame::Component {
    friend class Physics;

 protected:
    shared_ptr<b2World> world;
    shared_ptr<b2Body> world_edges;
    shared_ptr<b2Fixture> body_edges[4];

 public:
    PhysicsWorld() : world_edges(0) {
        world = shared_ptr<b2World>(new b2World(b2Vec2(0, 40)));
    }
};







