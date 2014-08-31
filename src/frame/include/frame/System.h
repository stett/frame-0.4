// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include "frame/interface/FrameInterface.h"


namespace frame {

    class System {
        friend class Frame;

    protected:
        FrameInterface* f;

    public:
        explicit System(FrameInterface* f) : f(f) {}
        virtual ~System() {}

    protected:
        virtual void start() {}
        virtual void step_begin() {}
        virtual void step() {}
        virtual void step_end() {}
        virtual void stop() {}
    };
}
