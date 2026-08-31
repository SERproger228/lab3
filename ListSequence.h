#pragma once

#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> list;

    void AppendInternal(T item) override { list.append(item); }
    void PrependInternal(T item) override { list.prepend(item); }
    void InsertAtInternal(T item, int index) override { list.insertAt(item, index); }
    void SetInternal(T item, int index) override { list.Set(index, item); }
    Sequence<T>* EmptyClone() const override;

public:
    ListSequence() : list() {}
    ListSequence(T* data, int count) : list(data, count) {}
    ListSequence(const ListSequence<T>& other) : list(other.list) {}
    ListSequence(const LinkedList<T>& source) : list(source) {}
    ~ListSequence() override = default;

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
class MutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* Instance() override { return this; }
    Sequence<T>* Clone() const override { return new MutableListSequence<T>(*this); }

public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* data, int count) : ListSequence<T>(data, count) {}
    MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
    MutableListSequence(const LinkedList<T>& source) : ListSequence<T>(source) {}
};

template<class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* Instance() override { return new ImmutableListSequence<T>(*this); }
    Sequence<T>* Clone() const override { return new ImmutableListSequence<T>(*this); }

public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* data, int count) : ListSequence<T>(data, count) {}
    ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
    ImmutableListSequence(const LinkedList<T>& source) : ListSequence<T>(source) {}
};

#include "ListSequence.tpp"
