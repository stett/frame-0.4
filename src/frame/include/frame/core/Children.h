// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

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
        Children() { mask = 1; }
        /*
        explicit Children(...);
        */
        ~Children() { clear(); }

    public:
        Children* add(Entity* e);
        Children* remove(Entity* e);
        Children* clear();
        unsigned int size() { return child_list.size(); }
        set<Entity*>::iterator begin() { return child_list.begin(); }
        set<Entity*>::iterator end() { return child_list.end(); }
        set<Entity*>::iterator find(Entity* e) { return child_list.find(e); }
    };
}
