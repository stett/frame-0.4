#pragma once
#include <list>
#include "frame/Entity.h"
#include "frame/Component.h"
#include "components/GameEntityContainer.h"
using std::list;
using frame::Entity;
using frame::Component;

class GameEntity : public Component {
 protected:
    GameEntityContainer* container;

 public:
    GameEntity();
    ~GameEntity();
};
