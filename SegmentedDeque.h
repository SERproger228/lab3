#pragma once

#include "exseptions.h"
#include "Sequence.h"
#include "DynamicArray.h"
#include "ArraySequence.h"
#include "ListSequence.h"

enum class Backing
{
    Array,
    List
};

template<class T>
class SegmentedDequeTestAccess;

template<class T>
class SegmentedDeque
{
    friend class SegmentedDequeTestAccess<T>;

private:

    static const int INITIAL_SEGMENT_MAP_SIZE = 3;

    class Segment
    {
        friend class SegmentedDequeTestAccess<T>;

    private:
        DynamicArray<T>* data;

        int first;
        int count;
        int capacity;
        bool firstPrepared;
   public:
        explicit Segment(int segmentSize);

        Segment(const Segment& other);

        ~Segment();

        bool IsEmpty() const;
        bool IsFull() const;

        bool CanPushFront() const;
        bool CanPushBack() const;

        int GetCount() const;

        void MoveFirstToMid();

        T At(int index) const;

        T GetFirst() const;
        T GetLast() const;

        void Put(T item, int index);

        void PushFront(T item);
        void PushBack(T item);

        T PopFront();
        T PopBack();
    };


    Sequence<Segment*>* segments;

    int frontSegmentIndex;
    int backSegmentIndex;

    int length;

    int segmentSize;

    Backing backing;

    Segment* CreateSegment() const;
    void CreateBackSegment();
    void CreateFrontSegment();
    void CreateInitialSegment();

    Sequence<Segment*>* CreateSegmentSequence(
        int size
    ) const;

    Segment* GetFrontSegment() const;
    Segment* GetBackSegment() const;

    void EnsureSegmentsCapacity();
    void EnsureFrontSegmentsCapacity();
    void EnsureBackSegmentsCapacity();

    T GetItem(int index) const;
    void SetItem(T item, int index);

public:

    explicit SegmentedDeque(
        int segmentSize = 4,
        Backing backing = Backing::Array
    );


    SegmentedDeque(
        T* items,
        int count,
        int segmentSize = 4,
        Backing backing = Backing::Array
    );


    SegmentedDeque(
        const SegmentedDeque<T>& other
    );


    ~SegmentedDeque();


    void PushFront(T item);
    void PushBack(T item);

    T PopFront();
    T PopBack();


    T GetFirst() const;
    T GetLast() const;

    int GetLength() const;
    int GetCount() const { return GetLength(); }

    bool IsEmpty() const;


    SegmentedDeque<T>* Concat(
        const SegmentedDeque<T>& other
    ) const;


    SegmentedDeque<T>* GetSubsequence(
        int startIndex,
        int endIndex
    ) const;


    SegmentedDeque<T>* Map(
        T (*function)(T)
    ) const;


    SegmentedDeque<T>* Where(
        bool (*predicate)(T)
    ) const;


    T Reduce(
        T (*function)(T, T),
        T initial
    ) const;

    SegmentedDeque<T>* Sort(
        bool (*compare)(T, T)
    ) const;

    int FindSubsequence(
       const SegmentedDeque<T>& subsequence
    ) const;

    SegmentedDeque<T>* Merge(
      const SegmentedDeque<T>& other,
      bool (*compare)(T, T)
    ) const;

    bool operator==(const SegmentedDeque<T>& other) const;
    bool operator!=(const SegmentedDeque<T>& other) const;
    SegmentedDeque<T>& operator=(const SegmentedDeque<T>& other);
};


#include "SegmentedDeque.tpp"
