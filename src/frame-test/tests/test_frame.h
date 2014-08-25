// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.hpp"
#include "components/Position.hpp"

namespace {

    class FrameTest : public ::testing::Test {
    protected:
        FrameTest() {}
        virtual ~FrameTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        frame::Frame f;
    };

    TEST_F(FrameTest, TestAddComponent) {

        // Create an entity and add a Position component to it
        shared_ptr<frame::Entity> e = f.add_entity();
        ASSERT_NE(e, shared_ptr<frame::Entity>(0));
        shared_ptr<frame::Component> c = e->set_component<Position>();
        ASSERT_NE(c, shared_ptr<frame::Component>(0));

        // Get all entities that have a Position component,
        // and assert that it only contains the one we just made
        frame::EntitySet entities = f.get_entities<Position>();
        ASSERT_EQ(entities.size(), 1);
        ASSERT_EQ(entities.count(e), 1);
        ASSERT_EQ(*entities.begin(), e);

        // Get the entity out of the entity set and ensure that
        // it contains the Position component we added
        ASSERT_EQ(e->get_component<Position>(), c);
    }
}
