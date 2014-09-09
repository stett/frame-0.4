// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include "gtest/gtest.h"
#include "frame/Frame.h"
using frame::Frame;


namespace {

    class MetaBoxTest : public ::testing::Test {
    protected:
        Frame f;
    };



    TEST_F(MetaBoxTest, TestDoingSuffTheWayIWantToForMetaBox) {

        // Set up game
        //f.add_system<>();
        //f.add_system<Graphics>();
        //f.add_system<Physics>();

        auto root_box = f.add_entity<
            Children,       // The root box can be a parent of child boxes and other entities
            BoxDoors,       // Box can have doors
            PhysicsWorld,   // Contains a physics world for its children
            Slots           // Contains slots for its children
        >();

        auto sub_box = f.add_entity<
            Parent,         // Any non-root box has to have a parent...
            Children,       // ... but it can still have children...
            BoxDoors,       // ... and doors.
            PhysicsBody,    // A sub box must have a physics body...
            PhysicsWorld,   // ... and a physics world for its children.
            Slot,           // It belongs in a slot of it's parent...
            Slots,          // And it must keep track of its own slots
        >();

        // The following could be contained in a factory or helper function in some system
        /*sub_box.get_component<Parent>().set(root_box);
        sub_box.get_component<PhysicsBody>().set_world(
            root_box->get_component<PhysicsWorld>());*/

        ///
    }
}
