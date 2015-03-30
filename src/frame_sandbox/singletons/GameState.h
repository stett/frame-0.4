// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include "frame/Entity.h"
#include "frame/Singleton.h"
using frame::Entity;
using frame::Singleton;

struct GameState : public Singleton {
    Entity* root_box;
    Entity* active_box;
    GameState() : root_box(0), active_box(0) {}
};
