#pragma once

#include "SegmentedDeque.h"
#include "exseptions.h"
#include "ICollection.h"

template<class T>
SegmentedDeque<T>::Segment::Segment(int segmentSize)
{
    if (segmentSize <= 0)
        throw InvalidArgument("Segment size must be positive");

    capacity = segmentSize;
    count = 0;
    first = 0;

    data = new DynamicArray<T>(capacity);
}

template<class T>
SegmentedDeque<T>::Segment::Segment(const Segment& other)
{
    capacity = other.capacity;
    first = other.first;
    count = other.count;

    data = new DynamicArray<T>(capacity);

    for (int i = 0; i < capacity; i++)
        data->Set(i, other.data->Get(i));
}

template<class T>
SegmentedDeque<T>::Segment::~Segment()
{
    delete data;
}

template<class T>
void SegmentedDeque<T>::Segment::MoveFirstToMid(){
    if (!IsEmpty()){
        throw InvalidArgument("Cannot move start of a non-empty segment");
    }
    first = capacity/2;
};

template<class T>
bool SegmentedDeque<T>::Segment::IsEmpty() const
{
    return count == 0;
}

template<class T>
bool SegmentedDeque<T>::Segment::IsFull() const
{
    return count == capacity;
}

template<class T>
bool SegmentedDeque<T>::Segment::CanPushFront() const
{
    return count == 0 || first > 0;
}

template<class T>
bool SegmentedDeque<T>::Segment::CanPushBack() const
{
    return count == 0 || first + count < capacity;
}

template<class T>
int SegmentedDeque<T>::Segment::GetCount() const
{
    return count;
}

template<class T>
T SegmentedDeque<T>::Segment::Get(int index) const
{
    if (index < 0 || index >= count)
        throw IndexOutOfRange();

    return data->Get(first + index);
}

template<class T>
T SegmentedDeque<T>::Segment::GetFirst() const
{
    if (IsEmpty())
        throw InvalidArgument("Segment is empty");

    return data->Get(first);
}

template<class T>
T SegmentedDeque<T>::Segment::GetLast() const
{
    if (IsEmpty())
        throw InvalidArgument("Segment is empty");

    return data->Get(first + count - 1);
}

template<class T>
void SegmentedDeque<T>::Segment::Set(T item, int index){
   if (index<0 || index>=count) throw IndexOutOfRange();

   data->Set(first + index, item);
}

template<class T>
void SegmentedDeque<T>::Segment::PushFront(T item)
{
    if (!CanPushFront())
        throw InvalidArgument("Cannot push front into segment");

    if (count == 0)
        first = capacity - 1;
    else
        first--;

    data->Set(first, item);
    count++;
}

template<class T>
void SegmentedDeque<T>::Segment::PushBack(T item)
{
    if (!CanPushBack())
        throw InvalidArgument("Cannot push back into segment");

    if (count == 0)
    {
        first = 0;
        data->Set(first, item);
    }
    else
    {
        data->Set(first + count, item);
    }

    count++;
}

template<class T>
T SegmentedDeque<T>::Segment::PopFront()
{
    if (IsEmpty())
        throw InvalidArgument("Segment is empty");

    T result = data->Get(first);
    first++;
    count--;

    return result;
}

template<class T>
T SegmentedDeque<T>::Segment::PopBack()
{
    if (IsEmpty())
        throw InvalidArgument("Segment is empty");

    T result = data->Get(first + count - 1);
    count--;

    return result;
}

template<class T>
typename SegmentedDeque<T>::Segment*
SegmentedDeque<T>::CreateSegment() const
{
    return new Segment(segmentSize);
}

template<class T>
void SegmentedDeque<T>::CreateFrontSegment() 
{
    EnsureFrontSegmentsCapacity();
    frontSegmentIndex--;
    if(segments->Get(frontSegmentIndex)==nullptr) segments->Set(CreateSegment(), frontSegmentIndex);
}

template <class T>
void SegmentedDeque<T>::CreateBackSegment(){
    EnsureBackSegmentsCapacity();
    backSegmentIndex++;
    if(segments->Get(backSegmentIndex)==nullptr) segments->Set(CreateSegment(), backSegmentIndex);
}

