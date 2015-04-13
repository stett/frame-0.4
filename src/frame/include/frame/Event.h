#pragma once
#include <list>
#include <memory>
#include "System.h"
using std::list;
using std::shared_ptr;


namespace frame {

    // Abstract event listener base
    struct EventListenerBase {
        virtual void trigger() = 0;
        virtual ~EventListenerBase() {}
    };

    // Event listener type, specific to the listener type
    template <class T_Listener>
    struct EventListener : EventListenerBase {

        // Add a pointer to the listener, and the function which will be listening
        T_Listener* listener;
        void (T_Listener::*listening_func)();

        //
        EventListener(T_Listener* listener, void (T_Listener::*listening_func)())
        : listener(listener), listening_func(listening_func) {}

        // Trigger the listener's listening function
        virtual void trigger() {
            (listener->*listening_func)();
        }
    };

    class Event {

    private:
        // List of event listener pointers
        list<EventListenerBase*> listeners;

    public:
        // On destruction, delete all event listeners
        ~Event() {
            for (auto listener : listeners)
                delete listener;
        };

    public:
        // Add an arbitrarily typed event listener
        template <class T_Listener>
        void add_listener(T_Listener* listener, void (T_Listener::*listening_func)()) {
            auto event_listener = new EventListener<T_Listener>(listener, listening_func);
            listeners.push_back(event_listener);
        }

        // Trigger all functions listening to this event
        void trigger() {
            for (auto listener : listeners)
                listener->trigger();
        }
    };



    /*
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
    */
};
