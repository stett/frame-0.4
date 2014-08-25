// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <memory>
#include "Component.hpp"

namespace frame {
    template <class T>
    class List : public Component {
    public:
        Component() {
            // Assert that T is a component base
            static_cast<Component*>((T*)0);
        }
    };
}
