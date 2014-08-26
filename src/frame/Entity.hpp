// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <set>
#include <map>
#include <memory>
#include "Component.hpp"
#include "FrameInterface.h"
using std::set;
using std::map;
using std::shared_ptr;
using std::type_index;
using std::dynamic_pointer_cast;

namespace frame {

    class Entity {
        friend class Frame;

    protected:
        map<type_index, shared_ptr<Component>> components;
        FrameInterface* f;

    public:
        explicit Entity(FrameInterface* f) : f(f) {}
        ~Entity() {}

    public:
        // add_component<Component>()
        //
        // Add a new component with default constructor settings.
        //
        // TODO(stett):
        // Add an "enable_if" to ensure that T always has the Component
        // base type
        template <typename T>
        shared_ptr<T> add_component() {
            auto c = add_component(new T());
            return dynamic_pointer_cast<T>(c);
        }
        shared_ptr<Component> add_component(Component* c) {
            return f->entity_add_component(this, c);
        }

        // remove_component<Component>()
        //
        // Exactly what it sounds like
        template <typename T>
        void remove_component() {
            f->entity_remove_component(this, type_index(typeid(T)));
        }

        // get_component<Component>()
        //
        // Get a component belonging to the entity with a type of Component
        template <typename T>
        shared_ptr<T> get_component() {
            auto type = type_index(typeid(T));
            auto component_it = components.find(type);
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
