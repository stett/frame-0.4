// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "frame/Frame.h"
#include "frame/System.h"
#include "frame/Node.h"
#include "components/Sprite.hpp"
using std::shared_ptr;
using std::string;
using frame::Frame;
using frame::System;
using frame::Node;

class Window : public System {
 private:
    shared_ptr<sf::RenderWindow> window;
    Node* sprites;

 protected:
    void start() {

        // Collect entities with sprite components
        sprites = f->add_node<Sprite>();

        // Create the window object
        window = shared_ptr<sf::RenderWindow>(
            new sf::RenderWindow(
                sf::VideoMode(800, 600),
                "Frame Sandbox",
                sf::Style::Close | sf::Style::Titlebar));
    }

    void step_begin() {
        window->clear(sf::Color(100, 100, 100));
    }

    void step() {

        // Render all sprites :D
        for (auto e : *sprites)
            window->draw(e->get_component<Sprite>()->sprite);
    }

    void step_end() {
        window->display();
    }

    void stop() {
        window->close();
        window.reset();
    }
};
