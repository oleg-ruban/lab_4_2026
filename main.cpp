#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree db;

    // Додавання даних
    db.insert({"Ivanov", 4.5, true, 0});
    db.insert({"Petrov", 3.2, false, 5});
    db.insert({"Abramov", 5.0, true, 0});
    db.insert({"Sidorov", 4.8, true, 1});

    std::cout << "--- Список студентів ---" << std::endl;
    db.print();

    std::cout << "\nСтатистика дерева:" << std::endl;
    std::cout << "Кількість студентів: " << db.size() << std::endl;
    std::cout << "Висота дерева: " << db.height() << std::endl;

    // Пошук у діапазоні
    std::cout << "\nСтуденти на проміжку від 'B' до 'P':" << std::endl;
    auto range = db.findInRange({"B"}, {"P"});
    for (const auto& s : range) {
        std::cout << "- " << s.name << std::endl;
    }

    return 0;
}