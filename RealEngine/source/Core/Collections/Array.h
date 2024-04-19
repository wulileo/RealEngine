#pragma once

#include <type_traits>
#include <vector>

using std::is_same;
using std::vector;

class UObject;

template<typename T>
class TArray {
    static_assert(is_same<T, UObject *>::value, "Template parameter T must be of type Object*");

public:
    void Add(T);

    T Remove();

    T Remove(int Index);

    void Clear();

private:
    vector<T> data;
};