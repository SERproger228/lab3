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

void TestPushBack(){
    SegmentedDeque<int> deque(2);

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);

    Check(deque.GetLength() == 3, "TestPushBack length");
    Check(deque.Get(0) == 1, "TestPushBack Get(0)");
    Check(deque.Get(1) == 2, "TestPushBack Get(1)");
    Check(deque.Get(2) == 3, "TestPushBack Get(2)");
}

void TestPushFront(){
    
    SegmentedDeque<int> deque(2);

    deque.PushFront(1);
    deque.PushFront(2);
    deque.PushFront(3);

    Check(deque.GetLength() == 3, "TestPushFront length");
    Check(deque.Get(0) == 3, "TestPushFront Get(0)");
    Check(deque.Get(1) == 2, "TestPushFront Get(1)");
    Check(deque.Get(2) == 1, "TestPushFront Get(2)");
}

void TestPopBack(){

    int items[] = {1,2,3,4,5};
    SegmentedDeque<int> deque(items, 5, 2);

    int firsPop = deque.PopBack();
    int secondPop = deque.PopBack();
    int thirdPop = deque.PopBack();

    Check(deque.GetLength()==2, "TestPopBack lenght");
    Check(deque.Get(0)==1, "TestPopBack Get(0)");
    Check(deque.Get(1)==2, "TestPopBack Get(1)");
    Check(firsPop==5, "TestPopBack firstPop");
    Check(secondPop==4, "TestPopBack secondPop");
    Check(thirdPop==3, "TestPopBack thirdPop");
}

void TestPopFront(){
    int items[] = {1,2,3,4,5};
    SegmentedDeque<int> deque(items, 5, 2);

    int firsPop = deque.PopFront();
    int secondPop = deque.PopFront();
    int thirdPop = deque.PopFront();

    Check(deque.GetLength()==2, "TestPopFront lenght");
    Check(deque.Get(0)==4, "TestPopFront Get(0)");
    Check(deque.Get(1)==5, "TestPopFront Get(1)");
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

void TestsGet(){
    
    int item[]={1,2,3,4};
    SegmentedDeque<int> deque(item, 4, 2);

    Check(deque.Get(0)==1, "TestsGet Get(0)");
    Check(deque.Get(3)==4, "TestsGet Get(lenght-1)");

    bool thrown = false;
    try{
        deque.Get(-1);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestsGet Get(-1)");

    thrown = false;
    try{
        deque.Get(4);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestsGet Get(lenght)");


}

void TestsSet(){
    int item[]={1,2,3,4,5};
    SegmentedDeque<int> deque(item,5,2);

    deque.Set(13,3);
    Check(deque.Get(3)==13, "TestsSet Set(n)");
    Check(deque.Get(2) == 3, "TestSet left unchanged");
    Check(deque.Get(4) == 5, "TestSet right unchanged");
    bool thrown = false;
    try{
        deque.Set(13,-1);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestsSet Set(-1)");

    thrown = false;
    try{
        deque.Set(13, 5);
    }
    catch(const IndexOutOfRange&){
        thrown = true;
    }
    Check(thrown, "TestsSet Set(lenght)");
}

void TestCopyConstructor()
{
int item[]={1,2,3,4,5};
SegmentedDeque<int> original(item, 5, 2);
SegmentedDeque<int> copy(original);
Check(copy==original, "TestCopyConstructor check copy");
copy.Set(13,2);
Check(copy.Get(2)!=original.Get(2), "TestCopyConstructor check copy set");
}

void TestAssignmentOperator(){
    int a[]= {1,2,3};
    int b[]={4,5,6,7,8};
    SegmentedDeque<int> original(a, 3, 2);
    SegmentedDeque<int> copy(b, 5, 3);

    copy=original;
    Check(copy==original, "TestAssignmentOperator correct copy");
    copy.Set(99, 2);
    Check(copy.Get(2)!=original.Get(2), "TestAssignmentOperator check copy set");

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
    int e[] = {3,99,5,6,1,2,3,4,5};

    SegmentedDeque<int> cRef(c,8,2);
    SegmentedDeque<int> dRef(d, 4, 2);
    SegmentedDeque<int> eRef(e,9,2);


    
    SegmentedDeque<int> A(a, 5, 2);
    SegmentedDeque<int> B(b, 3, 2);

    SegmentedDeque<int>* C = A.Concat(B);
    Check(*C==cRef, "TestComplexChain A.concat(B)");

    SegmentedDeque<int>* D = C->GetSubsequence(2, 5);
    Check(*D==dRef, "TestComplexChain GetSubsequence");

    D->Set(99, 1);
    Check(*C==cRef, "TestComplexChain correct set for C");
    Check(D->Get(1)==99, "TestComplexChain correct set for D");

    
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
    Check(deque.Get(0) == 1 && deque.Get(4) == 5, "TestMapWhereReduce source unchanged");

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
    Check(deque.Get(0) == 5 && deque.Get(1) == 1, "TestSort source unchanged");

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
    Check(deque.Get(4) == 4, "TestListBacking middle");
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
        SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == initalMapSize,
        "TestDoubleSegmentMapExpansion no early expansion"
    );

    deque.PushBack(5);

    int newMapSize = SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque);

    Check(newMapSize == initalMapSize * 2, "TestDoubleSegmentMapExpansion first expansion");
    Check(deque.GetLength() == 5, "TestDoubleSegmentMapExpansion length after first expansion");
    Check(deque.Get(0) == 1 && deque.Get(4) == 5, "TestDoubleSegmentMapExpansion items after first expansion");

    for(int i=0; i<4; i++){
        deque.PushFront(i*-1);
    }

    Check(
        SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == newMapSize,
        "TestDoubleSegmentMapExpansion no early second expansion"
    );

    deque.PushFront(-4);

    int newNewMapSize = SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque);

    Check(newNewMapSize == newMapSize * 2, "TestDoubleSegmentMapExpansion second expansion");
    Check(deque.GetLength() == 10, "TestDoubleSegmentMapExpansion length after second expansion");
    Check(deque.Get(0) == -4 && deque.Get(9) == 5, "TestDoubleSegmentMapExpansion items after second expansion");

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
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 1, "TestInternalIndexesAfterPushes first segment front");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 1, "TestInternalIndexesAfterPushes first segment back");

    deque.PushBack(3);
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 2, "TestInternalIndexesAfterPushes back index moves right");

    deque.PushFront(0);
    deque.PushFront(-1);
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 0, "TestInternalIndexesAfterPushes front index moves left");
    Check(SegmentedDequeTestAccess<int>::HasSegmentAt(deque, 0), "TestInternalIndexesAfterPushes front segment exists");
    Check(SegmentedDequeTestAccess<int>::HasSegmentAt(deque, 1), "TestInternalIndexesAfterPushes middle segment exists");
    Check(SegmentedDequeTestAccess<int>::HasSegmentAt(deque, 2), "TestInternalIndexesAfterPushes back segment exists");
}

