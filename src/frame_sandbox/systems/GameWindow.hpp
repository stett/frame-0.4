#pragma once

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "frame/Frame.h"
#include "frame/System.h"
#include "frame/Node.h"
#include "components/Sprite.hpp"
#include "components/BackgroundTexture.h"
#include "components/ViewFollow.h"
#include "components/BoxNode.h"
#include "components/GameEntityContainer.h"
#include "components/GameEntity.h"
using std::shared_ptr;
using std::string;
using frame::Frame;
using frame::System;
using frame::Node;


const int BOX_RENDER_DEPTH = 3;
const int BOX_RENDER_SIZE = 600;  // Pixels
const int BOX_PHYSICAL_SIZE = 7;  // "meters"
const int BOX_METERS_PER_SLOT = (float)BOX_PHYSICAL_SIZE/(float)7;
const int BOX_PIXELS_PER_SLOT = (float)BOX_RENDER_SIZE/(float)7;
const int PIXELS_PER_METER = (float)BOX_RENDER_SIZE/(float)BOX_PHYSICAL_SIZE;


class GameWindow : public System {
 private:
    struct View {
        float x, tx;
        float y, ty;
        float scale, tscale;
        float angle, tangle;
        View() : x(0), tx(0), y(0), ty(0), scale(1), tscale(1), angle(0), tangle(0) {}
    };

 private:
    shared_ptr<sf::RenderWindow> window;
    View view;
    Node* follow_box;

 protected:
    void get_view_transforms(sf::RenderStates& states) {
        states.transform
              .translate(sf::Vector2f(
                window->getSize().x * .5f,
                window->getSize().y * .5f))
              .scale(sf::Vector2f(view.scale, view.scale))
              .translate(sf::Vector2f(view.x, view.y))
              .translate(-sf::Vector2f(
                window->getSize().x * .5f,
                window->getSize().y * .5f));
    }

    void start() {

        // Collect entities with sprite components
        // sprites = f->add_node<Sprite>();
        // Get the view-follow box and draw it
        follow_box = f->add_node<BoxNode, ViewFollow>();

        // Create the window object
        window = shared_ptr<sf::RenderWindow>(
            new sf::RenderWindow(
                sf::VideoMode(800, 600),
                "MetaBox",
                sf::Style::Close | sf::Style::Titlebar));
    }

    void step_begin() {
        window->clear(sf::Color(0, 0, 0));
    }

    void step() {

        // If we have a box to follow, draw it. Just take the first one.
        auto e = *follow_box->begin();
        if (!e) return;

        // Draw the main box
        draw_box(e, sf::Transform());
    }

    void step_end() {
        window->display();
    }

    void stop() {
        window->close();
        window.reset();
    }

    void draw_box(Entity* e, const sf::Transform& t, int depth = 0) {

        // Don't do it if it's too deep
        if (depth >= BOX_RENDER_DEPTH) return;

        // Get this box's node
        auto box_node = e->get_component<BoxNode>();

        // Render the background if there is one
        auto box_bg_texture = e->get_component<BackgroundTexture>();
        if (box_bg_texture) {

            // Scale the background sprite so that it's the correct render size
            const sf::Texture& texture = box_bg_texture->get();
            sf::Sprite sprite; sprite.setTexture(texture);
            sf::Vector2u size = texture.getSize();
            sprite.setScale(sf::Vector2f(
                (float)BOX_RENDER_SIZE / (float)size.x,
                (float)BOX_RENDER_SIZE / (float)size.y));

            // Queue it up.
            window->draw(sprite, sf::RenderStates(t));
        }

        // Render child game entities if there are any
        auto box_entity_container = e->get_component<GameEntityContainer>();
        if (box_entity_container) {

            // Draw each of the game entities
            //for (auto game_entity : box_entity_container->get_game_entities()) {

                // If the entity has a sprite, render it

            //}
        }

        // Render it's children
        for (auto child : box_node->get_children()) {

            // Get the box node & slot for this child
            auto child_box_node = child->get_component<BoxNode>();
            auto child_slot = child_box_node->get_slot();

            // Generate the child's transform
            auto child_t = sf::Transform().translate(child_slot->x * BOX_RENDER_SIZE / 7.f,
                                                     child_slot->y * BOX_RENDER_SIZE / 7.f)
                                          .scale(sf::Vector2f(1.f / 7.f, 1.f / 7.f))
                                          .rotate(0.f)
                                          .combine(t);

            // Draw this child
            draw_box(child, child_t, depth + 1);
        }

        // Render the foreground
        // TODO
    }
};
