

#pragma once
#include <typeindex>
#include <typeinfo>
#include <set>
#include "frame/interface/FrameInterface.h"
using std::set;

namespace frame {

    class Frame;
    class Entity;

    class Node {
        friend class Frame;
    public:
        explicit Node(Frame* f) : mask(0), f(f) {}
        virtual ~Node() {}

    protected:
        unsigned int mask;
        set<Entity*> entities;
        Frame* f;

    public:
        Frame* get_frame() { return f; }

        void remove() {
            ((FrameInterface*)f)->remove_node(this);
        }

        template <typename T>
        Node* add_component() {
            ((FrameInterface*)f)->add_components_to_node(this, T().mask());
            return this;
        }

        template <typename T>
        Node* remove_component() {
            ((FrameInterface*)f)->remove_components_from_node(this, T().mask());
            return this;
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
