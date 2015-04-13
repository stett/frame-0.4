#pragma once
#include <cstdio>
#include <typeinfo>
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "frame/Event.h"
#include "components/Trigger.h"
#include "systems/Handle.h"
using frame::Frame;
using frame::Entity;
using frame::Component;
using frame::Node;
using frame::Children;
using frame::Parent;


namespace {

    class EventTest : public ::testing::Test {
    protected:
        Frame f;
    };

    TEST_F(EventTest, SystemHandlesEvents) {
        auto handle = f.add_system<Handle>();
        auto trigger = f.add_entity<Trigger>();
        trigger->get_component<Trigger>()->trigger("killa'");
        EXPECT_EQ(handle->event_handled, true);
        //EXPECT_EQ(handle->message, "killa'");
    }
};
