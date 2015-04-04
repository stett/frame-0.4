#include "GameEntity.h"

REGISTER_FRAME_COMPONENT(GameEntity);


GameEntity::GameEntity() : container(0) {}

GameEntity::~GameEntity() {

    // Remove from container if there was one
    if (container) {
        // erase from the container's list
    }
}