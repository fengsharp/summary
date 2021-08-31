#include <iostream>

#include "SalesItem.h"

void test01();

int main()
{
    test01();

    return 0;
}

void test01()
{
    SalesItem item1, item2;
    std::cin >> item1 >> item2;
    std::cout << item1 << std::endl
              << item2 << std::endl;
}













