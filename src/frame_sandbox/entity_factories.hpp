// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.


#pragma once
#include "frame/Frame.h"
#include "frame/Entity.h"
#include "components/Slot.hpp"
using frame::Frame;
using frame::Entity;

Entity* box_entity(Frame* f, Entity* parent = 0, int slot_x = 0, int slot_y = 0) {

    // Create a root metabox
    auto e = f->add_entity<
        Children,
        Slots,
        BoxDoors,
        PhysicsWorld
    >();

    // If parent is set, add necessary extra parameters
    if (parent) {
        e->add_component(new Parent(parent));
        e->add_component(new Slot(slot_x, slot_y));
        e->add_component(new PhysicsBody(
            parent->get_component<PhysicsWorld>));
    }
}
