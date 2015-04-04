#pragma once
#include <list>
#include "frame/Entity.h"
#include "frame/Component.h"
using std::list;
using frame::Entity;
using frame::Component;

class GameEntityContainer : public Component {
    friend class GameEntity;
 protected:
    list<Entity*> game_entities;

 public:
    GameEntityContainer();
    ~GameEntityContainer();
};
