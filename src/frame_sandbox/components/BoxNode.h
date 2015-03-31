

#pragma once
#include <vector>
#include <set>
#include "frame/Entity.h"
#include "frame/Component.h"
using std::vector;
using std::set;
using frame::Entity;
using frame::Component;


class BoxNode;


struct Slot {
    Entity* child;
    int x, y;
    Slot(Entity* child = 0, int x = 0, int y = 0)
    : child(child), x(x), y(y) {}
};


class BoxNode : public Component {
 protected:
    BoxNode* parent;
    set<Entity*> children;
    Slot* slot;
    Slot slots[7][7];

 public:
    BoxNode();
    ~BoxNode();

 public:
    BoxNode* set_parent(Entity* e, int x, int y);
    BoxNode* set_slot(int x, int y);
    BoxNode* add_child(Entity* e, int x, int y);
    BoxNode* remove_child(Entity* e);
    Entity* get_parent() { return parent ? parent->entity : 0; }
    Slot* get_slot() { return slot; }
    Slot* get_slot(int x, int y) { return &slots[x][y]; }
    const set<Entity*>& get_children() { return children; }
};
