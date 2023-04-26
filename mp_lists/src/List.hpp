/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode* curr = head_;
  while (curr) {
    ListNode* next = curr->next;
    delete curr;
    curr = next;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  
  tail_= newNode;
  length_++;
  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if ((curr != NULL)&&(curr != start)) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (head_ == NULL || head_ == tail_) {
    // Empty list or single node list, nothing to do.
    return;
  }
  ListNode *curr = head_->next; 
  ListNode *temp = nullptr; // Start from the second node
  int count = 2;
  while (curr != NULL && curr != tail_) {
    // Remove the current node from its current position
    if(count % 2 == 0){
    temp = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    // Append the current node to the end of the list
    curr->prev = tail_;
    curr->next = NULL;
    tail_->next = curr;
    tail_ = curr;

    // Advance to the next node to be removed
    curr = temp;
    count += 1;
    // if (curr != NULL) {
    //   curr = curr->next;
    // }
    }else{
      curr = curr->next;
      count+=1;
      continue;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if(startPoint == NULL || endPoint == NULL){
      return;
    }
    if (startPoint == endPoint) {
        return;
    }
  ListNode * dummy1 = startPoint->prev;
  ListNode * dummy2  = endPoint->next;
  startPoint->prev = startPoint->next;
  endPoint->next = endPoint->prev;
  startPoint->next = dummy2;
  endPoint->prev = dummy1;

  ListNode * curr = startPoint->prev;
  ListNode * temp = NULL;
  while (curr != endPoint) {
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
  }

  if (dummy1 != NULL) {
    dummy1->next = endPoint;
    }
  if (dummy2 != NULL) {
    dummy2->prev = startPoint;
    }

  temp = endPoint;
  ListNode * temp2 = startPoint;
  endPoint = temp2;
  startPoint = temp;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(head_ == NULL || n == 0 || n == 1){
    return;
  }
  ListNode *head = head_;
  ListNode *tail = head_;
  while (tail->next != NULL){
    for(int i = 1; i < n ;i++){
      if(tail->next != NULL){
      tail = tail ->next;
      }
    }
    if ((head == head_) && (tail == tail_)) {
      reverse(head_, tail_);
      break;
    }else if (head == head_) {
      reverse(head_, tail);
    }else if (tail == tail_) {
      reverse(head, tail_);
      tail = tail_;
    }else {
      reverse(head,tail);
    }
    if (tail -> next != NULL) {
      tail = tail -> next;
      head = tail;
    }

  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
    // Initialize pointers to the first node of each list
  ListNode* curr1 = first;
  ListNode* curr2 = second;

  // Check if either list is empty and return the other if it is
  if (curr1 == NULL) {
    return curr2;
  } else if (curr2 == NULL) {
    return curr1;
  }

  // Determine which list's first node should come first
  if (!(curr1->data < curr2->data)) {
    std::swap(curr1, curr2);
  }
  
  // Merge the two lists
  while (curr1->next != NULL && curr2 != NULL) {
    if (!(curr1->next->data < curr2->data)) {
      // Insert curr2 before curr1's next node
      ListNode* next = curr1->next;
      ListNode* temp = curr2->next;
      curr1->next = curr2;
      curr2->prev = curr1;
      curr2->next = next;
      next->prev = curr2;

      // Move curr2 to its next node
      curr2 = temp;
    } else {
      // Move curr1 to its next node
      curr1 = curr1->next;
    }
  }
  // If there are remaining nodes in curr2, append them to the end of curr1
  if (curr2 != NULL) {
    while(curr2 != NULL){
    curr1->next = curr2;
    curr2->prev = curr1;
    curr2 = curr2->next;
    curr1 = curr1->next;
    }
  }

  // Return a pointer to the head of the merged list
  return (first->data < second->data) ? first : second;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if (chainLength == 1) {return start;}
  int splitPoint = chainLength / 2;
  ListNode * halflist = start;
  for (int i = 0; i < splitPoint; i++) {
    halflist = halflist -> next;
  }
  halflist -> prev -> next = NULL;
  halflist -> prev = NULL;
  ListNode * left = mergesort(start, splitPoint);
  ListNode * right = mergesort(halflist, chainLength - splitPoint);
  return merge(left, right);
}
