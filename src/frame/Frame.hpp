// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <cstdio>
#include <typeinfo>
#include <set>
#include "frame/Entity.hpp"
#include "frame/Node.hpp"
#include "frame/System.hpp"
#include "frame/FrameInterface.h"
using std::type_index;
using std::set;


namespace frame {

    class Frame : public FrameInterface {
    private:
        set<Entity*> entities;
        set<Node*> nodes;
        set<System*> systems;
        bool running;

    public:
        Frame() : running(true) {}
        ~Frame() {
            clear_entities();
            clear_nodes();
            clear_systems();
        }

    public:
        Entity* add_entity() {
            Entity* e = new Entity(this);
            entities.insert(e);
            ravel(e);
            return e;
        }

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

        Node* add_node() {
            Node* n = new Node(this);
            nodes.insert(n);
            ravel(n);
            return n;
        }

        template <typename... T>
        Node* add_node() {
            Node* n = new Node(this);
            nodes.insert(n);
            [](...) {} ((n->mask |= T().mask)...);
            ravel(n);
            return n;
        }

        template <typename T>
        T* add_system() {
            T* s = new System(this);
            systems.insert(s);
            return s;
        }

        void clear_entities() {
            while (entities.size())
                remove_entity(*entities.begin());
        }

        void clear_nodes() {
            while (nodes.size())
                remove_node(*nodes.begin());
        }

        void clear_systems() {
            while (systems.size())
                remove_system(*systems.begin());
        }

        virtual void remove_entity(Entity* e) {
            for (auto c: e->components)
                delete c.second;
            for (auto n : e->nodes)
                unravel(n, e);
            entities.erase(e);
            delete e;
        }

        virtual void remove_node(Node* n) {
            for (auto e : n->entities)
                unravel(n, e);
            nodes.erase(n);
            delete n;
        }

        virtual void remove_system(System* s) {
            systems.erase(s);
            delete s;
        }

        virtual void add_component_to_entity(Entity* e, Component* c) {
            auto c_type = type_index(typeid(*c));
            c->entity = e;
            e->components[c_type] = c;
            e->mask |= c->mask;
            ravel(e);
        }

        virtual void remove_component_from_entity(Entity* e, Component* c) {
            auto c_type = type_index(typeid(*c));
            e->components.erase(c_type);
            e->mask &= !c->mask;
            unravel(e);
            delete c;
        }

        virtual void add_components_to_node(Node* n, unsigned int mask) {
            n->mask |= mask;
            unravel(n);
        }

        virtual void remove_components_from_node(Node* n, unsigned int mask) {
            n->mask &= !mask;
            ravel(n);
        }

    private:
        // Raveling functions associate nodes with entities based on their masks
        void ravel(Entity* e) {
            for (auto n : nodes)
                if ((n->mask & e->mask) >= n->mask)
                    ravel(n, e);
        }
        void ravel(Node* n) {
            for (auto e : entities)
                if ((n->mask & e->mask) >= n->mask)
                    ravel(n, e);
        }
        void ravel(Node* n, Entity* e) {
            n->entities.insert(e);
            e->nodes.insert(n);
        }

        // Unraveling functions take a specific node or entity and dis-associate
        // them from the entities or nodes with which they no longer match
        void unravel(Entity* e) {
            for (auto n : e->nodes)
                if ((n->mask & e->mask) < n->mask)
                    unravel(n, e);
        }
        void unravel(Node* n) {
            for (auto e : n->entities)
                if ((n->mask & e->mask) < n->mask)
                    unravel(n, e);
        }
        void unravel(Node* n, Entity* e) {
            n->entities.erase(e);
            e->nodes.erase(n);
        }

    public:
        virtual void run() {
            for (auto s : systems) s->start();
            while (running) {
                for (auto s : systems) s->step_begin();
                for (auto s : systems) s->step();
                for (auto s : systems) s->step_end();
            }
            for (auto s : systems)s->stop();
        }

        virtual void stop() {
            running = false;
        }
    };
}
