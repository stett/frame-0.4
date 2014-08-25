// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <set>
#include <list>
#include "Entity.hpp"
#include "Node.hpp"
#include "Signals.hpp"
using std::shared_ptr;
using std::set;
using std::list;


namespace frame {

    class Frame {
    private:
        set<shared_ptr<Entity>> entities;
        list<Node> nodes;
        shared_ptr<Signals> signals;

    public:
        Frame() {
            signals = shared_ptr<Signals>(new Signals());
        }

    public:
        // add_entity()
        //
        // Creates a new entity and returns a pointer to it
        shared_ptr<Entity> add_entity() {
            auto e = shared_ptr<Entity>(new Entity());
            e->set_signals(signals);
            entities.insert(e);
            return e;
        }

        // get_entities()
        //
        // Returns all the entities which own a specific set of components
        template <typename... T>
        EntitySet get_entities() {
            return EntitySet();
        }
    };
}
