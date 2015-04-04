#pragma once
#include "frame/Component.h"
using frame::Component;
using frame::Entity;

class GameEntity : public Component {
    friend class GameEntityContainer;

protected:
    Entity* container;

public:
    GameEntity() : container(0) {}
    ~GameEntity() { clear_container(); }

public:
    GameEntity* set_container(Entity* e_container);
    GameEntity* clear_container();
    Entity* get_container() { return container; }

protected:
    virtual void save(frame::ArchiveWriter* archive) {
        archive->save<Entity*>(container);
    }

    virtual void load(frame::ArchiveReader* archive) {
        archive->load<Entity*>(container);
    }
};
