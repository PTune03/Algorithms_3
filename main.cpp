
#include "menu.h"
#include "Tests.hpp"
#include "LinkedList.hpp"
#include <cassert>
int main()
{
    int items[5] = {1, 2, 3, 4, 5};

    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(5);

    for (int i = 0; i < 5; i++)
        list2[i] = i + 1;
    list1.print();
    assert(list1 == list2);
//    tests();
//    menu();
    return 0;
}