// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.


#include "frame/Frame.h"
#include "systems/Physics.hpp"
#include "systems/Render.hpp"
#include "systems/Window.hpp"
#include "components/Sprite.hpp"
#include "components/BoxNode.h"
#include "entity_factories.hpp"

int main(int argc, char** argv) {

    // Make frame
    frame::Frame f;

    // Add a window system
    f.add_system<Physics>();
    f.add_system<Render>();
    f.add_system<Window>();

    // Add an entity with a sprite component
    frame::Entity* box0 = f.add_entity<BoxNode>();
    //frame::Entity* box1 = f.add_entity<BoxNode, Sprite>();
    //frame::Entity* box2 = f.add_entity<BoxNode, Sprite>();
    //frame::Entity* box3 = f.add_entity<BoxNode, Sprite>();

    //box1->get_component<BoxNode>()->set_parent(box0);
    //box2->get_component<BoxNode>()->set_parent(box0);

    // Run the program
    f.run();

    return 0;
}
