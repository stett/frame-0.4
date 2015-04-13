#pragma once
#include <string>
#include <cstdio>
#include "frame/Component.h"
#include "frame/Event.h"
using std::string;

frame::Event<string> the_event;

class Trigger : public frame::Component {
 public:
    Trigger() {}
    virtual ~Trigger() {}

    void trigger(string message) {
        the_event.trigger(message);
    }
};
