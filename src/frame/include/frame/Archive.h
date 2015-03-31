#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::map;

namespace frame {

    class Entity;
    class ArchiveReader;
    class ArchiveWriter;

    typedef vector<Entity*> EntityMapIn;
    typedef map<Entity*, unsigned int> EntityMapOut;
    typedef Entity* EntityPtr;

    template<typename T>
    struct ArchiveIO {
        static void save(ofstream& os, const T& obj, EntityMapOut& emo) {
            os.write((char*)(&obj), sizeof(T));
        }

        static void load(ifstream& is, T& obj, EntityMapIn& emi) {
            is.read((char*)(&obj), sizeof(T));
        }
    };

    // Save/load specialization declarations
    template<> void ArchiveIO<EntityPtr>::save(ofstream& os, const EntityPtr& e, EntityMapOut& emo);
    template<> void ArchiveIO<EntityPtr>::load(ifstream& is, EntityPtr& e, EntityMapIn& emi);
    template<> void ArchiveIO<string>::save(ofstream& os, const string& str, EntityMapOut& emo);
    template<> void ArchiveIO<string>::load(ifstream& is, string& str, EntityMapIn& emi);


    class ArchiveReader {
        friend class Frame;

    protected:
        ifstream is;
        EntityMapIn entity_map;

    public:
        explicit ArchiveReader(const string& tag) {
            is.open(tag, std::ifstream::binary);
        }
        ~ArchiveReader() { is.close(); }

        template<typename T>
        void load(T& obj) {
            ArchiveIO<T>::load(is, obj, entity_map);
        }
    };


    class ArchiveWriter {
        friend class Frame;

    protected:
        ofstream os;
        EntityMapOut entity_map;

    public:
        explicit ArchiveWriter(const string& tag) {
            os.open(tag, std::ofstream::binary);
        }
        ~ArchiveWriter() { os.close(); }

        template<typename T>
        void save(const T& obj) {
            ArchiveIO<T>::save(os, obj, entity_map);
        }
    };
}
