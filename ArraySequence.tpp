#include "ArraySequence.h"
#include "exseptions.h"

template<class T>
ArraySequence<T>::ArraySequence(): items(0), size(0){};

template<class T>
ArraySequence<T>::ArraySequence(T* data, int count): items(data, count), size(count){};

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other): items(other.items), size(other.size){};

template<class T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list): items(list.GetLenght()), size(0) {
    int listLength = list.GetLenght();
    for(int i=0; i<listLength; i++){
       AppendInternal(list.Get(i));
    };
};

template<class T>
void ArraySequence<T>::assureCapacity(int needed){
    int capacity = items.GetSize();
    if(capacity>=needed) return;
    int newCapacity=capacity==0 ? 1 : capacity;
    while(newCapacity<needed) newCapacity*=2;
    items.Resize(newCapacity);
};

template<class T>
T ArraySequence<T>::GetFirst() const{
    if (size == 0) throw IndexOutOfRange("GetFirst(): sequence is empty");
    return items.Get(0);
};

template<class T>
T ArraySequence<T>::GetLast() const{
    if (size == 0) throw IndexOutOfRange("GetLast(): sequence is empty");
    return items.Get(size-1);
};

template<class T>
T ArraySequence<T>::Get(int index) const{
    if (index < 0 || index >= size) throw IndexOutOfRange("Get(): index out of range");
    return items.Get(index);
};

template<class T>
int ArraySequence<T>::GetLength() const{
    return size;
};

template<class T>
void ArraySequence<T>::AppendInternal(T item){
    assureCapacity(size + 1);
    items.Set(size, item);
    size+=1;
};

template<class T>
void ArraySequence<T>::PrependInternal(T item){
    assureCapacity(size + 1);
    for (int i=size; i>0; i--)items.Set(i, items.Get(i-1));
    items.Set(0, item);
    size+=1;
};

template<class T>
void ArraySequence<T>::InsertAtInternal(T item, int index){
    if (index < 0 || index > size) throw IndexOutOfRange("InsertAt(): index out of range");
    assureCapacity(size + 1);
    for (int i=size; i>index; i--)items.Set(i, items.Get(i-1));
    items.Set(index, item);
    size+=1;
};

template<class T>
void ArraySequence<T>::SetInternal(T item, int index){
    if (index < 0 || index >= size) throw IndexOutOfRange("Set(): index out of range");
    items.Set(index, item);
};

template<class T> 
Sequence<T>* ArraySequence<T>::EmptyClone() const{
    return new MutableArraySequence<T>();
};

template<class T>
Sequence<T>* ArraySequence<T>::Append(T item){
    ArraySequence<T>* inst = static_cast<ArraySequence<T>*>(this->Instance());
    inst->AppendInternal(item);
    return inst;
};

template<class T>
Sequence<T>* ArraySequence<T>::Prepend(T item){
   ArraySequence<T>* inst = static_cast<ArraySequence<T>*>(this->Instance());
   inst->PrependInternal(item);
   return inst;
};

template<class T>
Sequence<T>* ArraySequence<T>::InsertAt(T item, int index){
    ArraySequence<T>* inst = static_cast<ArraySequence<T>*>(this->Instance());
    inst->InsertAtInternal(item, index);
    return inst;
};

template<class T>
Sequence<T>* ArraySequence<T>::Set(T item, int index){
    ArraySequence<T>* inst = static_cast<ArraySequence<T>*>(this->Instance());
    inst->SetInternal(item, index);
    return inst;
};

template<class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* other){
    if (other == nullptr) throw InvalidArgument("Concat(): other sequence is null");
    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->Instance());
    for(int i=0; i<other->GetLength();i++){
        result->AppendInternal(other->Get(i));
    };
return result;
};

template<class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const{
    if (startIndex < 0 || endIndex < startIndex || endIndex >= size)
        throw IndexOutOfRange("GetSubsequence(): index out of range");
    ArraySequence<T>* result = new MutableArraySequence<T>();
    for(int i = startIndex; i<=endIndex; i++){
        result->AppendInternal(Get(i));
    };
    return result;
};
