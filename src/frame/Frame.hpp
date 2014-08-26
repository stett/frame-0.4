// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeindex>
#include <memory>
#include <set>
#include "Entity.hpp"
#include "Node.hpp"
#include "FrameInterface.h"
#include "querymap.hpp"
using std::shared_ptr;
using std::set;


namespace frame {

    class Frame : public FrameInterface {
    private:
        querymap<type_index, shared_ptr<Entity>> entities;
        set<Node> nodes;

    public:
        Frame() {}
        ~Frame() {}

    public:
        // add_entity()
        //
        // Creates a new entity and returns a pointer to it
        shared_ptr<Entity> add_entity() {
            auto e = shared_ptr<Entity>(new Entity(this));
            //entities.insert(e);
            //return entities;
            return e;
        }

        // get_entities()
        //
        // Returns an iterator over the entities which own a specific set
        // of component types.
        template <typename... T>
        querymap<type_index, shared_ptr<Entity> >& get_entities() {
            querymap<type_index, shared_ptr<Entity>>::keyset keys;
            [](...) {}((keys.insert(type_index(typeid(T))))...);
            return entities.find(keys);
        }

        // entity_add_component(Entity*, ComponentType)
        //
        // Add a new component of a specific type to an entity
        virtual shared_ptr<Component> entity_add_component(Entity* e, Component* c) {
            auto c_type = type_index(typeid(*c));
            auto c_ptr = shared_ptr<Component>(c);
            e->components[c_type] = c_ptr;
            return c_ptr;
        }

        // entity_remove_component(Entity*, ComponentType)
        //
        //
        virtual void entity_remove_component(Entity* e, type_index c_type) {
            //auto c_it = e->components.find(c_type);
            //if (c_it == e->components.end()) return;
            //e->components.erase(c_it);
        }

        virtual void node_add_component(Node* n, type_index c_type) {
        }

        virtual void node_remove_component(Node* n, type_index c_type) {
        }
    };
}
