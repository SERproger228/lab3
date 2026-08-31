#ifndef INVERSIONS_H
#define INVERSIONS_H

#include "ICollection.h"
#include "ArraySequence.h"


template<class T>
int CountInversions(
    const ICollection<T>& collection,
    bool (*compare)(T, T)
);

#include "Inversion.tpp"

#endif