template<class T>
void SegmentedDeque<T>::CreateInitialSegment(){
    frontSegmentIndex = segments->GetLength()/2;
    backSegmentIndex = frontSegmentIndex;
    Segment* segment = CreateSegment();
    segment->MoveFirstToMid();
    segments = segments->Set(segment, backSegmentIndex);
}

template<class T>
Sequence<typename SegmentedDeque<T>::Segment*>*
SegmentedDeque<T>::CreateSegmentSequence(int size) const
{
    if (size <= 0)
        throw InvalidArgument("Segment map size must be positive");

    Segment** items = new Segment*[size]{};
    Sequence<Segment*>* result = nullptr;

    if (backing == Backing::Array)
        result = new MutableArraySequence<Segment*>(items, size);
    else
        result = new MutableListSequence<Segment*>(items, size);

    delete[] items;
    return result;
}

template<class T>
typename SegmentedDeque<T>::Segment*
SegmentedDeque<T>::GetFrontSegment() const
{
    if (length == 0)
        throw InvalidArgument("Deque is empty");

    return segments->Get(frontSegmentIndex);
}

template<class T>
typename SegmentedDeque<T>::Segment*
SegmentedDeque<T>::GetBackSegment() const
{
    if (length == 0)
        throw InvalidArgument("Deque is empty");

    return segments->Get(backSegmentIndex);
}

template<class T>
void SegmentedDeque<T>::EnsureSegmentsCapacity()
{
    int oldSize = segments->GetLength();
    int newSize = oldSize*2;
    Sequence<Segment*>* newSegments = CreateSegmentSequence(newSize);
    int shift = (newSize-oldSize)/2;
    
    for (int i=0; i<oldSize; i++){
        if(segments->Get(i)!=nullptr){
            newSegments=newSegments->Set(segments->Get(i), i+shift);
        }
    }
    delete segments;
    segments = newSegments;
    frontSegmentIndex +=shift;
    backSegmentIndex +=shift;
}

template<class T>
void SegmentedDeque<T>::EnsureFrontSegmentsCapacity(){
    if (segments->GetFirst()==nullptr) return;
    EnsureSegmentsCapacity();
}

template<class T>
void SegmentedDeque<T>::EnsureBackSegmentsCapacity(){
      if (segments->GetLast()==nullptr) return;
    EnsureSegmentsCapacity();
}

template<class T>
SegmentedDeque<T>::SegmentedDeque(
    int segmentSize,
    Backing backing
)
{
    if (segmentSize <= 0)
        throw InvalidArgument("Segment size must be positive");

    this->segmentSize = segmentSize;
    this->backing = backing;

    length = 0;

    segments = CreateSegmentSequence(INITIAL_SEGMENT_MAP_SIZE);

    frontSegmentIndex = segments->GetLength() / 2;
    backSegmentIndex = frontSegmentIndex;
}

template<class T>
SegmentedDeque<T>::SegmentedDeque(
    T* items,
    int count,
    int segmentSize,
    Backing backing
)
    : SegmentedDeque(segmentSize, backing)
{
    if (count < 0)
        throw InvalidArgument("Count cannot be negative");

    if (items == nullptr && count > 0)
        throw InvalidArgument("Items cannot be null");

    for (int i = 0; i < count; i++)
        PushBack(items[i]);
}

template<class T>
SegmentedDeque<T>::SegmentedDeque(
    const SegmentedDeque<T>& other
)
{
    segmentSize = other.segmentSize;
    backing = other.backing;
    length = other.length;

    frontSegmentIndex = other.frontSegmentIndex;
    backSegmentIndex = other.backSegmentIndex;

    int mapSize = other.segments->GetLength();
    segments = CreateSegmentSequence(mapSize);

    for (int i = 0; i < mapSize; i++)
    {
        Segment* segment = other.segments->Get(i);

        if (segment != nullptr)
            segments = segments->Set(new Segment(*segment), i);
    }
}

template<class T>
SegmentedDeque<T>::~SegmentedDeque()
{
    if (segments == nullptr)
        return;

    for (int i = 0; i < segments->GetLength(); i++)
    {
        Segment* segment = segments->Get(i);

        if (segment != nullptr)
            delete segment;
    }

    delete segments;
}

