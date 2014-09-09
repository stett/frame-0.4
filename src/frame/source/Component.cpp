// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include <typeindex>
#include <typeinfo>
#include <map>
#include <functional>
#include "frame/Component.h"
using std::type_index;
using std::map;
using std::function;
using frame::Component;


unsigned int Component::_mask = 1;
map<type_index, function<Component*()>> Component::component_factories;
map<type_index, unsigned int> Component::component_masks;

function<Component*()> Component::register_component(function<Component*()> factory) {
    Component* c = factory();
    auto type = type_index(typeid(*c));
    component_factories[type] = factory;
    component_masks[type] = _mask;
    map<type_index, unsigned int> test;
    test[type] = _mask;
    _mask = _mask << 1;
    delete c;
    return factory;
}

Component* Component::make_component(type_index type) {
    auto it = component_factories.find(type);
    if (it == component_factories.end()) return 0;
    function<Component*()> factory = it->second;
    return factory();
}

unsigned int Component::mask() const {
    auto type = type_index(typeid(*this));
    return component_masks[type];
}
