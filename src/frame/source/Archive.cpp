// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include <fstream>
#include <string>
#include "frame/Archive.h"
using std::ifstream;
using std::ofstream;
using std::string;


namespace frame {

    // A special save overload for strings
    template<>
    void ArchiveIO<string>::save(ofstream* os, const string& str) {
        os->write(str.c_str(), sizeof(char) * (str.size()+1));
    }

    // A special load overload for strings
    template<>
    void ArchiveIO<string>::load(ifstream* is, string& str) {
        str.clear();
        char c = ' ';
        while (true) {
            is->read((char*)(&c), sizeof(char));
            if (c == '\0') break;
            str += c;
        }
    }
}