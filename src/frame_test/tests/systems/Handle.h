#pragma once
#include <cstdio>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "frame/Frame.h"
#include "frame/System.h"
#include "frame/Event.h"
#include "../components/Trigger.h"
using frame::Frame;
using frame::System;
using frame::Node;
using frame::Event;
using frame::EventHandler;
using std::string;
using std::type_index;


class Handle : public System, public EventHandler<TriggerEvent> {
 public:
    bool event_handled;
    string message;

 public:
    Handle() : event_handled(0), message("") {}

 protected:
    void start() {
        f->add_event_handler<TriggerEvent>(this);
    }

    /*void event(Event* e) {
        event_handled = true;
        auto a = type_index(typeid(*e));
        int i;
        //message = e->message;
    }*/

    void handle(TriggerEvent* e) {
        event_handled = true;
        auto a = type_index(typeid(*e));
        message = e->message;
    }
};
