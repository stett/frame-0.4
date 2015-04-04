#include "frame/Frame.h"
#include "systems/Physics.hpp"
#include "systems/RenderBoxes.hpp"
#include "systems/GameWindow.hpp"
#include "components/BoxNode.h"
#include "components/ViewFollow.h"
#include "entity_factories.hpp"

int main(int argc, char** argv) {

    // Make frame
    frame::Frame f;

    // Add a window system
    //f.add_system<Physics>();
    //f.add_system<RenderBoxes>();
    f.add_system<GameWindow>();

    // Add an entity with a sprite component and a child
    auto box0 = f.add_entity<BoxNode, ViewFollow, Sprite>();
    box0->get_component<BoxNode>()
        ->add_child(f.add_entity<Sprite>(), 0, 0);

    // Add another child using the set-parent method
    auto box1 = f.add_entity<BoxNode, Sprite>();
    box1->get_component<BoxNode>()
        ->set_parent(box0, 2, 3);

    // Run the program
    f.run();

    return 0;
}
