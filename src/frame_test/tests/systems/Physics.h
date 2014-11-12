// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include "frame/Frame.h"
#include "frame/System.h"
#include "frame/Node.h"
#include "../components/Position.h"
#include "../components/Velocity.h"
using frame::Frame;
using frame::System;
using frame::Node;

class Physics : public System {
 protected:
    Node* bodies;

 protected:
    void start() {
        bodies = f->add_node<Position, Velocity>();
    }

    void step() {
        for (auto e_body : *bodies) {
            auto c_position = e_body->get_component<Position>();
            auto c_velocity = e_body->get_component<Velocity>();
            c_position->x += c_velocity->x;
            c_position->y += c_velocity->y;
        }
    }

    void stop() {
        bodies->remove();
    }
};
