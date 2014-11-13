// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <string>
#include <set>
#include <map>
#include <typeinfo>
#include <typeindex>
#include "frame/Entity.h"
#include "frame/Node.h"
#include "frame/System.h"
#include "frame/Singleton.h"
#include "frame/interface/FrameInterface.h"
using std::string;
using std::set;
using std::type_index;


namespace frame {

    class Frame : public FrameInterface {

    private:
        set<Entity*> entities;
        set<Node*> nodes;
        set<System*> systems;
        map<type_index, Singleton*> singletons;
        bool running;

    public:
        Frame() : running(true) {}
        ~Frame() {
            clear_entities();
            clear_nodes();
            clear_systems();
        }

    public:
        Entity* add_entity();
        Node* add_node();
        void clear_entities();
        void clear_nodes();
        void clear_systems();
        void remove_system(System* s);
        void remove_singleton(Singleton* s);

        template <typename... T>
        Entity* add_entity() {
            Entity* e = new Entity(this);
            entities.insert(e);
            // TODO(stett):
            // Do something else, so that it doesn't try to re-ravel for
            // every single component... just need to do that once, really.
            [](...) {} ((e->add_component<T>())...);
            return e;
        }

        template <typename... T>
        Node* add_node() {
            // TODO: Make the node list a map<bitmask, Node*> so that we can avoid
            //       duplicate nodes.
            Node* n = new Node(this);
            nodes.insert(n);
            [](...) {} ((n->mask |= T().mask())...);
            ravel(n);
            return n;
        }

        template <typename T>
        T* add_system() {
            return add_system<T>(new T);
        }

        template <typename T>
        T* add_system(T* s) {
            s->f = this;
            ((System*)s)->start();
            systems.insert(s);
            return s;
        }

        template <typename T>
        T* singleton() {
            auto type = type_index(typeid(T));
            auto it = singletons.find(type);
            if (it == singletons.end())
                singletons[type] = new T();
            return (T*)singletons[type];
        }

    private:
        void ravel(Entity* e);
        void ravel(Node* n);
        void ravel(Node* n, Entity* e);

        void unravel(Entity* e);
        void unravel(Node* n);
        void unravel(Node* n, Entity* e);

    public:
        virtual void remove_entity(Entity* e);
        virtual void add_component_to_entity(Entity* e, Component* c);
        virtual void remove_component_from_entity(Entity* e, Component* c);

        virtual void remove_node(Node* n);
        virtual void add_components_to_node(Node* n, unsigned int mask);
        virtual void remove_components_from_node(Node* n, unsigned int mask);

    public:
        virtual void run();
        virtual void step();
        virtual void stop();
        virtual void save(string tag);
        virtual void load(string tag);
    };
}
