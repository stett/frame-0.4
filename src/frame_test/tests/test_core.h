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
        auto children = e_parent->add_component<Children>();
        children->add(e_child_0);
        children->add(e_child_1);
        EXPECT_EQ(children->size(), (unsigned)2) << "The parent's child list should be exactly 2 items long";
        EXPECT_NE(children->find(e_child_0), children->end()) << "The first child we added isn't showing up in the parent's child list";
        EXPECT_NE(children->find(e_child_1), children->end()) << "The second child we added isn't showing up in the parent's child list";
        EXPECT_EQ(e_child_0->get_component<Parent>()->get(), e_parent) << "The first child we added doesn't point to the parent";
        EXPECT_EQ(e_child_1->get_component<Parent>()->get(), e_parent) << "The second child we added doesn't point to the parent";
    }

    TEST_F(CoreTest, TestAddParent) {
        auto e_parent = f.add_entity();
        auto e_child_0 = f.add_entity();
        auto e_child_1 = f.add_entity();
        auto parent_0 = e_child_0->add_component<Parent>()->set(e_parent);
        auto parent_1 = e_child_1->add_component<Parent>()->set(e_parent);
        auto children = e_parent->get_component<Children>();
        ASSERT_NE(children, (Children*)0) << "A Children component should have been added to the parent";
        EXPECT_EQ(children->size(), (unsigned)2) << "The parent's child list should be exactly 2 items long";
        EXPECT_NE(children->find(e_child_0), children->end()) << "The first child we added isn't showing up in the parent's child list";
        EXPECT_NE(children->find(e_child_1), children->end()) << "The second child we added isn't showing up in the parent's child list";
        EXPECT_EQ(e_child_0->get_component<Parent>()->get(), e_parent) << "The first child we added doesn't point to the parent";
        EXPECT_EQ(e_child_1->get_component<Parent>()->get(), e_parent) << "The second child we added doesn't point to the parent";
    }
}
