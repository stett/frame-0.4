#pragma once
#include <vector>
#include <set>
#include "frame/Entity.h"
#include "frame/Component.h"
#include "frame/Archive.h"
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

 protected:
    virtual void save(frame::ArchiveWriter* archive) {

        //
        // NOTE: We don't save parent data here.
        // Instead, we assume the top parent is saved/loaded.
        // Parent data is loaded to child nodes in the child-load loop.
        //

        // Save the size of the child list
        archive->save<unsigned int>(children.size());

        // Save each child
        for (int x = 0; x < 7; x ++)
        for (int y = 0; y < 7; y ++) {
            auto child = slots[x][y].child;
            if (!child) continue;

            // Save the child's pointer and slot position
            archive->save<Entity*>(child);
            archive->save<int>(x);
            archive->save<int>(y);
        }
    }

    virtual void load(frame::ArchiveReader* archive) {

        // Load the number of children
        unsigned int num_children;
        archive->load<unsigned int>(num_children);

        // Load each of the children
        for (int i = 0; i < num_children; i ++) {

            // Load the child's pointer and slot position
            Entity* child;
            int x, y;
            archive->load<Entity*>(child);
            archive->load<int>(x);
            archive->load<int>(y);

            // Add the child
            add_child(child, x, y);
        }
    }
};
