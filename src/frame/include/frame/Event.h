#pragma once
#include <list>
#include <memory>
#include "System.h"
using std::list;
using std::shared_ptr;


namespace frame {

    // Abstract event listener base
    template <typename... arg_types>
    struct EventListenerBase {
        virtual void trigger(arg_types... args) = 0;
        virtual ~EventListenerBase() {}
    };

    // Event listener type, specific to the listener type
    template <class T_Listener, typename... arg_types>
    struct EventListener : EventListenerBase<arg_types...> {

        // Add a pointer to the listener, and the function which will be listening
        T_Listener* listener;
        void (T_Listener::*listening_func)(arg_types...);

        //
        EventListener(T_Listener* listener, void (T_Listener::*listening_func)(arg_types...))
        : listener(listener), listening_func(listening_func) {}

        // Trigger the listener's listening function
        virtual void trigger(arg_types... args) {
            (listener->*listening_func)(args...);
        }
    };

    template <typename... arg_types>
    class Event {

    private:
        // List of event listener pointers
        list<EventListenerBase<arg_types...>*> listeners;

    public:
        // On destruction, delete all event listeners
        ~Event() {
            for (auto listener : listeners)
                delete listener;
        };

    public:
        // Add an arbitrarily typed event listener
        template <class T_Listener>
        void add_listener(T_Listener* listener, void (T_Listener::*listening_func)(arg_types...)) {
            auto event_listener = new EventListener<T_Listener, arg_types...>(listener, listening_func);
            listeners.push_back(event_listener);
        }

        // Trigger all functions listening to this event
        void trigger(arg_types... args) {
            for (auto listener : listeners)
                listener->trigger(args...);
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
