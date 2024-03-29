#pragma once
#include "frame/Component.h"

namespace frame {
    class Entity;
    class Parent : public Component {
        friend class Children;

    protected:
        Entity* parent;

    public:
        Parent() : parent(0) {}
        ~Parent() { clear(); }

    public:
        Parent* set(Entity* e);
        Parent* clear();
        Entity* get() { return parent; }
        Entity* operator* () { return parent; }

    protected:
        virtual void save(ArchiveWriter* archive) {
            archive->save<Entity*>(parent);
        }

        virtual void load(ArchiveReader* archive) {
            archive->load<Entity*>(parent);
        }
    };
}
