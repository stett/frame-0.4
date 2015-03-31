

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

    Name* set(const string& _str) {
        str = _str;
        return this;
    }
    const string& get() { return str; }

 protected:
    void save(frame::ArchiveWriter* archive) {
        archive->save<string>(str);
    }

    void load(frame::ArchiveReader* archive) {
        archive->load<string>(str);
    }
};
