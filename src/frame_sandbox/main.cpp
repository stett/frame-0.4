#include "frame/Frame.h"
#include "systems/Physics.hpp"
#include "systems/GameWindow.hpp"
#include "systems/Window.hpp"
#include "components/BoxNode.h"
#include "components/ViewFollow.h"
#include "components/BackgroundTexture.h"
#include "components/GameEntity.h"
#include "components/Texture.h"

int main(int argc, char** argv) {

    // Make frame
    frame::Frame f;

    // Add a window system
    //f.add_system<Physics>();
    //f.add_system<RenderBoxes>();
    f.add_system<GameWindow>();

    // Add an entity with a sprite component and a child
    auto box0 = f.add_entity<BoxNode, ViewFollow, BackgroundTexture>();
    box0->get_component<BoxNode>()
        ->add_child(f.add_entity<BackgroundTexture>(), 3, 3);

    // Add another child using the set-parent method
    auto box1 = f.add_entity<BoxNode, BackgroundTexture>();
    box1->get_component<BoxNode>()
        ->set_parent(box0, 2, 3);

    // Add a player object to the root box
    auto player = f.add_entity<ViewFollow>();
    player->add_component<GameEntity>()
          ->set_container(box0);
    player->add_component<Texture>()
          ->set("jacob.png");

    // Add other player object to sub box
    auto bird = f.add_entity<ViewFollow>();
    bird->add_component<GameEntity>()
        ->set_container(box1);
    bird->add_component<Texture>()
        ->set("jacob.png");

    // Run the program
    f.run();

    return 0;
}
