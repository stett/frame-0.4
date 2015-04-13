#pragma once

namespace frame {

    // Abstract base event structure
    struct Event { virtual ~Event() {} };


    // Abstract event handler interface
    class EventHandlerBase {
     public:
        virtual ~EventHandlerBase() {}
    };

    // Abstract event handler interface template
    template <typename T>
    class EventHandler : public EventHandlerBase {
     public:
        virtual ~EventHandler() {}

     protected:
        virtual void handle(T* e) = 0;
    };
};
