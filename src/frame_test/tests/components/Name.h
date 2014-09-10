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
    void save(std::ofstream* os) {
        os->write(str.c_str(), sizeof(char) * (str.size() + 1));
    }

    void load(std::ifstream* is) {
        char c = ' ';
        while (true) {
            is->read(&c, sizeof(char));
            if (c == '\0') break;
            else str += c;
        }
    }
};
