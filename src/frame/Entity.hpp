// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <set>
#include <map>
#include <memory>
#include "Component.hpp"
#include "Signals.hpp"
using std::set;
using std::map;
using std::shared_ptr;
using std::type_index;
using std::dynamic_pointer_cast;
using frame::Signal;
using frame::SignalManager;

namespace frame {


    class entity;
    class setcomponentsignal : public signal {
    public:
        setcomponentsignal(entity* e_, type_index c_type_) : e(e_), c_type(c_type_) {}
        setcomponentsignal(shared_ptr<entity> e_, type_index c_type_) : e(e_), c_type(c_type_) {}
        shared_ptr<entity> e;
        type_index c_type;
    };
    class removecomponentsignal : public signal {
    public:
        removecomponentsignal(shared_ptr<entity> e_, type_index c_type_) : e(e_), c_type(c_type_) {}
        shared_ptr<entity> e;
        type_index c_type;
    };


    class Entity : public SignalManager {
    private:
        map<type_index, shared_ptr<Component>> components;

    public:
        Entity();
        ~Entity() {}

    public:
        // set_component<Component>()
        //
        // Add a new component with default constructor settings. Note
        // it is not called "add_component" because each entity may only
        // have one of any type of component.
        //
        // TODO(stett):
        // Add an "enable_if" to ensure that T always has the Component
        // base type
        template <typename T>
        shared_ptr<T> set_component() {
            auto c = shared_ptr<T>(new T());
            auto c_type = type_index(typeid(T));
            components[c_type] = shared_ptr<Component>(c);
            dispatch<SetComponentSignal>(new SetComponentSignal(this, c_type));
            return c;
        }

        // get_component<Component>()
        //
        // Get a component belonging to the entity with a type of Component
        template <typename T>
        shared_ptr<T> get_component() {
            auto component_it = components.find(type_index(typeid(T)));
            if (component_it == components.end()) return 0;
            return dynamic_pointer_cast<T>(component_it->second);
        }

        // [<Component>]
        //
        // Retrieves a pointer to the component of the type inside
        // the brackets, if it exists, belonging to the entity.
        // shared_ptr<Component> operator [] (type_index) {}
    };


    class EntitySet {
        friend class Frame;

    protected:
        set<shared_ptr<Entity>> entities;

    public:
        set<shared_ptr<Entity>>::const_iterator begin() const { return entities.begin(); }
        set<shared_ptr<Entity>>::const_iterator end() const { return entities.end(); }
        set<shared_ptr<Entity>>::size_type size() const { return entities.size(); }
        set<shared_ptr<Entity>>::size_type count(shared_ptr<Entity> e) const { return entities.count(e); }
    };
}
