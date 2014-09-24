// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <string>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "components/Position.h"
#include "components/Name.h"
using std::string;
using frame::Frame;
using frame::Entity;
using frame::Component;
using frame::Node;


namespace {

    class SerializationTest : public ::testing::Test {};

    TEST_F(SerializationTest, TestSave) {

        // Create a frame with some basic entities/components and save it
        Frame f_0;
        auto e_0 = f_0.add_entity();
        e_0->add_component(new Name("Entity #1"));
        auto c = e_0->add_component<Position>();
        c->x = 2.0f;
        c->y = 5.0f;
        auto e_1 = f_0.add_entity();
        e_1->add_component(new Name("Entity #2"));
        f_0.save("data");

        // Make a new frame with some nodes, load the data into it,
        // and make assertions
        Frame f_1;
        auto n_0 = f_1.add_node<Name>();
        auto n_1 = f_1.add_node<Name, Position>();
        f_1.load("data");
        EXPECT_EQ((unsigned)2, n_0->size());
        EXPECT_EQ((unsigned)1, n_1->size());
        EXPECT_EQ("Entity #1", (*n_0->begin())->get_component<Name>()->str);
    }

    TEST_F(SerializationTest, TestSaveParentChild) {

        // Create a frame with a famliy tree of entities and save it
        Frame f0;
        auto e0 = f0.add_entity();
        e0->add_component<Name>()->set("A");
        auto e1 = f0.add_entity();
        e1->add_component<Name>()->set("B");
        e1->add_component<Parent>()->set(e0);
        f0.save("data");

        // Load
        Frame f1;
        auto n0 = f1.add_node<Name, Children>();
        auto n1 = f1.add_node<Name, Parent>();
        f1.load("data");
        EXPECT_EQ((unsigned)1, n0->size());
        EXPECT_EQ((unsigned)1, n1->size());
        e0 = *n0->begin();
        e1 = *n1->begin();
        EXPECT_EQ("A", e0->get_component<Name>()->get());
        EXPECT_EQ("B", e1->get_component<Name>()->get());
        EXPECT_EQ(e0, e1->get_component<Parent>()->get());
        EXPECT_EQ(e1, *e0->get_component<Children>()->begin());
    }

    TEST_F(SerializationTest, TestSaveFamily) {

        // Create a frame with a famliy tree of entities and save it
        Frame f0;
        auto e0 = f0.add_entity();
        e0->add_component<Name>()->set("First Gen #1");
        auto e1 = f0.add_entity();
        e1->add_component<Name>()->set("Second Gen #1");
        e1->add_component<Parent>()->set(e0);
        auto e2 = f0.add_entity();
        e2->add_component<Name>()->set("Second Gen #2");
        e2->add_component<Parent>()->set(e0);
        auto e3 = f0.add_entity();
        e3->add_component<Name>()->set("Third Gen #1");
        e3->add_component<Parent>()->set(e1);
        EXPECT_EQ((unsigned)2, e0->get_component<Children>()->size());
        EXPECT_EQ((unsigned)1, e1->get_component<Children>()->size());
        f0.save("data");

        // Load data into a new frame and ensure that the heirarchy is the same
        // (there must be a nicer way to test the heirarchy...)
        Frame f1;
        auto n0 = f1.add_node<Name, Parent>();
        f1.load("data");
        for (auto e : *n0) {
            string name = e->get_component<Name>()->get();
            if (name == "Second Gen #1") {
                auto parent = e->get_component<Parent>()->get();
                ASSERT_NE((Entity*)0, parent) << "Parent is null";
                auto parent_name = parent->get_component<Name>()->get();
                EXPECT_EQ("First Gen #1", parent_name);
            } else if (name == "Second Gen #2") {
                auto parent = e->get_component<Parent>()->get();
                ASSERT_NE((Entity*)0, parent) << "Parent is null";
                auto parent_name = parent->get_component<Name>()->get();
                EXPECT_EQ("First Gen #1", parent_name);
            } else if (name == "Third Gen #1") {
                auto parent = e->get_component<Parent>()->get();
                ASSERT_NE((Entity*)0, parent) << "Parent is null";
                auto parent_name = parent->get_component<Name>()->get();
                EXPECT_EQ("Second Gen #1", parent_name);
            } else {
                ASSERT_EQ(true, false) << "Unexpected component name: \""
                                       << name
                                       << "\"";
            };
        }
    }

    TEST_F(SerializationTest, TestSaveFrameTree) {
        Frame r0;
        Frame* f0 = &r0;

        // Add some named sub-frames to the root frame
        auto e1 = f0->add_entity<Frame, Name>();
        auto f1 = e1->get_component<Frame>();
        e1->get_component<Name>()->set("Sub Frame 1");
        auto e2 = f0->add_entity<Frame, Name>();
        auto f2 = e2->get_component<Frame>();
        e2->get_component<Name>()->set("Sub Frame 2");

        // Add some entities to the frames
        f0->add_entity<Position>()->add_component<Name>()->set("Entity 0.1");
        f1->add_entity<Position>()->add_component<Name>()->set("Entity 1.1");
        f1->add_entity<Position>()->add_component<Name>()->set("Entity 1.2");
        f2->add_entity<Position>()->add_component<Name>()->set("Entity 2.1");

        // Save the root frame, make a new root frame,
        // and load the data into it.
        Frame r1;
        f0 = &r1;
        r0.save("data");
        /*
        r1.load("data");

        // Ensure that the sub-frames exist
        auto n0 = f0->add_node<Frame, Name>();
        EXPECT_EQ((unsigned)2, n0->size());
        e1 = e2 = 0;
        for (auto e : *n0) {
            auto n = e->get_component<Name>()->get();
            if (n == "Sub Frame 1") e1 = e;
            else if (n == "Sub Frame 2") e2 = e;
        }
        ASSERT_NE((Entity*)0, e1) << "Expected to find \"Sub Frame 1\"";
        ASSERT_NE((Entity*)0, e2) << "Expected to find \"Sub Frame 2\"";

        // Ensure that the components exist
        n0 = f0->add_node<Position, Name>();
        auto n1 = e1->get_component<Frame>()->add_node<Position, Name>();
        auto n2 = e2->get_component<Frame>()->add_node<Position, Name>();
        EXPECT_EQ((unsigned)1, n0->size());
        EXPECT_EQ((unsigned)2, n1->size());
        EXPECT_EQ((unsigned)1, n2->size());
        */
    }
}
