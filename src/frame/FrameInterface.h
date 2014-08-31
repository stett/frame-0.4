// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

namespace frame {

    class Entity;
    class Component;
    class Node;

    class FrameInterface {
    public:
        virtual ~FrameInterface() {}

        // Entity interface
        virtual void remove_entity(Entity* e) = 0;
        virtual void add_component_to_entity(Entity* e, Component* c) = 0;

        // Node interface
        virtual void remove_node(Node* n) = 0;
        virtual void add_components_to_node(Node* n, unsigned int mask) = 0;
        virtual void remove_components_from_node(Node* n, unsigned int mask) = 0;
    };
}
