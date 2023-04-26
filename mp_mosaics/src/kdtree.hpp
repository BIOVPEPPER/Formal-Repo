/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <string>
using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
      return true;
    }else if(first[curDim] == second[curDim]){
      return first < second;
    }

    return false;
}



template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double currdist = euclideanDistanceSquared(currentBest,target);
    double potdist = euclideanDistanceSquared(potential,target);
    if(currdist > potdist){
      return true;
    }else if (currdist == potdist){
      return potential < currentBest;
    }
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     size = newPoints.size();
     vector<Point<Dim>> Points= newPoints;
     root = treeHelper(Points,0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   _copy(other);
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != &rhs){
    _copy(rhs);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete root;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>:: treeHelper(vector<Point<Dim>>& newPoints, int partDim){
if(newPoints.size() == 0){
  return NULL;
}
auto middle = newPoints.begin() + newPoints.size() / 2;
int k = (newPoints.size() - 1) / 2;

auto cmp = [&](const Point<Dim>& a, const Point<Dim>& b) {
    return smallerDimVal(a, b, partDim);
};
//select(newPoints.begin(),newPoints.end(),middle,cmp);
Point<Dim> median = _Qselect(newPoints, 0, newPoints.size() - 1, k, partDim);
//KDTreeNode * subroot = new KDTreeNode(newPoints[k]);
KDTreeNode * subroot = new KDTreeNode(median);
vector<Point<Dim>> left;
vector<Point<Dim>> right;
for (int i = 0; i < k; i++) {
  left.push_back(newPoints[i]);
}
for (unsigned i = k+1; i < newPoints.size(); i++) {
  right.push_back(newPoints[i]);
}
subroot -> left = treeHelper(left, (partDim + 1) % Dim);
subroot -> right = treeHelper(right, (partDim + 1) % Dim);
return subroot;
}


template<int Dim>
void KDTree<Dim>::_copy(KDTree const & other){
  if(root != other){
    delete(root);
    size = other->size;
    if(root == NULL){
      return;
    }
    KDTreeNode *root = new KDTreeNode(*other);
    root->left = _copy(other->left);
    root->right = _copy(other->right);

  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return findNearestNeighbor(root,query,0)->point;
    
}



template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::findNearestNeighbor(KDTreeNode * const &  subroot, Point<Dim> const & target, 
                                            int partDim) const
{
    /**
     * @todo Implement this function!
     */
    if (subroot == NULL) {
        return NULL;
    }

    KDTreeNode * nearest = subroot;
    KDTreeNode * potentialNearest;

    if (smallerDimVal(target, subroot->point, partDim)) {
        potentialNearest = findNearestNeighbor(subroot->left, target, (partDim + 1) % Dim);
    } else {
        potentialNearest = findNearestNeighbor(subroot->right, target, (partDim + 1) % Dim);
    }

    if (potentialNearest != NULL && shouldReplace(target, nearest->point, potentialNearest->point)) {
        nearest = potentialNearest;
    }

    double radius_sq = euclideanDistanceSquared(target, nearest->point);
    double planeDistance_sq = (target[partDim] - subroot->point[partDim]) * (target[partDim] - subroot->point[partDim]);

    if (radius_sq >= planeDistance_sq) {
        KDTreeNode * otherSidePotentialNearest = findNearestNeighbor(subroot->left == potentialNearest ? subroot->right : subroot->left, target, (partDim + 1) % Dim);
        if (otherSidePotentialNearest != NULL && shouldReplace(target, nearest->point, otherSidePotentialNearest->point)) {
            nearest = otherSidePotentialNearest;
        }
    }

    return nearest;
}

template <int Dim>
double euclideanDistanceSquared(const Point<Dim> &a, const Point<Dim> &b){
    double distance = 0;

    for (int i = 0; i < Dim; ++i) {
        distance += (a[i] - b[i]) * (a[i] - b[i]);
    }

    return distance;
}

template<typename RandIter, typename Comparator>
void select(RandIter begin, RandIter end, RandIter k, Comparator cmp) {
    while (begin != end)
    {
        RandIter pivot = ::partition(begin, end, cmp);
        if (pivot == k)
            return;
        else if (pivot < k)
            begin = pivot + 1;
        else
            end = pivot;
}
}

template<int Dim>
Point<Dim>& _Qselect(vector<Point<Dim>> & list, int left, int right, int k, int curDim) {
    while (left < right) {
        int pivotInd = ::_Qpartition(list, left, right, k, curDim);
        if (pivotInd == k) {
            return list[k];
        } else if (pivotInd < k) {
            left = pivotInd + 1;
        } else {
            right = pivotInd - 1;
        }
    }
    return list[left];
}

template<int Dim>
int _Qpartition(vector<Point<Dim>> & list, int left, int right, int pivot, int curDim) {

    Point<Dim> val_pivot = list[pivot];
    std::swap(list[pivot], list[right]);
    int i = left, j = right - 1;
    while (i <= j) {
        while (i <= j && smallerDimVal(list[i], val_pivot, curDim)) {
            i++;
        }
        while (i <= j && !smallerDimVal(list[j], val_pivot, curDim)) {
            j--;
        }
        if (i <= j) {
            std::swap(list[i], list[j]);
            i++;
            j--;
        }
    }
    std::swap(list[right], list[i]);
    return i;
}

template<typename RandIter, typename Comparator>
RandIter partition(RandIter begin, RandIter end, Comparator cmp) {

    RandIter pivot = end - 1;
    RandIter i = begin;
    for (RandIter j = begin; j < end - 1; j++)
    {
        if (cmp(*j, *pivot))
        {
            std::iter_swap(i, j);
            i++;
        }
    }
    std::iter_swap(i, pivot);
    return i;
}

// template <typename T>
// void my_swap(T& a, T& b) {
//     T temp = a;
//     a = b;
//     b = temp;
// }



