// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include <list>
#include <SFML/Graphics.hpp>
#include "frame/System.h"
#include "frame/Node.h"
#include "frame/core/Parent.h"
#include "frame/core/Children.h"
#include "components/Sprite.hpp"
#include "components/RenderTexture.hpp"
#include "components/Slots.hpp"
#include "singletons/GameState.h"
using std::list;
using frame::System;
using frame::Node;
using frame::Parent;
using frame::Children;

// Overridable constants
#ifndef NUM_BOX_TEXTURES
#define NUM_BOX_TEXTURES 8
#endif
#ifndef BOX_RENDER_SIZE
#define BOX_RENDER_SIZE 400
#endif
#ifndef BOX_RENDER_DEPTH
#define BOX_RENDER_DEPTH 3
#endif

class Render : public System {
 private:
    shared_ptr<sf::RenderTexture> box_textures[NUM_BOX_TEXTURES];
    int current_texture_id;
    Node* boxes;

 protected:
    void start() {

        // Set the texture ptr to the first one
        current_texture_id = 0;

        // Make a node to track boxes which have sprites
        boxes = f->add_node<Sprite, Slots>();

        // Allocate contiguous, reusable render spaces
        for (int i = 0; i < NUM_BOX_TEXTURES; i ++) {
            auto texture = shared_ptr<sf::RenderTexture>(new sf::RenderTexture());
            texture->create(BOX_RENDER_SIZE, BOX_RENDER_SIZE);
            box_textures[i] = texture;
        }
    }

    void step_begin() {

        // Remove "Sprite" from all boxes that have it and reset the current texture
        current_texture_id = 0;
        for (auto box : *boxes)
            box->remove_component<Sprite>();

        // Get the active box entity from the game state.
        // If there is no active box, just return.
        Entity* active_box = f->singleton<GameState>()->active_box;
        /*Entity* root_box = f->singleton<GameState>()->root_box;
        if (!active_box) active_box = root_box;*/
        if (!active_box) return;

        // Add sprite components to and render all visible boxes,
        // starting with the active box's parent if it has one.
        /*Entity* active_box_parent = active_box->get_component<Parent>()->get();
        if (active_box_parent) render_box(active_box_parent, -1);
        else                   render_box(active_box, 0);*/
        render_box(active_box, 0);
    }

 protected:
    void render_box(Entity* box, int depth) {

        // If we aren't already at max render depth and this box has children,
        // render them first.
        if (depth < BOX_RENDER_DEPTH) {
            auto children = box->get_component<Children>();
            if (children) {
                for (auto child : *children) {
                    auto texture = child->get_or_add_component<RenderTexture>();
                    texture->set();
                    render_box(child, depth + 1);
                }
            }
        }

        // Render the box background 
        */
    }
};
