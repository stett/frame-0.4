#pragma once
#include <string>
using std::string;


namespace frame {

    class Entity;
    class Component;
    class Node;
    class System;

    class FrameInterface {
    public:
        virtual ~FrameInterface() {}

        // Universal
        virtual void run() = 0;
        virtual void step() = 0;
        virtual void stop() = 0;
        virtual void save(string tag) = 0;
        virtual void load(string tag) = 0;

        // Entity interface
        virtual void remove_entity(Entity* e) = 0;
        virtual void add_component_to_entity(Entity* e, Component* c) = 0;
        virtual void remove_component_from_entity(Entity* e, Component* c) = 0;

        // Node interface
        virtual void remove_node(Node* n) = 0;
        virtual void add_components_to_node(Node* n, unsigned int mask) = 0;
        virtual void remove_components_from_node(Node* n, unsigned int mask) = 0;
    };
}
  