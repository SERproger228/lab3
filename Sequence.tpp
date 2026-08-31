#pragma once

#include "exseptions.h"
#include "Sequence.h"

template<class T>
Sequence<T>* Sequence<T>::Map(T (*f)(T)) const{
    if (f == nullptr) throw InvalidArgument("Map(): function is null");
    Sequence<T>* result = EmptyClone();
    for(int i = 0; i < GetLength(); i++) result->AppendInternal(f(Get(i)));
return result;
};

template<class T>
Sequence<T>* Sequence<T>::Where(bool (*f)(T)) const{
    if (f == nullptr) throw InvalidArgument("Where(): function is null");
    Sequence<T>* result = EmptyClone();
    for(int i = 0; i < GetLength(); i++) if(f(Get(i)))(result->AppendInternal(Get(i)));
    return result;
};

template<class T>
T Sequence<T>::Reduce(T (*f)(T,T), T initial) const{
    if (f == nullptr) throw InvalidArgument("Reduce(): function is null");
    T result = initial;
    for(int i = 0; i<GetLength(); i++)(result = f(result,Get(i)));
    return result;
};
