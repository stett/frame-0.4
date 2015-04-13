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
using std::string;
using std::type_index;


class Handle : public System {
 public:
    bool event_handled;
    string message;

 public:
    Handle() : event_handled(0), message("") {}

 protected:
    void start() {
        the_event.add_listener<Handle>(this, &Handle::handle);
    }

    void handle() {
        event_handled = true;
        //auto a = type_index(typeid(*e));
        //message = e->message;
    }
};
