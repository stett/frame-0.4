#pragma once
#include "frame/Frame.h"
#include "frame/Entity.h"
#include "frame/core/Parent.h"
#include "frame/core/Children.h"
#include "components/PhysicsBody.hpp"
#include "components/PhysicsWorld.hpp"
using frame::Frame;
using frame::Entity;
using frame::Parent;
using frame::Children;

/*
Entity* box_entity(Frame* f, Entity* parent = 0, int slot_x = 0, int slot_y = 0) {

    // Create a root metabox
    auto e = f->add_entity<
        //Sprite,
        Children,
        //Slots,
        //BoxDoors,
        PhysicsWorld
    >();

    // If parent is set, add necessary extra parameters
    if (parent) {
        e->add_component<Parent>()->set(parent);
        //e->add_component<Slot>()->set(slot_x, slot_y);
        e->add_component<PhysicsBody>();
    }
}
*/
