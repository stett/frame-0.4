// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <fstream>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <map>
#include <functional>
#include <cstdio>
using std::type_index;
using std::string;
using std::map;
using std::pair;
using std::function;



namespace frame {

    class Entity;

    class Component {
        friend class Frame;
        friend class Node;

    public:
        static unsigned int _mask;
        static map<string, function<Component*()>> component_factories;
        static map<type_index, unsigned int> component_masks;
        static map<type_index, string> component_names;
        //static map<string, type_index> component_types;
        static function<Component*()> register_component(string name, type_index type, function<Component*()> factory);
        //static Component* make_component(type_index type);
        static Component* make_component(string name);
    protected:
        Entity* entity;


    public:
        Component() : entity(0) {}
        virtual ~Component() {}

    public:
        const Entity* get_entity() const { return entity; }
        unsigned int mask() const;
        string name() const;

    protected:
        virtual void save(std::ofstream* os) {}
        virtual void load(std::ifstream* is) {}
    };
}


#define STR(str) #str
#define REGISTER_FRAME_COMPONENT(COMPONENT_TYPE)                \
    function<frame::Component*()> COMPONENT_TYPE ## Prototype = \
    frame::Component::register_component(                       \
        STR(COMPONENT_TYPE),                                    \
        type_index(typeid(COMPONENT_TYPE)),                     \
        []() {                                                  \
            return new COMPONENT_TYPE();                        \
        });
