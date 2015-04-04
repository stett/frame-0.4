#pragma once

#include "frame/System.h"
#include "frame/Node.h"
#include "components/BoxNode.h"
#include "components/Active.h"


class ActiveBoxes : public System {
 protected:
    Node* active_boxes;

 public:
    ActiveBoxes() {
    }

 protected:
    void start() {
        active_boxes = f->add_node<BoxNode, Active>();
    }

    void step() {
    }

    void find_active_family() {
        
    }
};
