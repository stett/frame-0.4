

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
    BoxNode* node;
    Entity* child;
    int x, y;
    Slot(BoxNode* node = 0, Entity* child = 0, int x = 0, int y = 0)
    : node(node), child(child), x(x), y(y) {}
};


class BoxNode : public Component {
 protected:
    Entity* parent;
    set<Entity*> children;
    Slot* slot;
    Slot slots[7][7];

 public:
    BoxNode();
    ~BoxNode();

 public:
    BoxNode* set_parent(Entity* e, int x, int y);
    BoxNode* add_child(Entity* e, int x, int y);
    BoxNode* remove_child(Entity* e);
};
