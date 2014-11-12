// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.


#include "frame/Frame.h"
#include "systems/Window.hpp"
#include "components/Sprite.hpp"

int main(int argc, char** argv) {

    // Make frame
    frame::Frame f;

    // Add a window system
    f.add_system<Window>();

    // Add an entity with a sprite component
    f.add_entity<Sprite>();

    // Run the program
    f.run();

    return 0;
}
