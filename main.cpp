#include <iostream>
#include "Testing.h"

int main()
{
    // 1. Перевіряємо коректність роботи BST через std::set
    if (testBinarySearchTree())
    {
        std::cout << "\n[OK] Базові операції працюють правильно." << std::endl;
    }

    // 2. Порівнюємо продуктивність та висоту
    runBalanceComparison();

    // 3. тестуємо Бінарну купу
    testPriorityQueue();

    return 0;
}
