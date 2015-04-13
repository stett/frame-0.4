#pragma once
#include <string>
#include <cstdio>
#include "frame/Component.h"
#include "frame/Event.h"
using std::string;

struct TriggerEvent : public frame::Event {
    TriggerEvent(string message) : message(message) {}
    string message;
};

class Trigger : public frame::Component {
 public:
    Trigger() {}
    virtual ~Trigger() {}

    void send(string message) {
        auto e = new TriggerEvent(message);
        entity->trigger_event(e);
        delete e;
    }
};
