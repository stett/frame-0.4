// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "components/Position.h"
#include "components/Name.h"
using frame::Frame;
using frame::Entity;
using frame::Component;
using frame::Node;


namespace {

    class FrameTest : public ::testing::Test {
    protected:
        Frame f;
    };

    TEST_F(FrameTest, TestAddEntity) {

        // Create a node which doesn't filter anything and an entity
        // which has no components, and assert that the node contains
        // the entity.
        auto n = f.add_node();
        auto e = f.add_entity();
        EXPECT_EQ(n->size(), (unsigned)1) << "Node should have exactly one entity";
        EXPECT_NE(n->find(e), n->end()) << "Entity with no components not found in node without filters";
    }

    TEST_F(FrameTest, TestAddComponent) {

        // Create an entity and add a Position component to it, and
        // make sure they point to each other after the operation.
        auto e = f.add_entity();
        auto c = e->add_component<Position>();
        EXPECT_EQ(c->get_entity(), e) << "Component entity pointer should be set to the entity we just added it to";
        EXPECT_EQ(e->get_component<Position>(), c) << "Entity's component list should contain the component we just added";
    }

    TEST_F(FrameTest, TestComponentMasks) {
        auto e_0 = f.add_entity();
        auto e_1 = f.add_entity();
        auto c_pos_0 = e_0->add_component<Position>();
        auto c_pos_1 = e_1->add_component<Position>();
        auto c_name_0 = e_0->add_component<Name>();
        auto c_name_1 = e_1->add_component<Name>();
        EXPECT_EQ(c_pos_0->mask(), c_pos_1->mask());
        EXPECT_EQ(c_name_0->mask(), c_name_1->mask());
        EXPECT_NE(c_pos_0->mask(), c_name_0->mask());
    }

    TEST_F(FrameTest, TestNodeLists) {

        // Create some nodes with various components
        auto n00 = f.add_node();
        auto n01 = f.add_node<Position>();

        // Create entities with various combinations of components
        auto e00 = f.add_entity();
        auto e01 = f.add_entity<Position>();
        auto e10 = f.add_entity<Name>();
        auto e11 = f.add_entity<Position, Name>();

        // Create some more nodes with various components
        auto n10 = f.add_node<Name>();
        auto n11 = f.add_node<Position, Name>();

        // Make sure the nodes contain what they should
        EXPECT_EQ(n00->size(), (unsigned)4);
        EXPECT_EQ(n01->size(), (unsigned)2);
        EXPECT_EQ(n10->size(), (unsigned)2);
        EXPECT_EQ(n11->size(), (unsigned)1);
        EXPECT_NE(n00->find(e00), n00->end());
        EXPECT_NE(n01->find(e01), n01->end());
        EXPECT_NE(n01->find(e11), n01->end());
        EXPECT_NE(n10->find(e10), n10->end());
        EXPECT_NE(n10->find(e11), n10->end());
        EXPECT_NE(n11->find(e11), n11->end());
    }
}
