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
        return data.find(k);
    }

    V Remove(K k) {
        return data.erase(k);
    }

    void Clear() {
        data.clear();
    }

    int Size() {
        return data.size();
    }

private:
    unordered_map<K, V> data;
};
