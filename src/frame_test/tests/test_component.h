// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Name.h"
#include "systems/Physics.h"
using std::type_index;
using frame::Frame;


namespace {

    class ComponentTest : public ::testing::Test {
    };

    TEST_F(ComponentTest, TestComponentFactories) {

        EXPECT_EQ(frame::Component::component_factories.size(), (unsigned int)5);
        auto type = type_index(typeid(Name));
        auto factory = frame::Component::component_factories[type];
        auto c_0 = factory();
        auto c_1 = new Name();

        EXPECT_EQ(sizeof(*static_cast<Name*>(c_0)), sizeof(*c_1));
        EXPECT_EQ(type, type_index(typeid(*c_0)));
        EXPECT_EQ(c_0->mask(), c_1->mask());

        delete c_0;
        delete c_1;
    }
}
