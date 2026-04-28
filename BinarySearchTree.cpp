#include "BinarySearchTree.h"
#include <iostream>
#include <algorithm>

BinarySearchTree::BinarySearchTree() : root(nullptr), treeSize(0)
{
}

BinarySearchTree::~BinarySearchTree() { clear(root); }

void BinarySearchTree::clear(Node* node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

Node* BinarySearchTree::insert(Node* node, Student s)
{
    if (!node)
    {
        treeSize++;
        return new Node(s);
    }
    if (s < node->data) node->left = insert(node->left, s);
    else if (s > node->data) node->right = insert(node->right, s);
    return node;
}

void BinarySearchTree::insert(Student s) { root = insert(root, s); }

bool BinarySearchTree::find(Student s) const
{
    Node* curr = root;
    while (curr)
    {
        if (s == curr->data) return true;
        curr = (s < curr->data) ? curr->left : curr->right;
    }
    return false;
}

Node* BinarySearchTree::findMin(Node* node)
{
    while (node && node->left) node = node->left;
    return node;
}

Node* BinarySearchTree::erase(Node* node, Student s)
{
    if (!node) return nullptr;
    if (s < node->data) node->left = erase(node->left, s);
    else if (s > node->data) node->right = erase(node->right, s);
    else
    {
        if (!node->left)
        {
            Node* temp = node->right;
            delete node;
            treeSize--;
            return temp;
        }
        else if (!node->right)
        {
            Node* temp = node->left;
            delete node;
            treeSize--;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = erase(node->right, temp->data);
    }
    return node;
}

void BinarySearchTree::erase(Student s) { root = erase(root, s); }

size_t BinarySearchTree::size() const { return treeSize; }

void BinarySearchTree::printInOrder(Node* node) const
{
    if (!node) return;
    printInOrder(node->left);
    std::cout << "Студент: " << node->data.name << " (Бал: " << node->data.avgGrade << ")" << std::endl;
    printInOrder(node->right);
}

void BinarySearchTree::print() const { printInOrder(root); }

int BinarySearchTree::calculateHeight(Node* node) const
{
    if (!node) return 0;
    return 1 + std::max(calculateHeight(node->left), calculateHeight(node->right));
}

int BinarySearchTree::height() const { return calculateHeight(root); }

void BinarySearchTree::getInRange(Node* node, const Student& minS, const Student& maxS, std::vector<Student>& res) const
{
    if (!node) return;
    if (node->data > minS) getInRange(node->left, minS, maxS, res);
    if (node->data >= minS && node->data <= maxS) res.push_back(node->data);
    if (node->data < maxS) getInRange(node->right, minS, maxS, res);
}

std::vector<Student> BinarySearchTree::findInRange(Student minS, Student maxS) const
{
    std::vector<Student> result;
    getInRange(root, minS, maxS, result);
    return result;
}

bool BinarySearchTree::isSameTree(Node* t1, Node* t2)
{
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    return (t1->data == t2->data) && isSameTree(t1->left, t2->left) && isSameTree(t1->right, t2->right);
}
