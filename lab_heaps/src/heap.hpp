
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    size_t size = _elems.size();
    if(size > currentIdx*2){
        return true;
    }else{
        return false;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t leftChildIdx = 2 * currentIdx;
    size_t rightChildIdx = 2 * currentIdx + 1;

    if (leftChildIdx >= _elems.size()) {
        return currentIdx; // no child nodes
    }

    if (rightChildIdx >= _elems.size() || higherPriority(_elems[leftChildIdx], _elems[rightChildIdx])) {
        return leftChildIdx; // only left child or left child has higher priority
    } else {
        return rightChildIdx; // right child has higher priority
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //I copyed the heapifyUP below.
    if (!hasAChild(currentIdx))
        return;
    size_t maxChild = maxPriorityChild(currentIdx);
    if (!higherPriority(_elems[currentIdx], _elems[maxChild])) {
        std::swap(_elems[currentIdx], _elems[maxChild]);
        heapifyDown(maxChild);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm

    _elems.reserve(elems.size() + 1); // preallocate memory for efficiency
    _elems.push_back(T()); // add a dummy element at the beginning

    for (const auto& elem : elems) {
        _elems.push_back(elem); // add each element to the end of the heap
    }

    for (size_t i = parent(_elems.size() - 1); i > 0; i--) {
        heapifyDown(i); // heapify down from the parent of the last element to the root
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }

    T maxElement = _elems[root()];
    std::swap(_elems[root()], _elems.back());
    _elems.pop_back();
    heapifyDown(root());
    return maxElement;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    if(!hasAChild(idx)){
        heapifyUp(idx);
    }else if(root() == idx){
        heapifyDown(idx);
        }
     else {
        if (!higherPriority(_elems[idx],_elems[maxPriorityChild(idx)])) {
            heapifyDown(idx);
        } else if (higherPriority(_elems[idx], _elems[parent(idx)])) {
            heapifyUp(idx);
        }
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= 1;
    
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
