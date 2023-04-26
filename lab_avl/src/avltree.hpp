/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>
#include <iostream>
using namespace std;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * Q = t->right;
    t->right = Q->left;
    Q->left = t;
    t = Q;

    t->left->height = 1 + std::max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* Q = t->left;
    t->left = Q->right;
    Q->right = t;
    t = Q;

    // Recalculate heights
    t->right->height = 1 + std::max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);

    if (balance > 1) {
        // Left subtree is taller than right subtree
        if (heightOrNeg1(subtree->left->left) >= heightOrNeg1(subtree->left->right)) {
            // Left-left case
            rotateRight(subtree);
        } else {
            // Left-right case
            rotateLeftRight(subtree);
        }
    } else if (balance < -1) {
        // Right subtree is taller than left subtree
        if (heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)) {
            // Right-right case
            rotateLeft(subtree);
        } else {
            // Right-left case
            rotateRightLeft(subtree);
        }
    }

    // Update the height of the subtree
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree->height = -1;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * IOP = subtree->left;
            while(IOP->right != NULL) {
                IOP = IOP->right;
            }
            swap(subtree, IOP);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL) {
                swap(subtree, subtree->left);
                remove(subtree->left, key);
            } else {
                swap(subtree, subtree->right);
                remove(subtree->right, key);
            }
        }
        // your code here
    }
    if ((subtree->left != NULL) && (subtree->left->height == -1)) {
        delete subtree->left;
        subtree->left = NULL;
    }
    if ((subtree->right != NULL) && (subtree->right->height == -1)) {
        delete subtree->right;
        subtree->right = NULL;
    }
    rebalance(subtree);
}
