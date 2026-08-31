#include <iostream>
#include "Tests.h"
#include "SegmentedDeque.h"
#include "SegmentedDequeTestAccess.h"

int TestDoubleValue(int value){
    return value * 2;
}

bool TestIsEven(int value){
    return value % 2 == 0;
}

int TestSum(int left, int right){
    return left + right;
}

bool TestLess(int left, int right){
    return left < right;
}

bool Check(bool condition, const char* testName){
    if(condition){
        std::cout << testName << ": COMPLETED\n";
        return true;
    }
    std::cout << testName << ": FAILED\n";
    return false;
};

bool DequeEqualsItems(const SegmentedDeque<int>& deque, const int* items, int count){
    if (deque.GetLength() != count)
        return false;

    SegmentedDeque<int> copy(deque);
    for (int i = 0; i < count; i++){
        if (copy.PopFront() != items[i])
            return false;
    }
    return copy.IsEmpty();
}

void TestPushBack(){
    SegmentedDeque<int> deque(2);
    int expected[] = {1, 2, 3};

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);

    Check(deque.GetLength() == 3, "TestPushBack length");
    Check(DequeEqualsItems(deque, expected, 3), "TestPushBack order");
}

void TestPushFront(){
    
    SegmentedDeque<int> deque(2);
    int expected[] = {3, 2, 1};

    deque.PushFront(1);
    deque.PushFront(2);
    deque.PushFront(3);

    Check(deque.GetLength() == 3, "TestPushFront length");
    Check(DequeEqualsItems(deque, expected, 3), "TestPushFront order");
}

void TestPopBack(){

    int items[] = {1,2,3,4,5};
    int expected[] = {1,2};
    SegmentedDeque<int> deque(items, 5, 2);

    int firsPop = deque.PopBack();
    int secondPop = deque.PopBack();
    int thirdPop = deque.PopBack();

    Check(deque.GetLength()==2, "TestPopBack lenght");
    Check(DequeEqualsItems(deque, expected, 2), "TestPopBack order");
    Check(firsPop==5, "TestPopBack firstPop");
    Check(secondPop==4, "TestPopBack secondPop");
    Check(thirdPop==3, "TestPopBack thirdPop");
}

void TestPopFront(){
    int items[] = {1,2,3,4,5};
    int expected[] = {4,5};
    SegmentedDeque<int> deque(items, 5, 2);

    int firsPop = deque.PopFront();
    int secondPop = deque.PopFront();
    int thirdPop = deque.PopFront();

    Check(deque.GetLength()==2, "TestPopFront lenght");
    Check(DequeEqualsItems(deque, expected, 2), "TestPopFront order");
    Check(firsPop==1, "TestPopFront firstPop");
    Check(secondPop==2, "TestPopFront secondPop");
    Check(thirdPop==3, "TestPopFront thirdPop");
    
}

void TestPopFrontEmpty(){
    SegmentedDeque<int> deque(2);

    bool thrown = false;

    try{
        deque.PopFront();
    }
    catch(const InvalidArgument&){
        thrown=true;
    }
    
    Check(thrown, "TestPopFrontEmpty");
}

void TestPopBackEmpty(){
    SegmentedDeque<int> deque(2);

    bool thrown = false;

    try{
        deque.PopBack();
    }
    catch(const InvalidArgument&){
        thrown=true;
    }
    Check(thrown, "TestPopBackEmpty");

}

void TestCopyConstructor()
{
int item[]={1,2,3,4,5};
SegmentedDeque<int> original(item, 5, 2);
SegmentedDeque<int> copy(original);
Check(copy==original, "TestCopyConstructor check copy");
copy.PushBack(13);
Check(copy.GetLength()!=original.GetLength(), "TestCopyConstructor copy changes independently");
}

void TestAssignmentOperator(){
    int a[]= {1,2,3};
    int b[]={4,5,6,7,8};
    SegmentedDeque<int> original(a, 3, 2);
    SegmentedDeque<int> copy(b, 5, 3);

    copy=original;
    Check(copy==original, "TestAssignmentOperator correct copy");
    copy.PushBack(99);
    Check(copy.GetLength()!=original.GetLength(), "TestAssignmentOperator copy changes independently");

}

