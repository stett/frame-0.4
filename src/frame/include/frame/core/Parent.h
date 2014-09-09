// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include "frame/Component.h"

namespace frame {
    class Entity;
    class Parent : public Component {
        friend class Children;

    protected:
        Entity* parent;

    public:
        Parent() : parent(0) {}// mask = 1 << 1; }
        ~Parent() { clear(); }

    public:
        Parent* set(Entity* e);
        Parent* clear();
        Entity* get() { return parent; }
        Entity* operator* () { return parent; }
    };
}
