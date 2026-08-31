#pragma once
#include "exseptions.h"
#include "ICollection.h"

template<class T>
class MutableArraySequence;

template<class T>
class Sequence : public ICollection<T>{
protected:

    virtual Sequence<T>* Instance() = 0;

    virtual Sequence<T>* Clone() const = 0;


    virtual Sequence<T>* EmptyClone() const = 0;

    virtual void AppendInternal(T item) = 0;
    virtual void PrependInternal(T item) = 0;
    virtual void InsertAtInternal(T item, int index) = 0;
    virtual void SetInternal(T item, int index) = 0;

public:
    virtual ~Sequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;
    virtual int GetCount() const override{
        return GetLength();
    }

    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Set(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) = 0;

    Sequence<T>* Map(T (*f)(T)) const;
    Sequence<T>* Where(bool (*f)(T)) const;
    T Reduce(T (*f)(T, T), T initial) const;
};

template<class T1, class T2>
class Pair{
    public:
    T1 first;
    T2 second;

    Pair(const T1& first, const T2& second): first(first), second(second){};
};


template<class T1, class T2>
class ZipSequence {
    Sequence<Pair<T1, T2>>* ZipInternal(Sequence<T1>& first, Sequence<T2>& second){
        int minLength= first.GetLength()<second.GetLength() ? first.GetLength() : second.GetLength();
        Sequence<Pair<T1,T2>>* result = new MutableArraySequence<Pair<T1,T2>>();
        for(int i=0; i<minLength; i++){
            result->Append(Pair<T1,T2>(first.Get(i), second.Get(i)));
        }
        return result;
    };
    Pair<Sequence<T1>*, Sequence<T2>*>* Unzip(Sequence<Pair<T1, T2>>& zipseq){
        Sequence<T1>* first = new MutableArraySequence<T1>();
        Sequence<T2>* second = new MutableArraySequence<T2>();
        for(int i=0; i<zipseq.GetLength(); i++){
            Pair<T1,T2> item = zipseq.Get(i);
            first->Append(item.first);
            second->Append(item.second);
        }
        return new Pair<Sequence<T1>*, Sequence<T2>*>(first, second);
    };
};

#include "Sequence.tpp"
