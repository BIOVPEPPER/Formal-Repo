#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to bfe visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    // Point point;
    // while (!work_list.empty()) {
    //   point = work_list.front();
    //   work_list.pop_front();
    //   if (visited[point.x][point.y]) {
    //     continue;
    //   } else {
    //     visited[point.x][point.y] = true;
    //     return point;
    //   }
    // }
    // endflag = true;
    // return Point();
    Point next = work_list.front();
    work_list.pop_front();
    return next;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    // Point point;
    // while (!work_list.empty()) {
    //   point = work_list.back();
    //   work_list.pop_back();
    //   if (visited[point.x][point.y]) {
    //     continue;
    //   } else {
    //     visited[point.x][point.y] = true;
    //     return point;
    //   }
    // }
    // endflag = true;
    // return Point();
    Point next = work_list.back();
    work_list.pop_back();
    return next;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    /** @todo [Part 1] */
    visited.resize(png.width(), std::vector<bool>(png.height(), false));
    this->png = png;
    this->start = Point(start.x,start.y);
    this->tolerance = tolerance;
    this->add = traversal_add;
    this->pop = traversal_pop;
    // work_list.push_back(start);
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    ImageTraversal* start_instance = new ImageTraversal(png,start,tolerance,add,pop);
    return ImageTraversal::Iterator(start_instance);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */

  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    instance = nullptr;
    endflag = true;
    current = Point();
  }


  ImageTraversal::Iterator::~Iterator(){
    delete instance;
  }
  
  ImageTraversal::Iterator::Iterator(ImageTraversal* instance_){
    instance = instance_;
    // if(!instance_->work_list.empty()){
    current = instance_->start;
    endflag = false;
    // }else{
    //   current = Point();
    //   endflag = true;
    // }
  }

  ImageTraversal::Iterator::Iterator(const Iterator &other) {
  endflag = other.endflag;
  current = other.current;
  instance = new ImageTraversal(*other.instance);
}


  // ImageTraversal::Iterator::Iterator_begin(ImageTraversal* instance_){
  //   instance = instance_;
  //   endflag = instance_;
  //   current = instance_->start;
  // }

 
  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
 ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point cur = current;
  //Point cur = instance->pop();
  instance->visited[cur.x][cur.y] = true;
  Point r = Point( cur.x + 1,cur.y);
  Point b = Point(cur.x, cur.y + 1);
  Point l = Point(cur.x-1,cur.y);
  Point u = Point(cur.x, cur.y-1);

  if (checkadd(r)){
    instance->add(instance->work_list,r);
  }

  if (checkadd(b)) {
    instance->add(instance->work_list,b);
  }
  if (checkadd(l)) {
    instance->add(instance->work_list,l);
  }
  if (checkadd(u)) {
    instance->add(instance->work_list,u);
  }
// for (size_t i = 0; i < instance->work_list.size(); i++) {
//  {
//     std::cout << instance->work_list[i]<< " ";
//   }
//   std::cout << std::endl;
// }
  while(!instance->work_list.empty()){
  Point point_temp = instance->pop(instance->work_list);
  if(checkadd(point_temp)){
    current = point_temp;
    break;
  }
  }

  if (instance->work_list.empty()) {
    endflag = true;
  }

  return *this;


  // Point cur;

  // do {
  //   if (instance->work_list.empty()) {
  //     endflag = true;
  //     return *this;
  //   }

  //   cur = instance->pop(instance->work_list);
  // } while (instance->visited[cur.x][cur.y]);

  // instance->visited[cur.x][cur.y] = true;

  // Point r = Point(cur.x + 1, cur.y);
  // Point b = Point(cur.x, cur.y + 1);
  // Point l = Point(cur.x - 1, cur.y);
  // Point u = Point(cur.x, cur.y - 1);

  // if (checkadd(r)) {
  //   instance->add(instance->work_list, r);
  // }

  // if (checkadd(b)) {
  //   instance->add(instance->work_list, b);
  // }

  // if (checkadd(l)) {
  //   instance->add(instance->work_list, l);
  // }

  // if (checkadd(u)) {
  //   instance->add(instance->work_list, u);
  // }

  // current = cur;

  // return *this;

}
  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  ImageTraversal::Iterator &ImageTraversal::Iterator::operator=(const Iterator &other) {
  if (this != &other) {
    delete instance;
    endflag = other.endflag;
    current = other.current;
    instance = new ImageTraversal(*other.instance);
  }
  return *this;
}


  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
  // Check if traversals are the same
  // if(endflag == true){
  //   return false;
  // }
  if (other.endflag == endflag) {
    return false;
  }

  return true;
  }

  bool ImageTraversal::Iterator::checkadd(const Point& point) const {
    if(point.x >= instance->png.width() || point.y >= instance->png.height()){
      return false;
    }
      if (calculateDelta(instance->png.getPixel(point.x,point.y), instance->png.getPixel(instance->start.x,instance->start.y)) < instance->tolerance
      && instance->visited[point.x][point.y] == false) {
            return true;
          }
        return false;
}

}