#include "AVLTree.h"
#include <iostream>

// --- Приватні методи балансування ---

AVLNode* AVLTree::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Виконуємо поворот
    x->right = y;
    y->left = T2;

    // Оновлюємо висоти
    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Виконуємо поворот
    y->left = x;
    x->right = T2;

    // Оновлюємо висоти
    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLNode* AVLTree::balanceNode(AVLNode* node)
{
    if (!node) return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    // Лівий випадок (Left)
    if (balance > 1)
    {
        // Left-Right Rotate
        if (getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        // Left-Left Rotate
        return rotateRight(node);
    }

    // Правий випадок (Right)
    if (balance < -1)
    {
        // Right-Left Rotate
        if (getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        // Right-Right Rotate
        return rotateLeft(node);
    }

    return node;
}

// --- Основні операції ---

void AVLTree::clear(AVLNode* node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

AVLNode* AVLTree::insert(AVLNode* node, Student s)
{
    if (!node)
    {
        treeSize++;
        return new AVLNode(s);
    }

    if (s < node->data)
    {
        node->left = insert(node->left, s);
    }
    else if (s > node->data)
    {
        node->right = insert(node->right, s);
    }
    else
    {
        return node; // Дублікати не додаємо
    }

    return balanceNode(node);
}

AVLNode* AVLTree::findMin(AVLNode* node) const
{
    AVLNode* current = node;
    while (current && current->left)
    {
        current = current->left;
    }
    return current;
}

AVLNode* AVLTree::erase(AVLNode* node, Student s)
{
    if (!node) return nullptr;

    if (s < node->data)
    {
        node->left = erase(node->left, s);
    }
    else if (s > node->data)
    {
        node->right = erase(node->right, s);
    }
    else
    {
        // Вузол знайдено
        if (!node->left || !node->right)
        {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp)
            {
                temp = node;
                node = nullptr;
            }
            else
            {
                *node = *temp; // Копіюємо дані нащадка
            }
            delete temp;
            treeSize--;
        }
        else
        {
            // Вузол з двома дітьми
            AVLNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = erase(node->right, temp->data);
        }
    }

    if (!node) return nullptr;
    return balanceNode(node);
}

// --- Методи для піддерев ---

void AVLTree::toVector(AVLNode* node, std::vector<Student>& res) const
{
    if (!node) return;
    toVector(node->left, res);
    res.push_back(node->data);
    toVector(node->right, res);
}

std::vector<Student> AVLTree::toVector() const
{
    std::vector<Student> res;
    toVector(root, res);
    return res;
}

void AVLTree::merge(AVLTree& other)
{
    std::vector<Student> otherData = other.toVector();
    for (const auto& s : otherData)
    {
        this->insert(s);
    }
    other.clear(other.root);
    other.root = nullptr;
    other.treeSize = 0;
}

void AVLTree::split(Student key, AVLTree& l, AVLTree& r)
{
    std::vector<Student> allData = this->toVector();
    l.clear(l.root);
    l.root = nullptr;
    l.treeSize = 0;
    r.clear(r.root);
    r.root = nullptr;
    r.treeSize = 0;

    for (const auto& s : allData)
    {
        if (s < key) l.insert(s);
        else r.insert(s);
    }
    this->clear(this->root);
    this->root = nullptr;
    this->treeSize = 0;
}
