#include <iostream>
#include "Testing.h"

int main() {
    std::cout << "Запуск тестування бази даних..." << std::endl;

    if (testBinarySearchTree()) {
        std::cout << "\n[SUCCESS] Програма пройшла всі тести." << std::endl;
    } else {
        std::cout << "\n[FAILED] У реалізації дерева є помилки." << std::endl;
    }

    return 0;
}