template<class T>
void SegmentedDeque<T>::PushFront(T item)
{
    Segment* segment = segments->Get(frontSegmentIndex);
    if (length==0){
        if (segment == nullptr){
            CreateInitialSegment();
            segment = segments->Get(frontSegmentIndex);
            segment->PushFront(item);
            length++;
            return;
        }
        segment->MoveFirstToMid();
    }
    if(segment->CanPushFront()){
        segment->PushFront(item);
        length++;
        return;
    }
    CreateFrontSegment();
    segment = segments->Get(frontSegmentIndex);
    segment->PushFront(item);
    length++;
    
}

template<class T>
void SegmentedDeque<T>::PushBack(T item)
{
    Segment* segment = segments->Get(backSegmentIndex);
    if (length==0){
        if(segment==nullptr){
            CreateInitialSegment();
            segment = segments->Get(backSegmentIndex);
            segment->PushBack(item);
            length++;
            return;
        }
        segment->MoveFirstToMid();
    }
    if (segment->CanPushBack()){
        segment->PushBack(item);
        length++;
        return;
    }
    CreateBackSegment();
    segment = segments->Get(backSegmentIndex);
    segment->PushBack(item);
    length++;
}

template<class T>
T SegmentedDeque<T>::PopFront()
{
    if (length == 0)
        throw InvalidArgument("Deque is empty");

    Segment* firstSegment = segments->Get(frontSegmentIndex);
    T result = firstSegment->PopFront(); 
    length --;
    if (length == 0) frontSegmentIndex=backSegmentIndex;
    else if (firstSegment->IsEmpty()) frontSegmentIndex++;
    return result;
}

template<class T>
T SegmentedDeque<T>::PopBack()
{
    if (length == 0)
        throw InvalidArgument("Deque is empty");

    Segment* lastSegment = GetBackSegment();
    T result = lastSegment->PopBack();
    length--;
    if (length==0) frontSegmentIndex=backSegmentIndex;
    else if(lastSegment->IsEmpty()) backSegmentIndex--;
    return result;
}

template<class T>
T SegmentedDeque<T>::GetFirst() const
{
    return GetFrontSegment()->GetFirst();
}

template<class T>
T SegmentedDeque<T>::GetLast() const
{
    return GetBackSegment()->GetLast();
}

template<class T>
T SegmentedDeque<T>::Get(int index) const
{
    if (index < 0 || index >= length)
        throw IndexOutOfRange();

    Segment* frontSegment = GetFrontSegment();
    if (index < frontSegment->GetCount()) return frontSegment->Get(index);
    index = index - frontSegment->GetCount();
    int segmentIndex = frontSegmentIndex + index / segmentSize + 1;
    int getIndex = index % segmentSize;
    return segments->Get(segmentIndex)->Get(getIndex);

}

template<class T>
void SegmentedDeque<T>::Set(T item, int index){
    if (index < 0 || index >= length) throw IndexOutOfRange(); 
    
    Segment* frontSegment = GetFrontSegment();
    if (index < frontSegment->GetCount()){
        frontSegment->Set(item, index);
        return;
    }
    index -= frontSegment->GetCount();
    int setSegmentIndex = frontSegmentIndex + index/segmentSize + 1;
    int setIndex = index % segmentSize; 
    Segment* segment = segments->Get(setSegmentIndex);
    segment->Set(item, setIndex);
}

template<class T>
int SegmentedDeque<T>::GetLength() const
{
    return length;
}

template<class T>
bool SegmentedDeque<T>::IsEmpty() const
{
    return length == 0;
}

template<class T>
SegmentedDeque<T>*
SegmentedDeque<T>::Concat(
    const ICollection<T>& other
) const
{
   SegmentedDeque<T>* result = new SegmentedDeque<T>(*this);
   for (int i=0; i<other.GetCount(); i++)
      result->PushBack(other.Get(i));
   
   return result;
}

template<class T>
SegmentedDeque<T>*
SegmentedDeque<T>::GetSubsequence(
    int startIndex,
    int endIndex
) const
{
    if (startIndex < 0 || endIndex < startIndex || endIndex >= length)
        throw IndexOutOfRange();

    SegmentedDeque<T>* result =
        new SegmentedDeque<T>(segmentSize, backing);

    for (int i = startIndex; i <= endIndex; i++)
        result->PushBack(Get(i));

    return result;
}

