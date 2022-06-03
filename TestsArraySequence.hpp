#pragma once

#include "ArraySequence.hpp"
#include <cassert>

class ArraySequenceTests
{
private:
    static void findTest();
    static void equalityTest();
    static void oneEqualAnotherTest();
    static void getSubSequenceTest();
    static void insertAtTest();
    static void concatTest();

public:
    static void allTestsTogether();
};

void ArraySequenceTests::findTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    ArraySequence<int> ArraySequence(items, 5);

    assert(ArraySequence.find(0) == 0);
    assert(ArraySequence.find(2) == 1);
    assert(ArraySequence.find(4) == 3);
    assert(ArraySequence.find(5) == 4);
    assert(ArraySequence.find(-7) == -1);
}

void ArraySequenceTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    ArraySequence<int> arr(items, 5);

    Sequence<int>* seq = new ArraySequence<int>(items, 5);
    assert(arr == *seq);
}

void ArraySequenceTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    Sequence<int> *seq = new ArraySequence<int>(items, 5);
    ArraySequence<int> arr;
    arr = *seq;

    assert(arr == *seq);
}

void ArraySequenceTests::getSubSequenceTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    ArraySequence<int> arr1(items, 5);

    ArraySequence<int> arr2(4);

    for (int i = 0; i < 4; i++)
        arr2[i] = arr1[i + 1];

    Sequence<int> *seq = &arr2;

    assert(*seq == *arr1.getSubSequence(1, 4));
}

void ArraySequenceTests::insertAtTest()
{
    int items1[5] = {0, 2, 2, 4, 5};
    int items2[7] = {0, 2, 3, 2, 15, 4, 5};

    ArraySequence<int> array1(items1, 5);
    ArraySequence<int> array2(items2, 7);
    array1.insertAt(3, 2);
    array1.insertAt(15, 4);

    assert(array1 == array2);
}

void ArraySequenceTests::concatTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    int items2[10] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    ArraySequence<int> array(items, 5);
    Sequence<int>* seq = new ArraySequence<int>(items, 5);
    assert(*array.concat(seq) == ArraySequence<int>(items2, 10));
}

void ArraySequenceTests::allTestsTogether()
{
    findTest();
    equalityTest();
    oneEqualAnotherTest();
    getSubSequenceTest();
    insertAtTest();
    concatTest();

}
