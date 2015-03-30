// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "frame/Component.h"
using std::shared_ptr;

class RenderTexture : public frame::Component {
 public:
    shared_ptr<sf::RenderTexture> texture;

    shared_ptr<sf::RenderTexture> get() { return texture; }
    void set(shared_ptr<sf::RenderTexture> new_texture) { texture = new_texture; }
};
