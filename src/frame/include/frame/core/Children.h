#pragma once
#include <set>
#include "frame/Component.h"
using std::set;

namespace frame {
    class Entity;

    class Children : public Component {
        friend class FamilyInterface;
        friend class Parent;

    protected:
        set<Entity*> child_list;

    public:
        Children() {}
        ~Children() { clear(); }

    public:
        Children* add(Entity* e);
        Children* remove(Entity* e);
        Children* clear();
        unsigned int size() { return child_list.size(); }
        set<Entity*>::iterator begin() { return child_list.begin(); }
        set<Entity*>::iterator end() { return child_list.end(); }
        set<Entity*>::iterator find(Entity* e) { return child_list.find(e); }

    protected:
        virtual void save(ArchiveWriter* archive) {
            archive->save<unsigned int>(child_list.size());
            for (auto child : child_list) {
                archive->save<Entity*>(child);
            }
        }
        virtual void load(ArchiveReader* archive) {
            unsigned int num_children;
            archive->load<unsigned int>(num_children);
            for (int i = 0; i < num_children; i ++) {
                Entity* child;
                archive->load<Entity*>(child);
                child_list.insert(child);
            }
        }
    };
}
