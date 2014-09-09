// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include "frame/Entity.h"
#include "frame/core/Parent.h"
#include "frame/core/Children.h"
using frame::Parent;
using frame::Children;


REGISTER_FRAME_COMPONENT(Parent);

Parent* Parent::set(Entity* e) {

    // If we had a previous parent, remove ourself
    // from its list of children.
    if (parent) clear();

    // Set the parent pointer
    parent = e;

    // Add a children component to the new parent if necessary,
    // and add this entity to its child list.
    auto children = parent->get_or_add_component<Children>();
    children->child_list.insert(entity);

    // Return this parent for command chaining
    return this;
}

Parent* Parent::clear() {

    // If parent was unset, then we don't need to remove this
    // from its children.
    if (parent == 0)
        return this;

    // Remove ourselves from our old parent's child list
    auto children = parent->get_component<Children>();
    children->child_list.erase(entity);

    // Return this parent for command chaining
    return this;
}
