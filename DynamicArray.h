#pragma once

#include "exseptions.h"

template<class T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    DynamicArray(T* items, int count);
    DynamicArray(int sz);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();

    T Get(int index) const;
    int GetSize();
    void Resize(int newSize);
    void Set(int index, T value);
};

#include "DynamicArray.cpp"