template<class T>
SegmentedDeque<T>*
SegmentedDeque<T>::Map(
    T (*function)(T)
) const
{
    if (function == nullptr)
        throw InvalidArgument("Function cannot be null");

    SegmentedDeque<T>* result =
        new SegmentedDeque<T>(segmentSize, backing);

    for (int i = 0; i < length; i++)
        result->PushBack(function(Get(i)));

    return result;
}

template<class T>
SegmentedDeque<T>*
SegmentedDeque<T>::Where(
    bool (*predicate)(T)
) const
{
    if (predicate == nullptr)
        throw InvalidArgument("Predicate cannot be null");

    SegmentedDeque<T>* result =
        new SegmentedDeque<T>(segmentSize, backing);

    for (int i = 0; i < length; i++)
    {
        T item = Get(i);

        if (predicate(item))
            result->PushBack(item);
    }

    return result;
}

template<class T>
T SegmentedDeque<T>::Reduce(
    T (*function)(T, T),
    T initial
) const
{
    if (function == nullptr)
        throw InvalidArgument("Function cannot be null");

    T result = initial;

    for (int i = 0; i < length; i++)
        result = function(Get(i), result);

    return result;
}

template<class T>
SegmentedDeque<T>* 
SegmentedDeque<T>::Sort(
    bool (*compare)(T, T)
) const
{ 
        if (compare == nullptr)
        throw InvalidArgument("Function cannot be null");

        SegmentedDeque<T>* result = new SegmentedDeque<T>(*this);
        for (int i = 0; i<length-1; i++){
            for(int j=0; j<length-1-i; j++){
                if(compare(result->Get(j+1), result->Get(j))){
                    T copy = result->Get(j+1);
                    
                    result->Set(result->Get(j), j+1);
                    result->Set(copy, j);
                    }
            }
        }
        return result;
}

template<class T>
int SegmentedDeque<T>::FindSubsequence(const ICollection<T>& subsequence) const{
    int count = subsequence.GetCount();
    if (count == 0) return 0;
    
    for (int i = 0;i <= length - count; i++){
        if (Get(i)==subsequence.Get(0)){
            int f=1;
            for(int j=i+1; j<i+count; j++){
                if(Get(j)!=subsequence.Get(f)) break;
                f++;
            }
            if (f==count) return i;
        }
    }
    return -1;
}

template<class T> 
SegmentedDeque<T>* SegmentedDeque<T>::Merge(
    const ICollection<T>& other,
    bool (*compare)(T, T)
)const{
    if (compare == nullptr)   throw InvalidArgument("Function cannot be null");
    
    SegmentedDeque<T>* temp = Concat(other);
    SegmentedDeque<T>* result = temp->Sort(compare);
    delete temp;
    return result;
}

template<class T>
T SegmentedDeque<T>::operator[](int index) const
{
  return Get(index);
}

template<class T>
bool SegmentedDeque<T>::operator==(const SegmentedDeque<T>& other) const
{
    if(length == other.GetLength()){
        for (int i = 0; i<length; i++){
            if (Get(i)!=other.Get(i)) return false;
        }
        return true;
    }
    return false;
}

template<class T>
bool SegmentedDeque<T>::operator!=(const SegmentedDeque<T>& other) const{
    return !(*this==other);
}

template<class T> 
SegmentedDeque<T>& SegmentedDeque<T>::operator=(const SegmentedDeque<T>& other)
{
    if(this==&other) return *this;

    for (int i = 0; i < segments->GetLength(); i++)
    {
    delete segments->Get(i);
    }

    delete segments;
    
    segmentSize = other.segmentSize;
    backing = other.backing;
    segments = CreateSegmentSequence(other.segments->GetLength());
    frontSegmentIndex = other.frontSegmentIndex;
    backSegmentIndex = other.backSegmentIndex;
    length=other.length;
    for(int i=0; i < other.segments->GetLength(); i++){
        Segment* oldSegment = other.segments->Get(i);

        if (oldSegment != nullptr)
        {
            Segment* newSegment = new Segment(*oldSegment);
            segments->Set(newSegment, i);
        }
    }
    return *this;

}
