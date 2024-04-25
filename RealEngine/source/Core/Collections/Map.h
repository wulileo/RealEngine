#pragma once

#include <unordered_map>

using std::unordered_map;

template<typename K, typename V>
class TMap {
public:
    void Put(K k, V v) {
        data[k] = v;
    }

    V Get(K k) {
        return data[k];
    }

    V Remove(K k) {
        return data.erase(k);
    }

    bool Contains(K k) {
        return data.count(k) > 0;
    }

    void Clear() {
        data.clear();
    }

    int Size() {
        return data.size();
    }


    typename unordered_map<K, V>::const_iterator begin() const {
        return data.cbegin();
    }

    typename unordered_map<K, V>::const_iterator end() const {
        return data.cend();
    }

private:
    unordered_map<K, V> data;
};
