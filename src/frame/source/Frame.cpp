// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.


#include <typeindex>
#include <cstdio>
#include <typeinfo>
#include <string>
#include <set>
#include "frame/Frame.h"
#include "frame/Entity.h"
#include "frame/Node.h"
#include "frame/System.h"
#include "frame/interface/FrameInterface.h"
using std::type_index;
using std::string;
using std::set;
using frame::Frame;
using frame::FrameInterface;
using frame::Entity;
using frame::Node;
using frame::System;


/*
 * Basic ECS operations - adding removing entities, nodes, systems
 */

Entity* Frame::add_entity() {
    Entity* e = new Entity(this);
    entities.insert(e);
    ravel(e);
    return e;
}

Node* Frame::add_node() {
    Node* n = new Node(this);
    nodes.insert(n);
    ravel(n);
    return n;
}

void Frame::clear_entities() {
    while (entities.size())
        remove_entity(*entities.begin());
}

void Frame::clear_nodes() {
    while (nodes.size())
        remove_node(*nodes.begin());
}

void Frame::clear_systems() {
    while (systems.size())
        remove_system(*systems.begin());
}

void Frame::remove_system(System* s) {
    systems.erase(s);
    delete s;
}


/*
 * Raveling system - keeps entities and nodes properly associated
 */

void Frame::ravel(Entity* e) {
    for (auto n : nodes)
        if ((n->mask & e->mask) >= n->mask)
            ravel(n, e);
}

void Frame::ravel(Node* n) {
    for (auto e : entities)
        if ((n->mask & e->mask) >= n->mask)
            ravel(n, e);
}

void Frame::ravel(Node* n, Entity* e) {
    n->entities.insert(e);
    e->nodes.insert(n);
}

void Frame::unravel(Entity* e) {
    for (auto n : e->nodes)
        if ((n->mask & e->mask) < n->mask)
            unravel(n, e);
}

void Frame::unravel(Node* n) {
    for (auto e : n->entities)
        if ((n->mask & e->mask) < n->mask)
            unravel(n, e);
}

void Frame::unravel(Node* n, Entity* e) {
    n->entities.erase(e);
    e->nodes.erase(n);
}


/*
 * Entity manipulation interface
 */

void Frame::remove_entity(Entity* e) {
    for (auto c: e->components)
        delete c.second;
    for (auto n : e->nodes)
        unravel(n, e);
    entities.erase(e);
    delete e;
}

void Frame::add_component_to_entity(Entity* e, Component* c) {
    auto c_type = type_index(typeid(*c));
    auto c_it = e->components.find(c_type);
    if (c_it != e->components.end())
        remove_component_from_entity(e, c_it->second);
    e->components[c_type] = c;
    e->mask |= c->mask();
    c->entity = e;
    ravel(e);
}

void Frame::remove_component_from_entity(Entity* e, Component* c) {
    auto c_type = type_index(typeid(*c));
    e->components.erase(c_type);
    e->mask &= !c->mask();
    unravel(e);
    delete c;
}


/*
 * Node manipulation interface
 */

void Frame::remove_node(Node* n) {
    for (auto e : n->entities)
        unravel(n, e);
    if (nodes.erase(n))
        delete n;
}

void Frame::add_components_to_node(Node* n, unsigned int mask) {
    n->mask |= mask;
    unravel(n);
}

void Frame::remove_components_from_node(Node* n, unsigned int mask) {
    n->mask &= !mask;
    ravel(n);
}


/*
 * Frame control interface
 */

void Frame::run() {
    for (auto s : systems) s->start();
    while (running) step();
    for (auto s : systems)s->stop();
}

void Frame::step() {
    for (auto s : systems) s->step_begin();
    for (auto s : systems) s->step();
    for (auto s : systems) s->step_end();
}

void Frame::stop() {
    running = false;
}

void Frame::save(string tag) {}

void Frame::load(string tag) {}
