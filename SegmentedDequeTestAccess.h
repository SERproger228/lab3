#pragma once

#include "SegmentedDeque.h"

template<class T>
class SegmentedDequeTestAccess
{
public:

    static int GetSegmentMapSize(
        const SegmentedDeque<T>& deque
    )
    {
        return deque.segments->GetLength();
    }

    static int GetFrontSegmentIndex(
        const SegmentedDeque<T>& deque
    )
    {
        return deque.frontSegmentIndex;
    }

    static int GetBackSegmentIndex(
        const SegmentedDeque<T>& deque
    )
    {
        return deque.backSegmentIndex;
    }

    static int GetSegmentSize(
        const SegmentedDeque<T>& deque
    )
    {
        return deque.segmentSize;
    }

    static int GetLength(
        const SegmentedDeque<T>& deque
    )
    {
        return deque.length;
    }

    static bool HasSegmentAt(
        const SegmentedDeque<T>& deque,
        int index
    )
    {
        return deque.segments->Get(index) != nullptr;
    }

    static int GetSegmentFirst(
        const SegmentedDeque<T>& deque,
        int index
    )
    {
        return deque.segments->Get(index)->first;
    }

    static int GetSegmentCount(
        const SegmentedDeque<T>& deque,
        int index
    )
    {
        return deque.segments->Get(index)->count;
    }

    static T GetItem(
        const SegmentedDeque<T>& deque,
        int index
    )
    {
        return deque.GetItem(index);
    }
};
