#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  startImage_ = new PNG(png);
}

FloodFilledImage::~FloodFilledImage() {
  delete startImage_;
}
/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traversals_.push_back(&traversal);
  colorPickers_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;

  // Helper function to update the image and manage animation frames
  auto updateImageAndAddFrame = [&](unsigned &filledPixel, PNG &curImg, Traversals::ImageTraversal &traversal, ColorPicker &colorPicker) {
    for (const Point &point : traversal) {
      curImg.getPixel(point.x, point.y) = colorPicker.getColor(point.x, point.y);
      filledPixel++;
      if (filledPixel % frameInterval == 0) {
        animation.addFrame(PNG(curImg));
      }
    }
  };

  animation.addFrame(PNG(*startImage_));
  if (traversals_.empty()) {
    return animation;
  }

  PNG curImg = PNG(*startImage_);
  unsigned filledPixel = 0;
  for (unsigned i = 0; i < traversals_.size(); i++) {
    updateImageAndAddFrame(filledPixel, curImg, *traversals_[i], *colorPickers_[i]);
  }

  if (filledPixel % frameInterval != 0) {
    animation.addFrame(PNG(curImg));
  }

  return animation;
}

