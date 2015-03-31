

#pragma once
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "systems/Physics.h"
using frame::Frame;


namespace {

    class SystemTest : public ::testing::Test {
    protected:
        Frame f;
    };

    TEST_F(SystemTest, TestSystemNode) {
        auto e0 = f.add_entity<Position, Velocity>();
        auto e1 = f.add_entity<Position, Velocity>();
        auto e2 = f.add_entity<Velocity>();
        auto e3 = f.add_entity<Position>();
        auto s = f.add_system<Physics>();

        e0->get_component<Velocity>()->x = 10;
        e1->get_component<Position>()->x = 10;
        e1->get_component<Velocity>()->x = -10;

        f.step();

        EXPECT_EQ(10, e0->get_component<Velocity>()->x);
        EXPECT_EQ(10, e0->get_component<Position>()->x);
        EXPECT_EQ(-10, e1->get_component<Velocity>()->x);
        EXPECT_EQ(0, e1->get_component<Position>()->x);
    }
}
