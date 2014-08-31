// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <map>
using std::map;

namespace frame {

    class Entity;

    class Component {
        friend class Frame;
        friend class Node;

    protected:
        unsigned int mask;
        Entity* entity;

    public:
        Component() : mask(0), entity(0) {}
        virtual ~Component() {}

    public:
        const Entity* get_entity() const {
            return entity;
        }
    };
}
