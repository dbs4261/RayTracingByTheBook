#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <Eigen/Core>
#include <glog/logging.h>
#include  <vector>

#include "raytracer/math/concepts/color.h"

namespace raytracer {

class Image {
 public:
  Image() : size_x_(1), size_y_(1), data_() {
    this->UpdateSize();
  }
  Image(size_t x, size_t y) : size_x_(x), size_y_(y), data_() {
    this->UpdateSize();
  }

  explicit operator const unsigned char* () const {
    return data_.data();
  }

  void SetSizeX(size_t x) {
    this->size_x_ = x;
    this->UpdateSize();
  }

  void SetSizeY(size_t y) {
    this->size_y_ = y;
    this->UpdateSize();
  }

  void SetSize(size_t x, size_t y) {
    this->size_x_ = x;
    this->size_y_ = y;
    this->UpdateSize();
  }

  void UpdateSize() {
    data_.resize(size_x_ * size_y_ * channels_);
  }

  size_t UnwrapIndices(size_t x, size_t y, size_t c = 1) const {
    DCHECK(c < 4) << "Maximum of 4 channels allowed";
    DCHECK(x < size_x_) << "X out of bounds";
    DCHECK(y < size_y_) << "Y out of bounds";
    return c + (x * channels_) + (y * size_x_ * channels_);
  }

  void SetPixel(size_t x, size_t y, size_t c, unsigned char val) {
    data_.at(UnwrapIndices(x, y, c)) = val;
  }

  void SetPixel(size_t x, size_t y, const Eigen::Matrix<unsigned char, 3, 1>& bgr) {
    Eigen::Map<Eigen::Matrix<unsigned char, 3, 1>>(data_.data() + UnwrapIndices(x, y, 1)) = bgr.reverse();
  }

  void SetPixel(size_t x, size_t y, const Eigen::Matrix<unsigned char, 4, 1>& bgra) {
    Eigen::Map<Eigen::Matrix<unsigned char, 4, 1>>(data_.data() + UnwrapIndices(x, y, 0)) = bgra.reverse();
  }

  void SetPixel(size_t x, size_t y, const Color& color) {
    Eigen::Map<Eigen::Matrix<unsigned char, 3, 1>>(data_.data() + UnwrapIndices(x, y, 1)) = color.val_.reverse();
  }

 protected:
  size_t size_x_;
  size_t size_y_;
  constexpr static size_t channels_ = 4;
  std::vector<unsigned char> data_;
};

}

#endif //RAYTRACER_IMAGE_H
