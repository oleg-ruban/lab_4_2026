#ifndef BST_H
#define BST_H

#include "Student.h"
#include <vector>

struct Node {
    Student data;
    Node* left;
    Node* right;
    Node(Student s) : data(s), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;
    size_t treeSize;

    // Допоміжні рекурсивні методи
    Node* insert(Node* node, Student s);
    Node* erase(Node* node, Student s);
    Node* findMin(Node* node);
    void printInOrder(Node* node) const;
    int calculateHeight(Node* node) const;
    void getInRange(Node* node, const Student& minS, const Student& maxS, std::vector<Student>& res) const;
    void clear(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(Student s);
    bool find(Student s) const;
    void erase(Student s);
    size_t size() const;
    void print() const;
    int height() const;
    std::vector<Student> findInRange(Student minS, Student maxS) const;
    
    static bool isSameTree(Node* t1, Node* t2);
    Node* getRoot() const { return root; }
};

#endif