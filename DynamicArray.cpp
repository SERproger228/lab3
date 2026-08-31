#pragma once

#include "DynamicArray.h"
#include "exseptions.h"

template<class T> 
DynamicArray<T>::DynamicArray(T* items, int count)
: size(count){
    if (count < 0) throw InvalidArgument("Count cannot be negative");
    if (items == nullptr && count > 0) throw InvalidArgument("Items cannot be null when count is positive");
    data = size > 0 ? new T[size] : nullptr;
    for (int i=0; i<count; i++) data[i]=items[i];
};

template<class T>
DynamicArray<T>::DynamicArray(int sz)
: size(sz){
    if(sz<0) throw InvalidArgument("Count cannot be negative");
    data = new T[size]{};
};

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
: size(other.size){
    data = size > 0 ? new T[size] : nullptr;
    for (int i = 0; i<size; i++) data[i] = other.data[i];
};

template<class T>
DynamicArray<T>:: ~DynamicArray(){delete[] data;};

template<class T>
T DynamicArray<T>:: Get(int index) const{
    if (index > size-1 || index < 0) throw IndexOutOfRange("Get(): index out of range");
    return(data[index]);
};

template<class T>
int DynamicArray<T>:: GetSize(){
    return(size);
};

template<class T>
void DynamicArray<T>:: Resize(int newSize){
   if (newSize<0) throw InvalidArgument("Set(): Size < 0");

   int copySize = newSize>size ? size : newSize;
   T* newData = new T[newSize]{};
   for (int i=0;i<copySize;i++) newData[i]=data[i];
   size = newSize;
   delete[] data;
   data = newData;
};

template<class T>
void DynamicArray<T>:: Set(int index, T value){
    if (index > size-1 || index < 0) throw IndexOutOfRange("Set(): index out of range");
    data[index]=value;
};
