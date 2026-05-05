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
    int size;

    AVLNode(Student s)
        : data(s), left(nullptr), right(nullptr), height(1), size(1)
    {}
};

class AVLTree
{
private:
    AVLNode* root;

    int getHeight(AVLNode* n) const { return n ? n->height : 0; }
    int getSize(AVLNode* n) const { return n ? n->size : 0; }

    void update(AVLNode* n);

    int getBalance(AVLNode* n) const
    {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balanceNode(AVLNode* node);

    AVLNode* insert(AVLNode* node, const Student& s);
    AVLNode* erase(AVLNode* node, const Student& s);
    AVLNode* findMin(AVLNode* node) const;
    AVLNode* removeMin(AVLNode* node);

    void clear(AVLNode* node);

    void split(AVLNode* node, const Student& key, AVLNode*& left, AVLNode*& right);
    AVLNode* merge(AVLNode* left, AVLNode* right);

    void toVector(AVLNode* node, std::vector<Student>& res) const;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    void insert(const Student& s) { root = insert(root, s); }
    void erase(const Student& s) { root = erase(root, s); }

    int height() const { return getHeight(root); }
    int size() const { return getSize(root); }

    void split(const Student& key, AVLTree& l, AVLTree& r);
    void merge(AVLTree& other);

    std::vector<Student> toVector() const;
};

#endif