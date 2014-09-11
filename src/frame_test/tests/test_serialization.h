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
}
