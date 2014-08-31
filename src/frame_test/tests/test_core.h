// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "frame/core/Children.h"
#include "frame/core/Parent.h"
#include "components/Position.h"
#include "components/Name.h"
using frame::Frame;
using frame::Entity;
using frame::Component;
using frame::Node;
using frame::Children;
using frame::Parent;


namespace {

    class CoreTest : public ::testing::Test {
    protected:
        CoreTest() {}
        virtual ~CoreTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        Frame f;
    };

    TEST_F(CoreTest, TestAddChildren) {
        auto e_parent = f.add_entity();
        auto e_child_0 = f.add_entity();
        auto e_child_1 = f.add_entity();
        //auto children = e->add_component(new Children(e_child_0, e_child_1));
        auto children = e_parent->add_component<Children>();
        children->add(e_child_0);
        children->add(e_child_1);
        EXPECT_EQ(children->size(), (unsigned)2) << "The parent's child list should be exactly 2 items long";
        EXPECT_NE(children->find(e_child_0), children->end()) << "The first child we added isn't showing up in the parent's child list";
        EXPECT_NE(children->find(e_child_1), children->end()) << "The second child we added isn't showing up in the parent's child list";
        //Entity* e_child_0_parent = e_child_0->get_component<Parent>()->get()
        //EXPECT_EQ(e_child_0_parent, e_parent) << "The first child we added doesn't point to the parent";
        //EXPECT_EQ(*(e_child_1->get_component<Parent>()), e_parent) << "The second child we added doesn't point to the parent";
    }
}
