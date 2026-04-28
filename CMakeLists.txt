cmake_minimum_required(VERSION 3.5)
project(lab_4_2026 CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_4_2026
        Student.h
        Student.cpp
        BinarySearchTree.h
        BinarySearchTree.cpp
        main.cpp
        Testing.cpp
        Testing.h
        PriorityQueue.h
        AVLTree.cpp
        AVLTree.h)
