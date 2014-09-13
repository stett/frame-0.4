// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;
using std::string;

namespace frame {

    template<typename T>
    struct ArchiveIO {
        static void save(ofstream* os, const T& obj) {
            os->write((char*)(&obj), sizeof(T));
        }

        static void load(ifstream* is, T& obj) {
            is->read((char*)(&obj), sizeof(T));
        }
    };

    // Save/load specialization declarations
    template<> void ArchiveIO<string>::save(ofstream* os, const string& str);
    template<> void ArchiveIO<string>::load(ifstream* is, string& str);


    class Archive {
    public:
        enum Mode { read, write };

    private:
        Mode mode;
        ifstream is;
        ofstream os;

    public:
        explicit Archive(const string& tag, Mode mode) : mode(mode) {
            if      (mode == read)  is.open(tag, std::ifstream::binary);
            else if (mode == write) os.open(tag, std::ofstream::binary);
        }

        ~Archive() {
            if      (mode == read)  is.close();
            else if (mode == write) os.close();
        }

        template<typename T>
        void save(const T& obj) {
            if (mode != write) return;
            ArchiveIO<T>::save(&os, obj);
        }

        template<typename T>
        void load(T& obj) {
            if (mode != read) return;
            ArchiveIO<T>::load(&is, obj);
        }
    };
}
