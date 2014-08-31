// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <set>
#include <map>
#include "frame/Component.h"
#include "frame/Node.h"
#include "frame/interface/FrameInterface.h"
using std::set;
using std::map;
using std::type_index;

namespace frame {
    class Entity {
        friend class Frame;

    protected:
        unsigned int mask;
        map<type_index, Component*> components;
        set<Node*> nodes;
        FrameInterface* f;

    public:
        explicit Entity(FrameInterface* f) : mask(0), f(f) {}
        ~Entity() {}

    public:
        void remove() {
            f->remove_entity(this);
        }

        template <typename T>
        T* add_component() {
            return add_component<T>(new T());
        }

        template <typename T>
        T* add_component(T* c) {
            f->add_component_to_entity(this, c);
            return c;
        }

        template <typename T>
        void remove_component() {
            auto c = get_component<T>();
            f->remove_component_from_entity(c);
        }


        template <typename T>
        T* get_component() {
            auto type = type_index(typeid(T));
            auto component_it = components.find(type);
            if (component_it == components.end()) return 0;
            return (T*)(component_it->second);
        }

        template <typename T>
        T* get_or_add_component() {
            auto c = get_component<T>();
            if (c == 0)
                c = add_component<T>();
            return c;
        }
    };
}
