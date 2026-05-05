#include "AVLTree.h"

// --- update ---
void AVLTree::update(AVLNode* n)
{
    if (!n) return;
    n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    n->size = 1 + getSize(n->left) + getSize(n->right);
}

// --- rotations ---
AVLNode* AVLTree::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update(y);
    update(x);

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update(x);
    update(y);

    return y;
}

AVLNode* AVLTree::balanceNode(AVLNode* node)
{
    if (!node) return nullptr;

    update(node);

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1)
    {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// --- insert ---
AVLNode* AVLTree::insert(AVLNode* node, const Student& s)
{
    if (!node) return new AVLNode(s);

    if (s < node->data)
        node->left = insert(node->left, s);
    else if (s > node->data)
        node->right = insert(node->right, s);
    else
        return node;

    return balanceNode(node);
}

// --- findMin ---
AVLNode* AVLTree::findMin(AVLNode* node) const
{
    return node->left ? findMin(node->left) : node;
}

// --- removeMin ---
AVLNode* AVLTree::removeMin(AVLNode* node)
{
    if (!node->left)
        return node->right;

    node->left = removeMin(node->left);
    return balanceNode(node);
}

// --- erase ---
AVLNode* AVLTree::erase(AVLNode* node, const Student& s)
{
    if (!node) return nullptr;

    if (s < node->data)
        node->left = erase(node->left, s);
    else if (s > node->data)
        node->right = erase(node->right, s);
    else
    {
        AVLNode* l = node->left;
        AVLNode* r = node->right;
        delete node;

        if (!r) return l;

        AVLNode* min = findMin(r);
        min->right = removeMin(r);
        min->left = l;

        return balanceNode(min);
    }

    return balanceNode(node);
}

// --- clear ---
void AVLTree::clear(AVLNode* node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void AVLTree::split(AVLNode* node, const Student& key, AVLNode*& left, AVLNode*& right)
{
    if (!node)
    {
        left = right = nullptr;
        return;
    }

    if (key < node->data)
    {
        split(node->left, key, left, node->left);
        right = balanceNode(node);
    }
    else
    {
        split(node->right, key, node->right, right);
        left = balanceNode(node);
    }
}

void AVLTree::split(const Student& key, AVLTree& l, AVLTree& r)
{
    clear(l.root);
    clear(r.root);

    split(this->root, key, l.root, r.root);

    this->root = nullptr;
}

AVLNode* AVLTree::merge(AVLNode* left, AVLNode* right)
{
    if (!left) return right;
    if (!right) return left;

    AVLNode* min = findMin(right);
    right = removeMin(right);

    min->left = left;
    min->right = right;

    return balanceNode(min);
}

void AVLTree::merge(AVLTree& other)
{
    root = merge(root, other.root);
    other.root = nullptr;
}

// =====================
// --- traversal ---
// =====================
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