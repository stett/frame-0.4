// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#include <fstream>
#include <string>
#include "frame/Archive.h"
using std::ifstream;
using std::ofstream;
using std::string;


namespace frame {
    class Entity;

    // Entity* IO specialization
    template<>
    void ArchiveIO<EntityPtr>::save(ofstream& os, const EntityPtr& e, EntityMapOut& emo) {
        unsigned int id = emo[e];
        ArchiveIO<unsigned int>::save(os, id, emo);
    }

    template<>
    void ArchiveIO<Entity*>::load(ifstream& is, EntityPtr& e, EntityMapIn& emi) {
        unsigned int id;
        ArchiveIO<unsigned int>::load(is, id, emi);
        e = emi[id];
    }

    // string IO specialization
    template<>
    void ArchiveIO<string>::save(ofstream& os, const string& str, EntityMapOut& emo) {
        os.write(str.c_str(), sizeof(char) * (str.size()+1));
    }
    template<>
    void ArchiveIO<string>::load(ifstream& is, string& str, EntityMapIn& emi) {
        str.clear();
        char c = ' ';
        while (true) {
            is.read((char*)(&c), sizeof(char));
            if (c == '\0') break;
            str += c;
        }
    }
}
