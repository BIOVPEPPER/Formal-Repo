/* Your code here! */
#include "dsets.h"
#include <vector>

using std::vector;

void DisjointSets::addelements(int num) {
    elements.insert(elements.end(), num, -1);
}

int DisjointSets::find(int elem) {
    return find_helper(elem);
}

int DisjointSets::find_helper(int elem) {
    int root = elem;
    while (elements[root] >= 0) {
        root = elements[root];
    }

    while (elements[elem] >= 0) {
        int parent = elements[elem];
        elements[elem] = root;
        elem = parent;
    }

    return root;
}

void DisjointSets::setunion(int a, int b) {
    int root1 = find(a);
    int root2 = find(b);

    if (root1 != root2) {
        if (elements[root1] > elements[root2]) {
            std::swap(root1, root2);
        }
        elements[root1] += elements[root2];
        elements[root2] = root1;
    }
}

int DisjointSets::size(int elem) {
    return -elements[find(elem)];
}
