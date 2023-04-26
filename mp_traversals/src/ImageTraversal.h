/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <deque>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

using namespace cs225;

/**
 * @brief Namespace containing everything required for an image traversal
 * 
 */
namespace Traversals {
  /**
  * This defines the expected types for an add function for a traversal
  * The first parameter is the deque which stores the list of points to be processed
  * The second parameter is the new point which needs to be added to the deque
  */
  typedef void (*add_function) (std::deque<Point> &, const Point &);
  
  /**
  * This defines the expected types for an add function for a traversal
  * The first parameter is the deque which stores the list of points to be processed
  * The function then returns the next point to be processed (and removes it from the deque)
  */
  typedef Point (*pop_function) (std::deque<Point> &);

  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);

  void bfs_add(std::deque<Point> & work_list, const Point & point);
  void dfs_add(std::deque<Point> & work_list, const Point & point);
  Point bfs_pop(std::deque<Point> & work_list);
  Point dfs_pop(std::deque<Point> & work_list);

  /**
  * A base class for traversal algorithms on images.
  * This class provides a traversal of the image by returning instances of ImageTraversal::Iterator.
  */
  class ImageTraversal {
  public:
    /**
    * A forward iterator through an ImageTraversal.
    */
    class Iterator : std::iterator<std::forward_iterator_tag, Point> {
    public:
      Iterator();
      Iterator & operator++();
      Point operator*();
      bool operator!=(const Iterator &other);
      Iterator & operator=(const Iterator &other);
      /** @todo [Part 1] */
      /** add member functions if neccesary*/
      //Constructor and Destructors
    Iterator(ImageTraversal* instance);
    Iterator(const Iterator &other);
    ~Iterator();
    Iterator & Iterator_begin(ImageTraversal* instance_);

    private:
      /** @todo [Part 1] */
      /** add private members here if neccesary*/
      friend class ImageTraversal;
      ImageTraversal * instance;
      bool endflag;
      Point current;
      bool checkadd(const Point& point) const;
    };

    /**
    * Constructor for the given traversal
    */
    ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop);

    /**
    * Returns an iterator for the traversal starting at the first point (specified in the constructor).
    */
    Iterator begin();

    /**
    * Returns an iterator for the traversal one past the end of the traversal.
    */
    Iterator end();

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    PNG png;
    Point start;
    std::vector<std::vector<bool>> visited;
    double tolerance;
    add_function add;
    pop_function pop;
    std::deque<Point> work_list;
    // bool isVisited(const Point &point) const {
    //       return visited[point.x][point.y];
    // }
  };
}