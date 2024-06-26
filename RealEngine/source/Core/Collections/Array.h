﻿#pragma once

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

    T Get(int Index) {
        return data[Index];
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

    bool IsEmpty() {
        return Size() <= 0;
    }

    void Sort(std::function<bool(T, T)> SortFunc) {
        std::sort(data.begin(), data.end(), SortFunc);
    }

    typename vector<T>::const_iterator begin() const {
        return data.cbegin();
    }

    typename vector<T>::const_iterator end() const {
        return data.cend();
    }

private:
    vector<T> data;
};
