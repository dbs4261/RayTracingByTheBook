#ifndef RAYTRACER_ORTHOGRAPHIC_CAMERA_H
#define RAYTRACER_ORTHOGRAPHIC_CAMERA_H

#include "abstract_camera.h"

#include "raytracer/math/transformations/transform.h"

namespace raytracer {

template <typename T>
class ProjectiveCamera : public AbstractCamera<T> {
 public:
  ProjectiveCamera(size_t height, size_t width)
      : AbstractCamera<T>(height, width), direction_(this->tform_.TransformDirection(Direction<T>()) {}
  ProjectiveCamera(size_t height, size_t width, T pitch_pitch)
      : AbstractCamera<T>(height, width, pixel_pitch_), direction_(this->tform_.TransformDirection(Direction<T>())  {}
  ProjectiveCamera(typename Transform<T>::SPtr tform, size_t height, size_t width)
      : AbstractCamera<T>(std::move(tform), height, width), direction_(this->tform_.TransformDirection(Direction<T>()) {}
  ProjectiveCamera(size_t height, size_t width, T pixel_pitch, typename Transform<T>::SPtr tform)
      : AbstractCamera<T>(std::move(tform), height, width, pixel_pitch), direction_(this->tform_.TransformDirection(Direction<T>()) {}

  void MakeRays(typename std::vector<Ray<T>>& container) const  {
    T shift_w = static_cast<T>(width_) / T{2};
    T shift_h = static_cast<T>(height_) / T{2};
    Point<T> center = this->tform_->TransformPoint();
    for (size_t h = 0; h < this->height_; h++) {
      for (size_t w = 0; w < this->width_; w++) {
        container.push_back(this->MakeRay(h, w));
      }
    }
  }

  Ray<T> MakeRay_(size_t y, size_t x, const Point<T>& center) const {
    return Ray<T>(this->tform_.TransformPoint(Point<T>(static_cast<T>(w) - shift_w, static_cast<T>(h) - shift_h, T{0})), direction_);
  }

  Ray<T> MakeRay(size_t y, size_t x) const {
    DCHECK(y < this->height_) << "Height out of range";
    DCHECK(x < this->width_) << "Width out of range";
    Point<T> center = this->tform_->TransformPoint();
    return this->MakeRay_(y, x, center);
  }

  T focal_length;
  T skew;
  T aspect_ratio;
  T principal_point_x;
  T principal_point_y;

};

}
#endif //RAYTRACER_ORTHOGRAPHIC_CAMERA_H
