// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <memory>
#include "gtest/gtest.h"
#include "frame/Signals.hpp"
using std::shared_ptr;
using frame::Signal;
using frame::SignalManager;
using frame::Signals;

namespace {


    class TestSignal : public Signal {
    public:
        explicit TestSignal(char* str_) : str(str_) {}
        char* str;
    };

    class TestSignalHandler : public SignalManager {
        char* str;
        TestSignalHandler() {}
        virtual void handle_signal(shared_ptr<Signal> signal, type_index type) {
            if (type == type_index(typeid(TestSignal))) {
                test_signal = dynamic_pointer_cast<TestSignal>(signal);
                str = test_signal.str;
            }
        }
    };

    class TestSignalDispatcher : public SignalManager {};


    class SignalsTest : public ::testing::Test {
    protected:
        SignalsTest() {}
        virtual ~SigalsTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        auto signals = shared_ptr<Signals>(new Signals());
    };

    TEST_F(SignalsTest, TestDispatchSignal) {
        TestSignalHandler handler;
        handler.set_signals(signals);

        TestSignalDispatcher dispatcher;
        dispatcher.set_signals(signals);

        dispatcher.dispatch<TestSignal>(TestSignal("Poo poo shitty"));

        EXPECT_EQ(handler.str, "Poo poo shitty");
    }
}
