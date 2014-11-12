// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <SFML/Graphics.hpp>
#include "frame/Component.h"

using frame::Component;

class Sprite : public Component {
 public:
    sf::Sprite sprite;

 public:
    Sprite() {
        sf::Texture texture;
        texture.loadFromFile("placeholder.png");
        sprite.setTexture(texture);
    }
    Sprite(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
};
