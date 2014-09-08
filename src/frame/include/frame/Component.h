// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <map>
#include <functional>
#include <cstdio>
using std::type_index;
using std::map;
using std::pair;
using std::function;


namespace frame {

    class Entity;

    class Component {
        friend class Frame;
        friend class Node;

    public:
        static unsigned int _mask;
        static map<type_index, function<Component*()>> component_factories;
        static map<type_index, unsigned int> component_masks;
        static function<Component*()> register_component(function<Component*()> factory);
        static Component* make_component(type_index type);
    protected:
        Entity* entity;


    public:
        Component() : entity(0) {}
        virtual ~Component() {}

    public:
        const Entity* get_entity() const { return entity; }
        unsigned int mask() const;
    };
}


#define REGISTER_FRAME_COMPONENT(COMPONENT_TYPE)                \
    function<frame::Component*()> COMPONENT_TYPE ## Prototype = \
    frame::Component::register_component([]() {                 \
        return new COMPONENT_TYPE();                            \
    });
