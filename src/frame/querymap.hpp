// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <set>
#include <map>
#include <utility>
using std::set;
using std::multimap;
using std::pair;

namespace frame {

    template <typename K, typename V>
    class querymap {
    public:
        typedef set<K> keyset;
        typedef typename keyset::iterator keyset_iter;

    private:
        multimap<keyset, V> kv_map;
        typename multimap<keyset, V>::iterator first;
        typename multimap<keyset, V>::iterator second;

    private:
        void subsets(set<K> key_set, set<set<K>> &sub_key_sets) {
            if (key_set.empty())
                return;

            sub_key_sets.insert(key_set);

            for (typename set<K>::iterator i = key_set.begin(); i != key_set.end(); ++i) {
                set<K> new_key_set(key_set);
                new_key_set.erase(*i);
                subsets(new_key_set, sub_key_sets);
            }
        }

    public:
        void insert(keyset key_set, V val) {
            set<keyset> sub_key_sets;
            subsets(key_set, sub_key_sets);
            for (auto sub_key_set : sub_key_sets) {
                kv_map.insert(pair<keyset, V>(sub_key_set, val));
            }
        }

        bool remove(V val) {
            /*
             * TODO: DO THIS SHIT
             */
            return true;
        }

        querymap& find(const keyset &key_set) {
            auto iter_pair = kv_map.equal_range(key_set);
            first = iter_pair.first;
            second = iter_pair.second;
            return *this;
        }
        typename multimap<keyset, V>::iterator begin() const { return first; }
        typename multimap<keyset, V>::iterator end() const { return second; }
    };
}
