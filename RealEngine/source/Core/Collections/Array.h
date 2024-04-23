#pragma once

#include <type_traits>
#include <vector>

using std::is_convertible;
using std::vector;

template<typename T>
class TArray {
public:
    void Add(T t) {
        data.push_back(t);
    }

    T Remove() {
        return data.pop_back();
    }

    T Remove(int Index) {
        return data.erase(Index);
    }

    void Clear() {
        data.clear();
    }

    int Size() {
        return data.size();
    }

private:
    vector<T> data;
};
