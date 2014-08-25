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
        shared_ptr<Entity> e = f.add_entity();
        ASSERT_NE(e, shared_ptr<Entity>(0));
        shared_ptr<Component> c = e->set_component<Position>();
        ASSERT_NE(c, shared_ptr<Component>(0));

        // Ensure that the entity contains the Position component we added
        ASSERT_EQ(e->get_component<Position>(), c);

        // Get all entities that have a Position component,
        // and assert that it only contains the one we just made
        EntitySet entities = f.get_entities<Position>();
        ASSERT_EQ(entities.size(), 1);
        ASSERT_EQ(entities.count(e), 1);
        ASSERT_EQ(*entities.begin(), e);
    }
}
