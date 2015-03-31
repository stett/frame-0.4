


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

    // Add an entity with a sprite component and a child
    auto box0 = f.add_entity<Sprite, BoxNode>();
    box0->get_component<BoxNode>()
        ->add_child(f.add_entity<Sprite>(), 3, 3);

    // Add another child using the set-parent method
    auto box1 = f.add_entity<Sprite, BoxNode>();
    box1->get_component<BoxNode>()
        ->set_parent(box0, 2, 3);

    // Run the program
    f.run();

    return 0;
}
