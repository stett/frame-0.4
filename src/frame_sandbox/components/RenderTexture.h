#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "frame/Entity.h"
#include "frame/Component.h"
using std::shared_ptr;
using frame::Entity;
using frame::Component;

typedef shared_ptr<sf::RenderTexture> texture_ptr;

class RenderTexture : public Component {
 protected:
    texture_ptr texture;

 public:
    bool rendered;

 public:
    RenderTexture() : texture(0), rendered(false) {}
    RenderTexture(texture_ptr texture) : texture(texture), rendered(false) {}

 public:
    RenderTexture* set(texture_ptr new_texture);
    texture_ptr get() { return texture; }

};