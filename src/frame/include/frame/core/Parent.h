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
        Parent() : parent(0) { mask = 1 << 3; }
        explicit Parent(Entity* parent) {
            mask = 1 << 3;
            set(parent);
        }
        ~Parent() { clear(); }

    public:
        void set(Entity* e);
        void clear();
        Entity* get() { return parent; }
        Entity* operator* () { return parent; }
    };
}
