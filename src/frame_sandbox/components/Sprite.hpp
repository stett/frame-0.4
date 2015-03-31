#pragma once
#include <SFML/Graphics.hpp>
#include "frame/Component.h"

class Sprite : public frame::Component {
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
