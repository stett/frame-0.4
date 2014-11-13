// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include <list>
#include <SFML/Graphics.hpp>
#include "frame/System.h"
#include "frame/Node.h"
using std::list;
using frame::System;
using frame::Node;

class Render : public System {
 private:
    list<shared_ptr<sf::RenderTexture>> box_textures;
    Node* boxes;

 public:
    Render() {

    }

 protected:
    void start() {
        //boxes = f->add_node<Sprite>();
    }

    void step_begin() {

    }
};
