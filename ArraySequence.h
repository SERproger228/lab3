#pragma once

#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

template<class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> items;
    int size;

    void assureCapacity(int needed);

    void AppendInternal(T item) override;
    void PrependInternal(T item) override;
    void InsertAtInternal(T item, int index) override;
    void SetInternal(T item, int index) override;
    Sequence<T>* EmptyClone() const override;

public:
    ArraySequence();
    ArraySequence(T* data, int count);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(const LinkedList<T>& list);
    ~ArraySequence() override = default;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;

    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;
    Sequence<T>* Set(T item, int index) override;
    Sequence<T>* Concat(Sequence<T>* other) override;
};

template<class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* Instance() override { return this; }
    Sequence<T>* Clone() const override { return new MutableArraySequence<T>(*this); }

public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* data, int count) : ArraySequence<T>(data, count) {}
    MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
};

template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* Instance() override { return new ImmutableArraySequence<T>(*this); }
    Sequence<T>* Clone() const override { return new ImmutableArraySequence<T>(*this); }

public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* data, int count) : ArraySequence<T>(data, count) {}
    ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
};

#include "ArraySequence.tpp"
