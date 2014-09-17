// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include <cstdarg>
#include "frame/Entity.h"
#include "frame/core/Parent.h"
#include "frame/core/Children.h"
using frame::Parent;
using frame::Children;


REGISTER_FRAME_COMPONENT(Children);

Children* Children::add(Entity* e_child) {

    // Add entity to child list
    child_list.insert(e_child);

    // Add parent component to child entity if necessary
    auto parent = e_child->get_or_add_component<Parent>();
    parent->parent = entity;

    // Return this children for command chaining
    return this;
}

Children* Children::remove(Entity* e_child) {

    // Remove the child from the child list.
    // If it wasn't in the list, stop here.
    if (child_list.erase(e_child) == 0)
        return this;

    // Clear the child's parent pointer
    auto parent = e_child->get_component<Parent>();
    parent->parent = 0;

    // Return this children for command chaining
    return this;
}

Children* frame::Children::clear() {
    while (size())
        remove(*begin());
    return this;
}

void frame::Children::save(frame::ArchiveWriter* archive) {
    archive->save<unsigned int>(child_list.size());
    for (auto child : child_list) {
        archive->save<Entity*>(child);
    }
}

void frame::Children::load(frame::ArchiveReader* archive) {
    unsigned int num_children;
    archive->load<unsigned int>(num_children);
    for (int i = 0; i < num_children; i ++) {
        Entity* child;
        archive->load<Entity*>(child);
        child_list.insert(child);
    }
}
