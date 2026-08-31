#pragma once

bool Check(bool condition, const char* testName);

void TestPushBack();
void TestPushFront();

void TestPopBack();
void TestPopFront();
void TestPopFrontEmpty();
void TestPopBackEmpty();

void TestsGet();
void TestsSet();

void TestCopyConstructor();
void TestAssignmentOperator();

void TestsConcat();
void TestFindSubsequence();
void TestConcatSubSequence();
void TestCompexChain();
void TestMapWhereReduce();
void TestSort();
void TestMerge();
void TestListBacking();
void TestInvalidArguments();
void TestInitialInternalState();
void TestInternalIndexesAfterPushes();
void TestInternalIndexesAfterPops();
void TestInternalExpansionKeepsCenteredSegments();

void RunAllTests();
