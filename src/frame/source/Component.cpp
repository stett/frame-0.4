#include <typeindex>
#include <typeinfo>
#include <string>
#include <map>
#include <functional>
#include "frame/Component.h"
#include "frame/Archive.h"
using std::type_index;
using std::string;
using std::map;
using std::function;
using frame::Component;


unsigned int Component::_mask = 1;
map<string, function<Component*()>> Component::component_factories;
map<type_index, unsigned int> Component::component_masks;
map<type_index, string> Component::component_names;

function<Component*()> Component::register_component(string name, type_index type, function<Component*()> factory) {
    component_factories[name] = factory;
    component_masks[type] = _mask;
    component_names[type] = name;
    _mask = _mask << 1;
    return factory;
}

Component* Component::make_component(string name) {
    auto it = component_factories.find(name);
    if (it == component_factories.end()) return 0;
    function<Component*()> factory = it->second;
    return factory();
}

unsigned int Component::mask() const {
    auto type = type_index(typeid(*this));
    return component_masks[type];
}

string Component::name() const {
    auto type = type_index(typeid(*this));
    return component_names[type];
}
