/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;
template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    return find(root,key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == NULL){
        return subtree;
    }
    if(subtree->key == key){
        return subtree;
    }else{
        if(subtree->key > key){
            if(subtree->left != NULL){
                return find(subtree->left,key);
            }else{
                return subtree->left;
            }
        }else{
            if(subtree->right != NULL){
                return find(subtree->right,key);
            }else{
                return subtree->right;
            }
        }
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here

    insert(root,key,value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    // if(subtree == NULL){
    //     subtree = new Node(key,value);
    //     return;
    // }
    if(subtree == NULL){
        Node * new_node = new Node(key,value);
        subtree = new_node;
    }
    if(find(subtree,key)!=NULL){
        return;
    }else{
        Node* new_node = new Node(key,value);
        Node*& node_ref = find(subtree,key);
        node_ref = new_node;
    }
    // Node* pos = subtree;
    // while (pos != NULL) {
    //     if (value < pos->value) {
    //         if (pos->left == NULL) {
    //             pos->left = new Node(key,value);
    //             break;
    //         } else {
    //             pos = pos->left;
    //         }
    //     } else {
    //         if (pos->right == NULL) {
    //             pos->right = new Node(key,value);
    //             break;
    //         } else {
    //             pos = pos->right;
    //         }
    //     }
    // }
    

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    Node* temp = first->left;
    first->left = second->left;
    second->left = temp;

    // swap the right pointers of the nodes
    temp = first->right;
    first->right = second->right;
    second->right = temp;

    // swap the nodes themselves
    temp = first;
    first = second;
    second = temp;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root,key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
    // your code here
{
    // search for the node to remove
    Node* & node = find(subtree, key);

    if (node == NULL) {
        // node not found, nothing to remove
        return;
    }

    // check if the node to remove has one or no children
    if (node->left == NULL) {
        Node* temp = node->right;
        delete node;
        node = temp;
    } else if (node->right == NULL) {
        Node* temp = node->left;
        delete node;
        node = temp;
    } else {
        // node has two children, find the successor and swap the values
        Node* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        node->key = successor->key;
        node->value = successor->value;
        // remove the successor recursively
        remove(node->right, successor->key);
    }
}


template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here

    BST<K, V> bst;
    for(auto & p : inList){
        bst.insert(p.first, p.second);
    }
    return bst;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    int n = inList.size();
    std::vector<int> res(n, 0);

    // Sort the input list by key to ensure all permutations are generated
    std::sort(inList.begin(), inList.end());

    do {
        // Build a tree for the current permutation
        BST<K, V> tree;
        for (auto& pair : inList) {
            tree.insert(pair.first, pair.second);
        }

        // Increment the histogram count for the height of the tree
        int height = tree.height();
        res[height]++;
    } while (std::next_permutation(inList.begin(), inList.end()));

    return res;
}



