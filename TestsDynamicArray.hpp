#pragma once

#include "DynamicArray.hpp"
#include <cassert>

class DynamicArrayTests
{
private:
    static void constructorFromCountTest();
    static void constructorFromItemsAndCountTest();
    static void equalityTest();
    static void constructorFromDynamicArrayTest();
    static void oneEqualAnotherRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void resizeTest();

public:
    static void allTestsTogether();
};

void DynamicArrayTests::constructorFromCountTest()
{
    DynamicArray<int> array(5);
    assert(array.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(array.get(i) == 0);
}

void DynamicArrayTests::constructorFromItemsAndCountTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(items, 5);

    assert(array.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(array.get(i) == i + 1);
}

void DynamicArrayTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    DynamicArray<int> arr1(items, 5);
    DynamicArray<int> arr2(5);
    for (int i = 0; i < 5; i++)
        arr2[i] = i + 1;

    assert(arr1 == arr2);
}

void DynamicArrayTests::constructorFromDynamicArrayTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr1(items, 5);
    DynamicArray<int> arr2(arr1);
    assert(arr1 == arr2);
}

void DynamicArrayTests::oneEqualAnotherRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    DynamicArray<int> arr1(items, 5);

    DynamicArray<int> arr2;
    arr2 = DynamicArray<int>(items, 5);

    assert(arr1 == arr2);
}

void DynamicArrayTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr1(items, 5);

    DynamicArray<int> arr2;
    arr2 = arr1;
    assert(arr2 == arr1);
}

void DynamicArrayTests::resizeTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[6] = {0, 2, 2, 4, 5, 0};
    int items3[4] = {0, 2, 2, 4};
    DynamicArray<int> array1(items, 5);
    DynamicArray<int> array2(items2, 6);

    array1.resize(6);
    assert(array1 == array2);
    array1.resize(4);
    array2 = DynamicArray<int>(items3, 4);
    assert(array1 == array2);

}

void DynamicArrayTests::allTestsTogether()
{
    constructorFromCountTest();
    constructorFromItemsAndCountTest();
    equalityTest();
    constructorFromDynamicArrayTest();
    oneEqualAnotherRvalueReferenceTest();
    oneEqualAnotherTest();
    resizeTest();
}