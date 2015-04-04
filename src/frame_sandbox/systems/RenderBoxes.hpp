#pragma once

#include <vector>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "frame/System.h"
#include "frame/Node.h"
#include "components/BoxNode.h"
#include "components/Active.h"
#include "components/RenderTexture.h"
#include "components/ViewFollow.h"
using std::shared_ptr;
using std::vector;
using std::list;
using frame::System;
using frame::Node;

typedef vector<shared_ptr<sf::RenderTexture>> texture_list;

class RenderBoxes : public System {
 protected:
    Node* follow_box;
    Node* active_boxes;
    Node* render_boxes;
    vector<texture_list> box_textures;
    const int TEXTURE_LEVELS = 3;  // Number of box textures
    const int BOX_RENDER_SIZE = 600;  // Pixels
    const int BOX_PHYSICAL_SIZE = 7;  // "meters"
    const int BOX_METERS_PER_SLOT = (float)BOX_PHYSICAL_SIZE/(float)7;
    const int BOX_PIXELS_PER_SLOT = (float)BOX_RENDER_SIZE/(float)7;
    const int PIXELS_PER_METER = (float)BOX_RENDER_SIZE/(float)BOX_PHYSICAL_SIZE;


 public:
    RenderBoxes() {
        box_textures.resize(TEXTURE_LEVELS);
    }

 protected:
    void start() {
        follow_box = f->add_node<BoxNode, ViewFollow>();
        active_boxes = f->add_node<BoxNode, Active>();
        render_boxes = f->add_node<BoxNode, RenderTexture>();
    }

    //
    void signal() {

        //
        // TODO:
        // When active boxes change, trigger this code!!!
        //

        // Vector which will count the number of
        // textures rendered for each texture level.
        vector<int> texture_count;
        texture_count.resize(TEXTURE_LEVELS, 0);

        // Remove render-texture from old boxes
        for (auto e : *render_boxes)
            e->remove_component<RenderTexture>();

        // Get the follow-box's box-node
        auto follow_box_node = (*follow_box->begin())->get_component<BoxNode>();

        // Assign textures
        for (auto e : *active_boxes) {
            auto box_node = e->get_component<BoxNode>();

            // If this box is too far from the follow-box then forget about it
            int depth = box_node->get_depth() - follow_box_node->get_depth();
            if (depth < -1 || TEXTURE_LEVELS <= depth)
                continue;
            int level = depth < 0 ? 0 : depth;

            // Allocate the new texture if needed.
            // Else, get a previously allocated one.
            shared_ptr<sf::RenderTexture> render_texture;
            if (box_textures[level].size() <= texture_count[level]) {
                render_texture = shared_ptr<sf::RenderTexture>(new sf::RenderTexture());
                int size = BOX_RENDER_SIZE / (7 * (level + 1));
                render_texture->create(size, size);
                box_textures[level].push_back(render_texture);
            } else {
                render_texture = box_textures[level][texture_count[level] - 1];
            }

            // Assign it a texture pointer
            auto texture = e->get_or_add_component<RenderTexture>();
            texture->set(render_texture);
        }
    }

    void step() {

        // Mark every box as not-rendered
        for (auto e : *render_boxes)
            e->get_component<RenderTexture>()->rendered = false;

        // Loop through and render each box
        for (auto e : *render_boxes)
            render_box(e);
    }

    void render_box(Entity* e_box) {

        // Get this box's tree node & texture
        auto box_node = e_box->get_component<BoxNode>();
        auto box_texture = e_box->get_component<RenderTexture>();

        // If this box has already been rendered, pass it
        if (box_texture->rendered) return;

        // Draw background
        box_texture->get()->clear(sf::Color::Blue);

        // Draw child boxes
        for (auto child : box_node->get_children()) {

            // Render child texture
            render_box(child);

            // Get the child's texture
            auto child_node = child->get_component<BoxNode>();
            auto child_texture = child->get_component<RenderTexture>();
            auto child_sprite = sf::Sprite(child_texture->get()->getTexture());

            // Child box transforms
            float slot_size = box_texture->get()->getTexture().getSize().x / 7;
            sf::RenderStates states(sf::Transform().translate(
                slot_size * box_node->get_slot()->x,
                slot_size * box_node->get_slot()->y
            ));

            // Queue the child for rendering in the parent texture
            box_texture->get()->draw(child_sprite, states);
        }

        // Draw foreground

        // Mark this entity as rendered
        box_texture->get()->display();
        box_texture->rendered = true;
    }
};
