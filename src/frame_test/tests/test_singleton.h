// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include "gtest/gtest.h"
#include "frame/Frame.h"
#include "frame/Singleton.h"
using frame::Frame;
using frame::Singleton;


namespace {

    class SingletonTest : public ::testing::Test {
    protected:
        Frame f;
    };

    struct TestSingleton : public Singleton {
        int param_0;

        TestSingleton() : param_0(10) {}
    };


    TEST_F(SingletonTest, TestDynamicSingletonCreation) {
        EXPECT_EQ(10, f.singleton<TestSingleton>()->param_0);
        f.singleton<TestSingleton>()->param_0 = 20;
        EXPECT_EQ(20, f.singleton<TestSingleton>()->param_0);
    }
}
