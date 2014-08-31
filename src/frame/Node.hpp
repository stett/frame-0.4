// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <set>
#include "frame/FrameInterface.h"
using std::set;

namespace frame {
    class Entity;

    class Node {
        friend class Frame;
    public:
        explicit Node(FrameInterface* f) : mask(0), f(f) {}
        virtual ~Node() {}

    protected:
        unsigned int mask;
        set<Entity*> entities;
        FrameInterface* f;

    public:
        void remove() {
            f->remove_node(this);
        }

        template <typename T>
        void add_component() {
            f->add_components_to_node(this, T().mask);
        }

        template <typename T>
        void remove_component() {
            f->remove_components_from_node(this, T().mask);
        }

        unsigned int size() { return entities.size(); }
        set<Entity*>::iterator find(Entity* e) { return entities.find(e); }
        set<Entity*>::iterator begin() { return entities.begin(); }
        set<Entity*>::iterator end() { return entities.end(); }


        const set<Entity*>& get_entities() const {
            return entities;
        }
    };
}