void TestsConcat(){
    int a[] = {1,2};
    int b[] = {3,4};
    int c[] = {1,2,3,4};
    int d[] = {1,2,3,4,3,4};

    SegmentedDeque<int> A(a, 2, 2);
    SegmentedDeque<int> B(b, 2);
    SegmentedDeque<int> C(2);
    SegmentedDeque<int> reference(c, 4, 2);
    SegmentedDeque<int> reference2(d, 6, 2);

    SegmentedDeque<int>* result = A.Concat(B);
    Check(result->GetLength()==4, "TestsConcat concatLenght");
    Check(*result==reference, "TestsConcat itemsCheck");

    SegmentedDeque<int>* result2 =  result->Concat(B);
    Check(*result2==reference2, "TestsConcat double concat");

    delete result;
    
    result = result2->Concat(C);
    Check(*result==reference2, "TestsConcat Empty concat");

    delete result2;
    delete result;
}


void TestFindSubsequence(){
    int item[] = {1,2,3,2, 3, 0};
    int seq[] = {2,3};
    int seq1[] = {7,7};

    SegmentedDeque<int> deque = SegmentedDeque<int>(item, 6, 2);
    SegmentedDeque<int> subSeq = SegmentedDeque<int>(seq, 2, 2);
    SegmentedDeque<int> subSeq1 = SegmentedDeque<int>(seq1,2,2);
    
    int result = deque.FindSubsequence(subSeq);
    int result1= deque.FindSubsequence(subSeq1);


    Check(result==1, "TestSubsequence");
    Check(result1==-1, "TestSebsequence -1");

}

void TestConcatSubSequence(){
    int item[] = {1,2,3,4,5,6,7,8};
    int reference[] = {1,2,3,4,5,6,7,8,3,4,5};

    SegmentedDeque<int> deque = SegmentedDeque<int>(item, 8, 3);
    SegmentedDeque<int> refDeque = SegmentedDeque<int>(reference, 11, 3);

    SegmentedDeque<int>* SubDeque = deque.GetSubsequence(2,4);
    SegmentedDeque<int>* result = deque.Concat(*SubDeque);

    Check(*result==refDeque, "TestConcatSubSequence");

    delete SubDeque;
    delete result;
}

void TestCompexChain(){
    int a[] = {1,2,3,4,5};
    int b[] = {6,7,8};
    int c[] = {1,2,3,4,5,6,7,8};
    int d[] = {3,4,5,6};
    int e[] = {3,4,5,6,99,1,2,3,4,5};

    SegmentedDeque<int> cRef(c,8,2);
    SegmentedDeque<int> dRef(d, 4, 2);
    SegmentedDeque<int> eRef(e,10,2);


    
    SegmentedDeque<int> A(a, 5, 2);
    SegmentedDeque<int> B(b, 3, 2);

    SegmentedDeque<int>* C = A.Concat(B);
    Check(*C==cRef, "TestComplexChain A.concat(B)");

    SegmentedDeque<int>* D = C->GetSubsequence(2, 5);
    Check(*D==dRef, "TestComplexChain GetSubsequence");

    D->PushBack(99);
    Check(*C==cRef, "TestComplexChain source unchanged after D modification");
    Check(*D!=dRef, "TestComplexChain D modified independently");

    
    SegmentedDeque<int>* E = D->Concat(A);
    Check(*E==eRef, "TestComplexChain D->concat(A)");

    delete C;
    delete D;
    delete E;
}

void TestMapWhereReduce(){
    int item[] = {1,2,3,4,5};
    int mappedItems[] = {2,4,6,8,10};
    int filteredItems[] = {2,4};

    SegmentedDeque<int> deque(item, 5, 2);
    SegmentedDeque<int> mappedReference(mappedItems, 5, 2);
    SegmentedDeque<int> filteredReference(filteredItems, 2, 2);

    SegmentedDeque<int>* mapped = deque.Map(TestDoubleValue);
    SegmentedDeque<int>* filtered = deque.Where(TestIsEven);
    int reduced = deque.Reduce(TestSum, 0);

    Check(*mapped == mappedReference, "TestMapWhereReduce Map");
    Check(*filtered == filteredReference, "TestMapWhereReduce Where");
    Check(reduced == 15, "TestMapWhereReduce Reduce");
    Check(DequeEqualsItems(deque, item, 5), "TestMapWhereReduce source unchanged");

    delete mapped;
    delete filtered;
}

void TestSort(){
    int item[] = {5,1,4,2,3};
    int reference[] = {1,2,3,4,5};

    SegmentedDeque<int> deque(item, 5, 2);
    SegmentedDeque<int> refDeque(reference, 5, 2);

    SegmentedDeque<int>* sorted = deque.Sort(TestLess);

    Check(*sorted == refDeque, "TestSort ascending");
    Check(DequeEqualsItems(deque, item, 5), "TestSort source unchanged");

    delete sorted;
}

