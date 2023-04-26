/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * subtree){
    if(subtree == NULL){
        return;
    }
    mirror(subtree->left);
    mirror(subtree->right);
    Node* left = subtree->left;
    subtree->left = subtree->right;
    subtree->right = left;
    return;
}
/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> IterT(root);
    T slow;
    T fast;
    int count = 0;
    for (typename TreeTraversal<T>::Iterator it = IterT.begin(); it != IterT.end(); ++it) {
        if (count == 0) {
            slow = (*it)->elem;
            count++;
            continue;
        }
        if (count == 1) {
            fast = (*it)->elem;
            count++;
            if(slow > fast) {
                return false;
            }
            continue;
        }
        slow = fast;
        fast = (*it)->elem;
        if (slow > fast) {
            return false;
        }
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    T max = findLargest(root);
    T min = findSmallest(root);
    return isOrderedRecursive(root,min,max);
}

template <typename T>
T BinaryTree<T>::findLargest(Node* root) const{
    T currmax = root->elem;
    T rightmax;
    T leftmax;
    if(root->right != NULL){
        rightmax = findLargest(root->right);
        if(rightmax > currmax){
            currmax = rightmax;
        }
    }
    if(root->left != NULL){
        leftmax = findLargest(root->left);
        if(leftmax > currmax){
            currmax = leftmax;
        }
    }
    return currmax;
}


template<typename T>
T BinaryTree<T>::findSmallest(Node* root) const{
    T currmin = root->elem;
    T rightmin;
    T leftmin;
    if(root->right != NULL){
        rightmin = findSmallest(root->right);
        if(rightmin < currmin){
            currmin = rightmin;
        }
    }
    if(root->left != NULL){
        leftmin = findSmallest(root->left);
        if(leftmin < currmin){
            currmin = leftmin;
        }
    }
    return currmin;
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subTree, T min, T max) const
{
    // your code here
    if(subTree == NULL){
        return true;
    }
    if(subTree->elem < min || subTree->elem > max){
        return false;
    }
    bool L_true = isOrderedRecursive(subTree->left,min,subTree->elem);
    bool R_true = isOrderedRecursive(subTree->right,subTree->elem,max);
    //if(L_true == )
    return (L_true && R_true);
}

