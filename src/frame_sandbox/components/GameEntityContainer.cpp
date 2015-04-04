#include "GameEntityContainer.h"
#include "GameEntity.h"

REGISTER_FRAME_COMPONENT(GameEntityContainer);


GameEntityContainer::GameEntityContainer() {}

GameEntityContainer::~GameEntityContainer() {

    // Remove game-entity component from all game entities within this container
    for (auto e : game_entities)
        e->remove_component<GameEntity>();
}