void TestMerge(){
    int a[] = {5,1,3};
    int b[] = {4,2};
    int reference[] = {1,2,3,4,5};

    SegmentedDeque<int> A(a, 3, 2);
    SegmentedDeque<int> B(b, 2, 2);
    SegmentedDeque<int> refDeque(reference, 5, 2);

    SegmentedDeque<int>* merged = A.Merge(B, TestLess);

    Check(*merged == refDeque, "TestMerge sorted result");
    Check(A.GetLength() == 3 && B.GetLength() == 2, "TestMerge sources unchanged");

    delete merged;
}

void TestListBacking(){
    int item[] = {1,2,3,4,5,6,7};

    SegmentedDeque<int> deque(item, 7, 3, Backing::List);
    deque.PushFront(0);
    deque.PushBack(8);

    Check(deque.GetLength() == 9, "TestListBacking length");
    Check(deque.GetFirst() == 0, "TestListBacking first");
    Check(deque.GetLast() == 8, "TestListBacking last");
    int expected[] = {0,1,2,3,4,5,6,7,8};
    Check(DequeEqualsItems(deque, expected, 9), "TestListBacking order");
}

void TestInvalidArguments(){
    bool thrown = false;
    try{
        SegmentedDeque<int> deque(0);
    }
    catch(const InvalidArgument&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments segment size");

    thrown = false;
    try{
        SegmentedDeque<int> deque(nullptr, 1, 2);
    }
    catch(const InvalidArgument&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments null items");

    int item[] = {1,2,3};
    SegmentedDeque<int> deque(item, 3, 2);

    thrown = false;
    try{
        deque.GetSubsequence(-1, 1);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments subsequence start");

    thrown = false;
    try{
        deque.GetSubsequence(1, 3);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments subsequence end");

    thrown = false;
    try{
        deque.Map(nullptr);
    }
    catch(const InvalidArgument&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments map null");

    thrown = false;
    try{
        deque.Sort(nullptr);
    }
    catch(const InvalidArgument&){
        thrown = true;
    }
    Check(thrown, "TestInvalidArguments sort null");
}

void TestDoubleSegmentMapExpansion(){
    SegmentedDeque<int> deque(2);

    int initalMapSize = SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque);

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushBack(4);

    Check(
        SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == initalMapSize * 2,
        "TestDoubleSegmentMapExpansion first expansion after centered start"
    );
    Check(deque.GetLength() == 4, "TestDoubleSegmentMapExpansion length after first expansion");
    int expectedAfterFirstExpansion[] = {1,2,3,4};
    Check(DequeEqualsItems(deque, expectedAfterFirstExpansion, 4), "TestDoubleSegmentMapExpansion items after first expansion");

    deque.PushBack(5);

    int newMapSize = SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque);

    Check(newMapSize == initalMapSize * 2, "TestDoubleSegmentMapExpansion no second expansion yet");
    Check(deque.GetLength() == 5, "TestDoubleSegmentMapExpansion length after fifth item");
    int expectedAfterFifth[] = {1,2,3,4,5};
    Check(DequeEqualsItems(deque, expectedAfterFifth, 5), "TestDoubleSegmentMapExpansion items after fifth item");

    for(int i=0; i<4; i++){
        deque.PushFront(i*-1);
    }

    Check(
        SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == newMapSize,
        "TestDoubleSegmentMapExpansion no early second expansion"
    );

    deque.PushFront(-4);
    deque.PushFront(-5);

    int newNewMapSize = SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque);

    Check(newNewMapSize == newMapSize * 2, "TestDoubleSegmentMapExpansion second expansion");
    Check(deque.GetLength() == 11, "TestDoubleSegmentMapExpansion length after second expansion");
    int expectedAfterSecondExpansion[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    Check(DequeEqualsItems(deque, expectedAfterSecondExpansion, 11), "TestDoubleSegmentMapExpansion items after second expansion");

}

void TestInitialInternalState(){
    SegmentedDeque<int> deque(4, Backing::Array);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 3, "TestInitialInternalState map size");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 1, "TestInitialInternalState front index");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 1, "TestInitialInternalState back index");
    Check(SegmentedDequeTestAccess<int>::GetSegmentSize(deque) == 4, "TestInitialInternalState segment size");
    Check(SegmentedDequeTestAccess<int>::GetLength(deque) == 0, "TestInitialInternalState length");
}