void TestInternalIndexesAfterPops(){
    int item[] = {1,2,3,4,5};
    SegmentedDeque<int> deque(item, 5, 2);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 6, "TestInternalIndexesAfterPops map expanded");

    deque.PopFront();
    deque.PopFront();
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 3, "TestInternalIndexesAfterPops front index skips empty segment");

    deque.PopBack();
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 3, "TestInternalIndexesAfterPops back index skips empty segment");

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
    Check(deque.Get(0) == 1 && deque.Get(4) == 5, "TestInternalExpansionKeepsCenteredSegments data after back expansion");

    deque.PushFront(0);
    deque.PushFront(-1);
    deque.PushFront(-2);
    deque.PushFront(-3);
    deque.PushFront(-4);

    Check(SegmentedDequeTestAccess<int>::GetSegmentMapSize(deque) == 12, "TestInternalExpansionKeepsCenteredSegments map size after front expansion");
    Check(SegmentedDequeTestAccess<int>::GetFrontSegmentIndex(deque) == 2, "TestInternalExpansionKeepsCenteredSegments shifted front after front expansion");
    Check(SegmentedDequeTestAccess<int>::GetBackSegmentIndex(deque) == 7, "TestInternalExpansionKeepsCenteredSegments shifted back after front expansion");
    Check(deque.Get(0) == -4 && deque.Get(9) == 5, "TestInternalExpansionKeepsCenteredSegments data after front expansion");
}

void RunAllTests()
{
    TestPushBack();
    TestPushFront();

    TestPopBack();
    TestPopFront();
    TestPopFrontEmpty();
    TestPopBackEmpty();

    TestsGet();
    TestsSet();

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
}
