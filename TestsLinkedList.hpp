#pragma once

#include "LinkedList.hpp"
#include <cassert>

class LinkedListTests
{
private:
    static void constructorFromCountTest();
    static void constructorFromItemsAndCountTest();
    static void equalityTest();
    static void constructorFromLinkedListTest();
    static void oneEqualAnotherRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void findTest();
    static void getSubListTest();
    static void appendTest();
    static void prependTest();
    static void insertAtTest();
    static void concatTest();

public:
    static void allTestsTogether();
};

void LinkedListTests::constructorFromCountTest()
{
    LinkedList<int> list(5);
    assert(list.getSize() == 5);

    for (int i = 0; i < 5; i++)
        assert(list.get(i) == 0);
}

void LinkedListTests::constructorFromItemsAndCountTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.getSize() == 5);
    for(int i = 0; i < 5; i++)
        assert(list.get(i) == i + 1);
}

void LinkedListTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(5);

    for (int i = 0; i < 5; i++)
        list2[i] = i + 1;

    assert(list1 == list2);
}

void LinkedListTests::constructorFromLinkedListTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(list1);

    assert(list2 == list1);
}

void LinkedListTests::oneEqualAnotherRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);
    LinkedList<int> list2;
    list2 = LinkedList<int>(items, 5);
    assert(list2 == list1);
}

void LinkedListTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);

    LinkedList<int> list2;
    list2 = list1;
    assert(list2 == list1);
}

void LinkedListTests::findTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.find(0) == 0);
    assert(list.find(2) == 1);
    assert(list.find(4) == 3);
    assert(list.find(5) == 4);
    assert(list.find(-7) == -1);
}

void LinkedListTests::getSubListTest()
{
    int items1[5] = {0, 2, 2, 4, 5};
    int items2[4] = {2, 2, 4, 5};
    LinkedList<int> list1(items1, 5);
    LinkedList<int> list2 = *list1.getSubList(1, 4);
    list1 = LinkedList<int>(items2, 4);
    assert(list1 == list2);

}

void LinkedListTests::appendTest()
{
    LinkedList<int> list(0);
    list.append(1);
    list.append(2);
    int items[2] = {1, 2};
    assert(list == LinkedList<int>(items, 2));
}

void LinkedListTests::insertAtTest()
{
    LinkedList<int> list(0);
    list.insertAt(5, 0);
    list.insertAt(3, 1);
    int items[2] = {5, 3};
    assert(list == LinkedList<int>(items, 2));
}

void LinkedListTests::concatTest()
{
    int items1[5] = {0, 2, 2, 4, 5};
    LinkedList<int> list1(items1, 5);
    LinkedList<int> list2(items1, 5);

    int items2[10] = {0, 2, 2, 4, 5, 0, 2, 2, 4, 5};
    LinkedList<int> list3(items2, 10);
    assert(*list1.concat(&list2) == list3);
}

void LinkedListTests::prependTest()
{
    LinkedList<int> list(0);
    list.prepend(1);
    list.prepend(2);
    int items[2] = {2, 1};
    assert(LinkedList<int>(items, 2) == list);
}

void LinkedListTests::allTestsTogether()
{
    constructorFromItemsAndCountTest();
    constructorFromCountTest();
    equalityTest();
    constructorFromLinkedListTest();
    oneEqualAnotherTest();
    oneEqualAnotherRvalueReferenceTest();
    findTest();
    getSubListTest();
    appendTest();
    prependTest();
    insertAtTest();
    concatTest();
}