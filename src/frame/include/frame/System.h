#pragma once


namespace frame {

    class Frame;
    class Event;


    class System {
        friend class Frame;

    protected:
        Frame* f;

    public:
        System() : f(0) {}
        virtual ~System() {}

    protected:
        virtual void start() {}
        virtual void step_begin() {}
        virtual void step() {}
        virtual void step_end() {}
        virtual void stop() {}
        //virtual void event(Event* e) {}
    };
}
