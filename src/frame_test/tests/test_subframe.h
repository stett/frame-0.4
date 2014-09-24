// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "components/Name.h"
using std::type_index;
using frame::Frame;


namespace {

    class SubFrameTest : public ::testing::Test {};

    TEST_F(SubFrameTest, TestSubFrameCount) {

        Frame root;
        Frame* f0 = &root;
        auto f1 = f0->add_entity()->add_component<Frame>();
        auto f2 = f0->add_entity()->add_component<Frame>();
        auto f3 = f1->add_entity()->add_component<Frame>();

        auto n0 = f0->add_node<Frame>();
        auto n1 = f1->add_node<Frame>();
        auto n2 = f2->add_node<Frame>();
        auto n3 = f3->add_node<Frame>();

        EXPECT_EQ(n0->size(), (unsigned)2);
        EXPECT_EQ(n1->size(), (unsigned)1);
        EXPECT_EQ(n2->size(), (unsigned)0);
        EXPECT_EQ(n3->size(), (unsigned)0);
    }
}
