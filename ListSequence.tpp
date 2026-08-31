#include "ListSequence.h"
#include "exseptions.h"

template<class T>
T ListSequence<T>::GetFirst() const{
  return list.GetFirst();
};

template<class T>
T ListSequence<T>::GetLast() const{
  return list.GetLast();
};

template<class T>
T ListSequence<T>::Get(int index) const{
  return list.Get(index);
};

template<class T>
int ListSequence<T>::GetLength() const{
    return list.GetLenght();
};

template<class T>
Sequence<T>* ListSequence<T>::EmptyClone() const{
  return new MutableListSequence<T>();
};

template<class T> 
Sequence<T>* ListSequence<T>::Append(T item){
  ListSequence<T>* inst = static_cast<ListSequence<T>*>(this->Instance());
  inst->AppendInternal(item);
  return inst;
};

template<class T> 
Sequence<T>* ListSequence<T>::Prepend(T item){
  ListSequence<T>* inst = static_cast<ListSequence<T>*>(this->Instance());
  inst->PrependInternal(item);
  return inst;
};

template<class T> 
Sequence<T>* ListSequence<T>::InsertAt(T item, int index){
  ListSequence<T>* inst = static_cast<ListSequence<T>*>(this->Instance());
  inst->InsertAtInternal(item, index);
  return inst;
};

template<class T>
Sequence<T>* ListSequence<T>::Set(T item, int index){
  ListSequence<T>* inst = static_cast<ListSequence<T>*>(this->Instance());
  inst->list.Set(index, item);
  return inst;
};

template<class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const{
  return new MutableListSequence<T>(*list.GetSubList(startIndex, endIndex));
};

template<class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* other){
  ListSequence<T>* result = static_cast<ListSequence<T>*>(this->Instance());
  for(int i = 0; i < other->GetLength(); i++) result->AppendInternal(other->Get(i));
  return result;
};
