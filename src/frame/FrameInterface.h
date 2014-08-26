// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <memory>
#include <typeindex>
using std::shared_ptr;
using std::type_index;


namespace frame {

    class Entity;
    class Component;
    class Node;

    class FrameInterface {
    public:
        virtual ~FrameInterface() {}

        // Entity interface
        virtual shared_ptr<Component> entity_add_component(Entity* e, Component* c) = 0;
        virtual void entity_remove_component(Entity* e, type_index c_type) = 0;

        // Node interface
        virtual void node_add_component(Node* e, type_index c_type) = 0;
        virtual void node_remove_component(Node* e, type_index c_type) = 0;
    };
}
