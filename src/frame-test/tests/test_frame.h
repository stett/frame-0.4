// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.hpp"
#include "components/Position.hpp"
using frame::Frame;
using frame::Entity;
using frame::EntitySet;
using frame::Component;

namespace {

    class FrameTest : public ::testing::Test {
    protected:
        FrameTest() {}
        virtual ~FrameTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        Frame f;
    };

    TEST_F(FrameTest, TestAddComponent) {

        // Create an entity and add a Position component to it
        auto e = f.add_entity();
        ASSERT_NE(e, shared_ptr<Entity>(0));
        auto c = e->add_component<Position>();
        ASSERT_NE(c, shared_ptr<Component>(0));

        // Ensure that the entity contains the Position component we added
        ASSERT_EQ(e->get_component<Position>(), c);

        // Get all entities that have a Position component,
        // and assert that it only contains the one we just made
        int i = 0;
        for (auto e_it : f.get_entities<Position>()) {
            ASSERT_EQ(i++, 1);
            ASSERT_EQ(e_it.second, e);
        }
    }
}
