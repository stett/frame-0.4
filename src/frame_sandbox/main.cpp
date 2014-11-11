// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    auto window = new sf::RenderWindow(sf::VideoMode(800, 600), "Frame Sandbox", sf::Style::Close | sf::Style::Titlebar);
    window->setActive(true);

    while (window->isOpen()) {}

    return 0;
}
