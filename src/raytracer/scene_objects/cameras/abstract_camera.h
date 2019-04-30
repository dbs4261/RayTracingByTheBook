#ifndef RAYTRACER_ABSTRACTCAMERA_H
#define RAYTRACER_ABSTRACTCAMERA_H

#include <memory>
#include <vector>

#include "raytracer/math/transformations/null_transform.h"
#include "raytracer/math/transformations/transform.h"

#include "raytracer/scene_objects/void_object.h"

namespace raytracer {

template <typename T>
class AbstractCamera : public VoidObject<T> {
 public:
  using SPtr = std::shared_ptr<AbstractCamera<T>>;

  AbstractCamera(size_t height, size_t width)
      : VoidObject<T>(), height_(height), width_(width), pixel_pitch_(T{1}) {}
  AbstractCamera(size_t height, size_t width, T pitch_pitch)
      : VoidObject<T>(), height_(height), width_(width), pixel_pitch_(pitch_pitch) {}
  AbstractCamera(typename Transform<T>::SPtr tform, size_t height, size_t width)
      : VoidObject<T>(std::move(tform)), height_(height), width_(width), pixel_pitch_(T{1}) {}
  AbstractCamera(typename Transform<T>::SPtr tform, size_t height, size_t width, T pixel_pitch)
      : VoidObject<T>(std::move(tform)), height_(height), width_(width), pixel_pitch_(pixel_pitch) {}

  virtual void MakeRays(typename std::vector<Ray<T>>& container) const = 0;

  virtual Ray<T> MakeRay(size_t y, size_t x) const = 0;

  virtual Point<T> RayCenter(T x = T{0}, T y = T{0}) const {
    return this->tform_->TransformPoint();
  }

  virtual Direction<T> RayDirection(T x = T{0}, T y = T{0}) const {
    return this->tform_->TransformDirection(Direction<T>());
  }

  size_t height_;
  size_t width_;
  T pixel_pitch_;
};

}

#endif //RAYTRACER_ABSTRACTCAMERA_H
