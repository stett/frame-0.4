// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <cstdio>
#include <typeinfo>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "gtest/gtest.h"
#include "frame/Frame.h"
using frame::Frame;
using frame::Entity;
using frame::Component;
using frame::Node;


namespace {

    class SFMLTest : public ::testing::Test {
    protected:
        Frame f;
    };

    TEST_F(SFMLTest, TestOpenSFMLWindow) {
        auto window = new sf::RenderWindow(sf::VideoMode(BOX_RENDER_SIZE, BOX_RENDER_SIZE), "Metabox Surfaces - Proof Of Concept", sf::Style::Close | sf::Style::Titlebar);
        window->setActive(true);

        while (window->isOpen()) {
            // .|.
        }
    }
}
