// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <fstream>
#include <string>
#include <cstdio>
#include "frame/Component.h"
using std::string;

class Name : public frame::Component {
 public:
    Name() : str("Name") {}
    Name(string str) : str(str) {}
    virtual ~Name() {}
    string str;

 protected:
    void save(frame::Archive* archive) {
        archive->save<string>(str);
    }

    void load(frame::Archive* archive) {
        archive->load<string>(str);
    }
};
