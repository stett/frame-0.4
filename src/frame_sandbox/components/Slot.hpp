// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include "frame/Component.h"

class Slot : public frame::Component {
 private:
    int x;
    int y;

 public:
    Slot() : x(0), y(0) {}

    void set(int x, int y) {
        if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
            this->x = x;
            this->y = y;
        }
    }

    void get(int& x, int& y) {
        x = this->x;
        y = this->y;
    }
    int get_x() const { return x; }
    int get_y() const { return y; }
};
