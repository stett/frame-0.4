#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "frame/Component.h"
using std::string;

class Sprite : public frame::Component {
 public:
    sf::Sprite sprite;

 public:
    Sprite() { set_texture("placeholder.png"); }
    Sprite(const sf::Texture& texture) { set_texture(texture); }

 public:
    void set_texture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    void set_texture(string filename) {
        sf::Texture texture;
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
    }
};
