#include <iostream>
#include <limits>
#include <string>
#include <chrono>

#include "ArraySequence.h"
#include "LinkedList.h"
#include "ListSequence.h"
#include "SegmentedDeque.h"

static int doubleValue(int value)
{
    return value * 2;
}

static bool isEven(int value)
{
    return value % 2 == 0;
}

static int sumValues(int left, int right)
{
    return left + right;
}

static bool ascending(int left, int right)
{
    return left < right;
}

static void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
            return value;

        std::cout << "Incorrect input. Enter an integer.\n";
        clearInput();
    }
}

static Backing readBacking()
{
    while (true)
    {
        int choice = readInt("Backing storage: 1 - ArraySequence, 2 - ListSequence: ");
        if (choice == 1)
            return Backing::Array;
        if (choice == 2)
            return Backing::List;

        std::cout << "Unknown backing type.\n";
    }
}

static SegmentedDeque<int>* readDeque()
{
    int count = readInt("Element count: ");
    if (count < 0)
        throw InvalidArgument("Count cannot be negative");

    int segmentSize = readInt("Segment size: ");
    Backing backing = readBacking();

    SegmentedDeque<int>* deque = new SegmentedDeque<int>(segmentSize, backing);
    for (int i = 0; i < count; i++)
    {
        int value = readInt("  item[" + std::to_string(i) + "]: ");
        deque->PushBack(value);
    }

    return deque;
}

static void printDeque(const SegmentedDeque<int>& deque, const std::string& label)
{
    std::cout << label << " [size=" << deque.GetLength() << "]: ";
    std::cout << "{";
    for (int i = 0; i < deque.GetLength(); i++)
    {
        if (i > 0)
            std::cout << ", ";
        std::cout << deque.Get(i);
    }
    std::cout << "}\n";
}

static bool check(bool condition, const std::string& message)
{
    std::cout << (condition ? "[OK] " : "[FAIL] ") << message << "\n";
    return condition;
}

static void demoBaseStructures()
{
    int items[] = {1, 2, 3, 4};

    DynamicArray<int> array(items, 4);
    LinkedList<int> list(items, 4);
    MutableArraySequence<int> arraySequence(items, 4);
    MutableListSequence<int> listSequence(items, 4);

    std::cout << "\nDynamicArray: ";
    for (int i = 0; i < array.GetSize(); i++)
        std::cout << array.Get(i) << " ";

    std::cout << "\nLinkedList: ";
    for (int i = 0; i < list.GetLenght(); i++)
        std::cout << list.Get(i) << " ";

    std::cout << "\nArraySequence length: " << arraySequence.GetLength();
    std::cout << "\nListSequence length: " << listSequence.GetLength() << "\n";

    Sequence<int>* mapped = arraySequence.Map(doubleValue);
    std::cout << "ArraySequence map(x2): ";
    for (int i = 0; i < mapped->GetLength(); i++)
        std::cout << mapped->Get(i) << " ";
    std::cout << "\n";
    delete mapped;
}

static void runAutomaticTests()
{
    int passed = 0;
    int total = 0;

    int items[] = {3, 1, 2};
    SegmentedDeque<int> deque(items, 3, 2, Backing::Array);

    total++;
    if (check(deque.GetLength() == 3 && deque.Get(0) == 3 && deque.Get(2) == 2,
              "constructor and indexed access"))
        passed++;

    deque.PushFront(0);
    deque.PushBack(4);
    total++;
    if (check(deque.GetLength() == 5 && deque.GetFirst() == 0 && deque.GetLast() == 4,
              "PushFront, PushBack, GetFirst, GetLast"))
        passed++;

    total++;
    if (check(deque.PopFront() == 0 && deque.PopBack() == 4 && deque.GetLength() == 3,
              "PopFront and PopBack"))
        passed++;

    deque.Set(9, 1);
    total++;
    if (check(deque.Get(1) == 9, "Set"))
        passed++;

    SegmentedDeque<int>* subsequence = deque.GetSubsequence(0, 1);
    total++;
    if (check(subsequence->GetLength() == 2 && subsequence->Get(0) == 3 && subsequence->Get(1) == 9,
              "GetSubsequence"))
        passed++;
    delete subsequence;

    SegmentedDeque<int>* mapped = deque.Map(doubleValue);
    total++;
    if (check(mapped->Get(0) == 6 && mapped->Get(1) == 18, "Map"))
        passed++;
    delete mapped;

    SegmentedDeque<int>* filtered = deque.Where(isEven);
    total++;
    if (check(filtered->GetLength() == 1 && filtered->Get(0) == 2, "Where"))
        passed++;
    delete filtered;

    total++;
    if (check(deque.Reduce(sumValues, 0) == 14, "Reduce"))
        passed++;

    SegmentedDeque<int>* sorted = deque.Sort(ascending);
    total++;
    if (check(sorted->Get(0) == 2 && sorted->Get(1) == 3 && sorted->Get(2) == 9,
              "Sort"))
        passed++;
    delete sorted;

    int findItems[] = {9, 2};
    SegmentedDeque<int> pattern(findItems, 2, 2, Backing::Array);
    total++;
    if (check(deque.FindSubsequence(pattern) == 1, "FindSubsequence"))
        passed++;

    int otherItems[] = {7, 8};
    SegmentedDeque<int> other(otherItems, 2, 2, Backing::List);
    SegmentedDeque<int>* concat = deque.Concat(other);
    total++;
    if (check(concat->GetLength() == 5 && concat->Get(3) == 7 && concat->Get(4) == 8,
              "Concat"))
        passed++;
    delete concat;

    SegmentedDeque<int>* merged = deque.Merge(other, ascending);
    total++;
    if (check(merged->GetLength() == 5 && merged->Get(0) == 2 && merged->Get(4) == 9,
              "Merge"))
        passed++;
    delete merged;

    std::cout << "Automatic tests: " << passed << "/" << total << " passed.\n";
}

