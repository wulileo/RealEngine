#include "Array.h"

template<typename T>
void TArray<T>::Add(T object) {
    data.push_back(object);
}

template<typename T>
T TArray<T>::Remove() {
    return data.pop_back();
}

template<typename T>
T TArray<T>::Remove(int Index) {
    return data.erase(Index);
}

template<typename T>
void TArray<T>::Clear() {
    data.clear();
}