void TestInternalIndexesAfterPushes(){
    SegmentedDeque<int> deque(2);

    deque.PushBack(1);
    deque.PushBack(2);
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 1, "TestInternalIndexesAfterPushes centered first segment front");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 2, "TestInternalIndexesAfterPushes back index moves after centered slot fills");

    deque.PushBack(3);
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 2, "TestInternalIndexesAfterPushes second back segment keeps index");

    deque.PushFront(0);
    deque.PushFront(-1);
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 0, "TestInternalIndexesAfterPushes front index moves left after first segment fills");
    Check(SegmentedDequeTestAccess<int>::HasSegmentAt(deque, 1), "TestInternalIndexesAfterPushes first segment exists");
    Check(SegmentedDequeTestAccess<int>::HasSegmentAt(deque, 2), "TestInternalIndexesAfterPushes back segment exists");
    int expected[] = {-1,0,1,2,3};
    Check(DequeEqualsItems(deque, expected, 5), "TestInternalIndexesAfterPushes data order");
}

void TestInternalIndexesAfterPops(){
    int item[] = {1,2,3,4,5};
    SegmentedDeque<int> deque(item, 5, 2);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 6, "TestInternalIndexesAfterPops map expanded");

    deque.PopFront();
    deque.PopFront();
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 3, "TestInternalIndexesAfterPops front index skips empty segment");

    deque.PopBack();
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 4, "TestInternalIndexesAfterPops back index keeps non-empty segment");

    deque.PopFront();
    deque.PopFront();
    Check(deque.IsEmpty(), "TestInternalIndexesAfterPops empty");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque),
          "TestInternalIndexesAfterPops equal indexes when empty");
}

void TestInternalExpansionKeepsCenteredSegments(){
    SegmentedDeque<int> deque(2);

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushBack(4);
    deque.PushBack(5);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 6, "TestInternalExpansionKeepsCenteredSegments map size after back expansion");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 2, "TestInternalExpansionKeepsCenteredSegments shifted front after back expansion");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 4, "TestInternalExpansionKeepsCenteredSegments shifted back after back expansion");
    int expectedAfterBackExpansion[] = {1,2,3,4,5};
    Check(DequeEqualsItems(deque, expectedAfterBackExpansion, 5), "TestInternalExpansionKeepsCenteredSegments data after back expansion");

    deque.PushFront(0);
    deque.PushFront(-1);
    deque.PushFront(-2);
    deque.PushFront(-3);
    deque.PushFront(-4);
    deque.PushFront(-5);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 12, "TestInternalExpansionKeepsCenteredSegments map size after front expansion");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 2, "TestInternalExpansionKeepsCenteredSegments shifted front after front expansion");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 7, "TestInternalExpansionKeepsCenteredSegments shifted back after front expansion");
    int expectedAfterFrontExpansion[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    Check(DequeEqualsItems(deque, expectedAfterFrontExpansion, 11), "TestInternalExpansionKeepsCenteredSegments data after front expansion");
}

void TestFirstPushBackKeepsInitialSegmentCentered(){
    SegmentedDeque<int> deque(4);

    deque.PushBack(10);

    int middleIndex = SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque);
    Check(deque.GetFirst() == 10, "TestFirstPushBackKeepsInitialSegmentCentered first");
    Check(deque.GetLast() == 10, "TestFirstPushBackKeepsInitialSegmentCentered last");
    Check(deque.GetLength() == 1, "TestFirstPushBackKeepsInitialSegmentCentered length");
    Check(SegmentedDequeTestAccess<int>::GetSegmentFirst(deque, middleIndex) == 2,
          "TestFirstPushBackKeepsInitialSegmentCentered first index");

    deque.PushFront(5);
    deque.PushBack(20);
    deque.PushFront(1);

    int expected[] = {1,5,10,20};
    Check(DequeEqualsItems(deque, expected, 4), "TestFirstPushBackKeepsInitialSegmentCentered order");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == middleIndex,
          "TestFirstPushBackKeepsInitialSegmentCentered no front segment yet");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == middleIndex,
          "TestFirstPushBackKeepsInitialSegmentCentered no back segment yet");
}