static void runPerformanceDemo()
{
    int count = readInt("Number of elements for performance test: ");
    if (count < 0)
        throw InvalidArgument("Count cannot be negative");

    int segmentSize = readInt("Segment size: ");
    Backing backing = readBacking();

    SegmentedDeque<int> deque(segmentSize, backing);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
        deque.PushBack(i);
    auto afterPush = std::chrono::high_resolution_clock::now();

    long long checksum = 0;
    for (int i = 0; i < count; i++)
        checksum += deque.Get(i);
    auto afterGet = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; i++)
        deque.PopBack();
    auto afterPop = std::chrono::high_resolution_clock::now();

    auto pushMs = std::chrono::duration_cast<std::chrono::milliseconds>(afterPush - start).count();
    auto getMs = std::chrono::duration_cast<std::chrono::milliseconds>(afterGet - afterPush).count();
    auto popMs = std::chrono::duration_cast<std::chrono::milliseconds>(afterPop - afterGet).count();

    std::cout << "PushBack time: " << pushMs << " ms\n";
    std::cout << "Indexed Get time: " << getMs << " ms\n";
    std::cout << "PopBack time: " << popMs << " ms\n";
    std::cout << "Checksum: " << checksum << "\n";
}

static void printMenu()
{
    std::cout
        << "\n=== Laboratory work 3: SegmentedDeque ===\n"
        << "Variant 5: deque with segmented buffer\n"
        << "1. Show deque\n"
        << "2. PushFront\n"
        << "3. PushBack\n"
        << "4. PopFront\n"
        << "5. PopBack\n"
        << "6. Get by index\n"
        << "7. Set by index\n"
        << "8. GetSubsequence\n"
        << "9. Concat\n"
        << "10. Map: x * 2\n"
        << "11. Where: even values\n"
        << "12. Reduce: sum\n"
        << "13. Sort ascending\n"
        << "14. FindSubsequence\n"
        << "15. Merge and sort ascending\n"
        << "16. Recreate deque\n"
        << "17. Demo base structures\n"
        << "18. Run automatic tests\n"
        << "19. Performance test\n"
        << "0. Exit\n";
}

static void runDequeMenu()
{
    SegmentedDeque<int>* deque = readDeque();

    while (true)
    {
        try
        {
            printMenu();
            int choice = readInt("Choice: ");

            if (choice == 0)
                break;

            if (choice == 1)
            {
                printDeque(*deque, "Deque");
            }
            else if (choice == 2)
            {
                deque->PushFront(readInt("Value: "));
            }
            else if (choice == 3)
            {
                deque->PushBack(readInt("Value: "));
            }
            else if (choice == 4)
            {
                std::cout << "Popped: " << deque->PopFront() << "\n";
            }
            else if (choice == 5)
            {
                std::cout << "Popped: " << deque->PopBack() << "\n";
            }
            else if (choice == 6)
            {
                int index = readInt("Index: ");
                std::cout << "Value: " << deque->Get(index) << "\n";
            }
            else if (choice == 7)
            {
                int index = readInt("Index: ");
                int value = readInt("Value: ");
                deque->Set(value, index);
            }
            else if (choice == 8)
            {
                int start = readInt("Start index: ");
                int end = readInt("End index: ");
                SegmentedDeque<int>* result = deque->GetSubsequence(start, end);
                printDeque(*result, "Subsequence");
                delete result;
            }
            else if (choice == 9)
            {
                SegmentedDeque<int>* other = readDeque();
                SegmentedDeque<int>* result = deque->Concat(*other);
                printDeque(*result, "Concat result");
                delete other;
                delete result;
            }
            else if (choice == 10)
            {
                SegmentedDeque<int>* result = deque->Map(doubleValue);
                printDeque(*result, "Mapped result");
                delete result;
            }
            else if (choice == 11)
            {
                SegmentedDeque<int>* result = deque->Where(isEven);
                printDeque(*result, "Filtered result");
                delete result;
            }
            else if (choice == 12)
            {
                std::cout << "Sum: " << deque->Reduce(sumValues, 0) << "\n";
            }
            else if (choice == 13)
            {
                SegmentedDeque<int>* result = deque->Sort(ascending);
                printDeque(*result, "Sorted result");
                delete result;
            }
            else if (choice == 14)
            {
                SegmentedDeque<int>* subsequence = readDeque();
                std::cout << "First position: " << deque->FindSubsequence(*subsequence) << "\n";
                delete subsequence;
            }
            else if (choice == 15)
            {
                SegmentedDeque<int>* other = readDeque();
                SegmentedDeque<int>* result = deque->Merge(*other, ascending);
                printDeque(*result, "Merged result");
                delete other;
                delete result;
            }
            else if (choice == 16)
            {
                delete deque;
                deque = readDeque();
            }
            else if (choice == 17)
            {
                demoBaseStructures();
            }
            else if (choice == 18)
            {
                runAutomaticTests();
            }
            else if (choice == 19)
            {
                runPerformanceDemo();
            }
            else
            {
                std::cout << "Unknown menu item.\n";
            }
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << "\n";
        }
    }

    delete deque;
}

int main()
{
    try
    {
        runDequeMenu();
    }
    catch (const std::exception& error)
    {
        std::cout << "Fatal error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
