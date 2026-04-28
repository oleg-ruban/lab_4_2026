#ifndef AVLTREE_H
#define AVLTREE_H

#include "Student.h"
#include <vector>
#include <algorithm>

struct AVLNode
{
    Student data;
    AVLNode *left, *right;
    int height;

    AVLNode(Student s) : data(s), left(nullptr), right(nullptr), height(1)
    {
    }
};

class AVLTree
{
private:
    AVLNode* root;
    size_t treeSize;

    int getHeight(AVLNode* n) const { return n ? n->height : 0; }
    int getBalance(AVLNode* n) const { return n ? getHeight(n->left) - getHeight(n->right) : 0; }
    void updateHeight(AVLNode* n) { if (n) n->height = 1 + std::max(getHeight(n->left), getHeight(n->right)); }

    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balanceNode(AVLNode* node);

    AVLNode* insert(AVLNode* node, Student s);
    AVLNode* erase(AVLNode* node, Student s);
    AVLNode* findMin(AVLNode* node) const; // Теж може бути const
    void clear(AVLNode* node);

public:
    AVLTree() : root(nullptr), treeSize(0)
    {
    }

    ~AVLTree() { clear(root); }

    void insert(Student s) { root = insert(root, s); }
    void erase(Student s) { root = erase(root, s); }

    // Тепер це працює правильно
    int height() const { return getHeight(root); }
    size_t size() const { return treeSize; }

    void split(Student key, AVLTree& l, AVLTree& r);
    void merge(AVLTree& other);

    // Додано const до методів обходу
    void toVector(AVLNode* node, std::vector<Student>& res) const;
    std::vector<Student> toVector() const;
};

#endif
