// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once


namespace frame {

    class Frame;

    class System {
        friend class Frame;

    protected:
        Frame* f;

    public:
        explicit System(Frame* f) : f(f) {}
        virtual ~System() {}

    protected:
        virtual void start() {}
        virtual void step_begin() {}
        virtual void step() {}
        virtual void step_end() {}
        virtual void stop() {}
    };
}
