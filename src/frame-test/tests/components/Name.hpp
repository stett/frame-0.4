// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once

#include <string>
#include "frame/Component.hpp"
using std::string;

class Name : public frame::Component {
 public:
    Name() : str("name") {
        mask = 1 << 1;
    }
    virtual ~Name() {}
    string str;
};
