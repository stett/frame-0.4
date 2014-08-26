// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <set>
#include "FrameInterface.h"
using std::shared_ptr;
using std::set;

namespace frame {
    class Node {
        friend class Frame;
        
    protected:
        set<type_index> components;
        set<shared_ptr<Entity>> entities;
        FrameInterface* f;


        template <typename T>
        // typename enable_if<is_base_of<Component, T>::value, void>::type
        void add_component() {
            f->node_add_component(this, type_index(typeid(T)));
            //components.insert(type_index(typeid(T)));
        }

    public:
        Node(FrameInterface* f) : f(f) {}
        virtual ~Node() {}
    };

    /*
    template <class... T>
    // typename enable_if<are_base_of<Component, T...>::value>::type
    class NodeT : public Node {
    public:
        NodeT() {
            [](...) {}((components.insert(type_index(typeid(T))))...);
        }
    };
    */
}
