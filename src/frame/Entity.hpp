// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <set>
#include <map>
#include <memory>
#include "Component.hpp"
using std::set;
using std::map;
using std::shared_ptr;
using std::type_index;
using std::dynamic_pointer_cast;

namespace frame {

    class Entity {
    private:
        map<type_index, shared_ptr<Component>> components;

    public:
        Entity() {}
        virtual ~Entity() {}

    public:
        // set_component<Component>()
        //
        // Add a new component with default constructor settings. Note
        // it is not called "add_component" because each entity may only
        // have one of any type of component.
        template <typename T>
        // typename enable_if<is_base_of<Component, T>::value, shared_ptr<T>::type
        shared_ptr<T> set_component() {
            //return dynamic_pointer_cast<T>(set_component(new T()));
            auto c = shared_ptr<Component>(new T());
            components[type_index(typeid(T))] = c;
            return dynamic_pointer_cast<T>(c);
        }

        // set_component(Component*)
        //
        // Add a new component via the new statement, specifying
        // constructor arguments. Should be called like so:
        // add_component(new Component(...))
        /*shared_ptr<Component> set_component(Component* c) {
            auto c_ptr = shared_ptr<Component>(c);
            auto c_type = type_index(typeid(c_ptr));
            components[c_type] = c_ptr;
            return c_ptr;
        }*/

        // get_component<Component>()
        //
        // Get a component belonging to the entity with a type of Component
        template <typename T>
        // typename enable_if<is_base_of<Component, T>::value, shared_ptr<T>::type
        shared_ptr<T> get_component() {
            return 0;
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
        set<shared_ptr<Entity>>::size_type count(shared_ptr<Entity> e) const {
            return entities.count(e);
        }
    };
}
