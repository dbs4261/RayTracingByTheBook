#ifndef RAYTRACER_ORTHOGRAPHIC_CAMERA_H
#define RAYTRACER_ORTHOGRAPHIC_CAMERA_H

#include <glog/logging.h>

#include "abstract_camera.h"

#include "raytracer/math/transformations/transform.h"

namespace raytracer {

template <typename T>
class OrthographicCamera : public AbstractCamera<T> {
 public:
  OrthographicCamera(size_t height, size_t width) :
      AbstractCamera<T>(height, width), direction_(this->tform_->TransformDirection(Direction<T>())) {}
  OrthographicCamera(size_t height, size_t width, T pixel_pitch) :
      AbstractCamera<T>(height, width, pixel_pitch), direction_(this->tform_->TransformDirection(Direction<T>()))  {}
  OrthographicCamera(typename Transform<T>::SPtr tform, size_t height, size_t width) :
      AbstractCamera<T>(std::move(tform), height, width), direction_(this->tform_->TransformDirection(Direction<T>())) {}
  OrthographicCamera(typename Transform<T>::SPtr tform, size_t height, size_t width, T pixel_pitch) :
      AbstractCamera<T>(std::move(tform), height, width, pixel_pitch), direction_(this->tform_->TransformDirection(Direction<T>())) {}

  void MakeRays(typename std::vector<Ray<T>>& container) const {
    T shift_w = static_cast<T>(this->width_) / T{2};
    T shift_h = static_cast<T>(this->height_) / T{2};
    for (size_t y = 0; y < this->height_; y++) {
      for (size_t x = 0; x < this->width_; x++) {
        container.push_back(this->MakeRay(y, x));
      }
    }
  }

  Ray<T> MakeRay(size_t y, size_t x) const {
    DCHECK(y < this->height_) << "Height out of range";
    DCHECK(x < this->width_) << "Width out of range";
    return Ray<T>(this->tform_->TransformPoint(Point<T>(static_cast<T>(x) - this->shift_w,
        static_cast<T>(y) - this->shift_h, T{0})), direction_);
  }

  Direction<T> direction_;
  T shift_w;
  T shift_h;
};

}
#endif //RAYTRACER_ORTHOGRAPHIC_CAMERA_H