void TestFirstPushFrontKeepsInitialSegmentCentered(){
    SegmentedDeque<int> deque(4);

    deque.PushFront(10);

    int middleIndex = SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque);
    Check(deque.GetFirst() == 10, "TestFirstPushFrontKeepsInitialSegmentCentered first");
    Check(deque.GetLast() == 10, "TestFirstPushFrontKeepsInitialSegmentCentered last");
    Check(deque.GetLength() == 1, "TestFirstPushFrontKeepsInitialSegmentCentered length");
    Check(SegmentedDequeTestAccess<int>::GetSegmentFirst(deque, middleIndex) == 2,
          "TestFirstPushFrontKeepsInitialSegmentCentered first index");

    deque.PushBack(20);

    int expected[] = {10,20};
    Check(DequeEqualsItems(deque, expected, 2), "TestFirstPushFrontKeepsInitialSegmentCentered order");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == middleIndex,
          "TestFirstPushFrontKeepsInitialSegmentCentered uses right space");
}

void TestNewEdgeSegmentsKeepTheirFillDirection(){
    SegmentedDeque<int> frontDeque(4);
    frontDeque.PushBack(10);
    frontDeque.PushFront(5);
    frontDeque.PushBack(20);
    frontDeque.PushFront(1);

    int oldFrontIndex = SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(frontDeque);
    frontDeque.PushFront(0);
    int newFrontIndex = SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(frontDeque);

    Check(newFrontIndex == oldFrontIndex - 1, "TestNewEdgeSegmentsKeepTheirFillDirection front segment created");
    Check(SegmentedDequeTestAccess<int>::GetSegmentFirst(frontDeque, newFrontIndex) == 3,
          "TestNewEdgeSegmentsKeepTheirFillDirection front starts at right edge");
    Check(SegmentedDequeTestAccess<int>::GetSegmentCount(frontDeque, newFrontIndex) == 1,
          "TestNewEdgeSegmentsKeepTheirFillDirection front count");
    int expectedFront[] = {0,1,5,10,20};
    Check(DequeEqualsItems(frontDeque, expectedFront, 5),
          "TestNewEdgeSegmentsKeepTheirFillDirection front order");

    SegmentedDeque<int> backDeque(4);
    backDeque.PushBack(10);
    backDeque.PushFront(5);
    backDeque.PushBack(20);
    backDeque.PushFront(1);

    int oldBackIndex = SegmentedDequeTestAccess<int>::GetBackSegmentIndex(backDeque);
    backDeque.PushBack(30);
    int newBackIndex = SegmentedDequeTestAccess<int>::GetBackSegmentIndex(backDeque);

    Check(newBackIndex == oldBackIndex + 1, "TestNewEdgeSegmentsKeepTheirFillDirection back segment created");
    Check(SegmentedDequeTestAccess<int>::GetSegmentFirst(backDeque, newBackIndex) == 0,
          "TestNewEdgeSegmentsKeepTheirFillDirection back starts at left edge");
    Check(SegmentedDequeTestAccess<int>::GetSegmentCount(backDeque, newBackIndex) == 1,
          "TestNewEdgeSegmentsKeepTheirFillDirection back count");
    int expectedBack[] = {1,5,10,20,30};
    Check(DequeEqualsItems(backDeque, expectedBack, 5),
          "TestNewEdgeSegmentsKeepTheirFillDirection back order");
}

void TestCenteringAfterDequeBecomesEmpty(){
    SegmentedDeque<int> deque(4);

    deque.PushBack(10);
    deque.PushFront(5);
    deque.PopFront();
    deque.PopBack();

    Check(deque.IsEmpty(), "TestCenteringAfterDequeBecomesEmpty empty");

    deque.PushFront(20);

    int middleIndex = SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque);
    Check(deque.GetFirst() == 20, "TestCenteringAfterDequeBecomesEmpty value");
    Check(SegmentedDequeTestAccess<int>::GetSegmentFirst(deque, middleIndex) == 2,
          "TestCenteringAfterDequeBecomesEmpty first index");
}

void RunAllTests()
{
    TestPushBack();
    TestPushFront();

    TestPopBack();
    TestPopFront();
    TestPopFrontEmpty();
    TestPopBackEmpty();

    TestCopyConstructor();
    TestAssignmentOperator();

    TestsConcat();
    TestFindSubsequence();
    TestConcatSubSequence();
    TestCompexChain();
    TestMapWhereReduce();
    TestSort();
    TestMerge();
    TestListBacking();
    TestInvalidArguments();

    TestDoubleSegmentMapExpansion();
    TestInitialInternalState();
    TestInternalIndexesAfterPushes();
    TestInternalIndexesAfterPops();
    TestInternalExpansionKeepsCenteredSegments();
    TestFirstPushBackKeepsInitialSegmentCentered();
    TestFirstPushFrontKeepsInitialSegmentCentered();
    TestNewEdgeSegmentsKeepTheirFillDirection();
    TestCenteringAfterDequeBecomesEmpty();
}
