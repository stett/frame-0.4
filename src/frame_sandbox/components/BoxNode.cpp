

#include "components/BoxNode.h"


REGISTER_FRAME_COMPONENT(BoxNode);


BoxNode::BoxNode() {
    parent = 0;
    for (int x = 0; x < 7; x ++)
    for (int y = 0; y < 7; y ++)
        slots[x][y] = Slot(0, x, y);
}


BoxNode::~BoxNode() {

    // Remove this box-node from its parent's children
    if (parent)
        parent->remove_child(entity);

    // Unset the parent pointers of this box-node's children
    while (children.size())
        remove_child(*children.begin());
}


BoxNode* BoxNode::set_parent(Entity* e, int x, int y) {

    // If the new parent doesn't have an opening in slot (x, y), stop here.
    // This keeps us from accidentally orphaning box tree nodes.
    if (e && e->get_or_add_component<BoxNode>()->slots[x][y].child)
        return this;

    // Remove from existing parent/slot.
    // This will clear the parent/slot if they're set,
    // so we don't have to do it manually.
    if (parent)
        parent->remove_child(entity);

    // If a new non-null parent was passed in, add this to its children
    if (e)
        e->get_component<BoxNode>()->add_child(entity, x, y);

    // Chain
    return this;
}

BoxNode* BoxNode::set_slot(int x, int y) {

    // If we don't have a parent or the target slot is full, stop here.
    if (!parent || parent->slots[x][y].child)
        return this;

    // Remove from previous slot and add to new slot
    slot->child = 0;
    slot = &parent->slots[x][y];
    slot->child = entity;
}

BoxNode* BoxNode::add_child(Entity* e, int x, int y) {

    // If there's already something in this slot, stop here.
    if (slots[x][y].child)
        return this;

    // If the insertion failed, it's already a child - stop here.
    if (!children.insert(e).second)
        return this;

    // Set the slot child
    slots[x][y].child = e;

    // Make sure the child has a box-node component. Set it's parent and slot.
    auto node = e->get_or_add_component<BoxNode>();
    node->parent = this;
    node->slot = &slots[x][y];

    // Chain
    return this;
}

BoxNode* BoxNode::remove_child(Entity* e) {

    // If we failed to remove from the child set,
    // then it's not actually a child so stop here
    if (children.erase(e) == 0)
        return this;

    // Remove from parent/slot
    auto node = e->get_component<BoxNode>();
    node->parent = 0;
    node->slot->child = 0;
    node->slot = 0;

    // Chain
    return this;
}
