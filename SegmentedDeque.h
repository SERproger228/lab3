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
class SegmentedDeque : public ICollection<T>
{
    friend class SegmentedDequeTestAccess<T>;

private:

    static const int INITIAL_SEGMENT_MAP_SIZE = 3;

    class Segment
    {
    private:
        DynamicArray<T>* data;

        int first;
        int count;
        int capacity;
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

        T Get(int index) const;

        T GetFirst() const;
        T GetLast() const;

        void Set(T item, int index);

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

    T Get(int index) const override;
    
    void Set(T item, int index);


    int GetLength() const;
    int GetCount() const override { return GetLength(); }

    bool IsEmpty() const;


    SegmentedDeque<T>* Concat(
        const ICollection<T>& other
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
       const ICollection<T>& subsequence
    ) const;

    SegmentedDeque<T>* Merge(
      const ICollection<T>& other,
      bool (*compare)(T, T)
    ) const;

    T operator[](int index) const;
    bool operator==(const SegmentedDeque<T>& other) const;
    bool operator!=(const SegmentedDeque<T>& other) const;
    SegmentedDeque<T>& operator=(const SegmentedDeque<T>& other);
};


#include "SegmentedDeque.tpp"
