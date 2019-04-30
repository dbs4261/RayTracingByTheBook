#ifndef RAYTRACER_ROTATE_H
#define RAYTRACER_ROTATE_H

#include <Eigen/Core>

#include "raytracer/math/concepts/direction.h"
#include "raytracer/math/utils.h"
#include "transform.h"

namespace raytracer {

template <typename T>
class Rotation : public Transform<T> {
 public:
  Rotation() : Transform<T>(), axis_(Direction<T>()), angle_(0.0) {}
  Rotation(Transform::SPtr prev) : Transform<T>(prev), axis_(Direction<T>()), angle_(0.0) {}
  Rotation(const Direction<T>& axis, T angle) : Transform<T>(), axis_(axis), angle_(angle) {axis_.Normalized();}
  Rotation(Transform::SPtr prev, const Direction<T>& axis, T angle) : Transform<T>(prev), axis_(axis), angle_(angle) {axis_.Normalized();}

  const Direction<T>& GetAxis() const {
    return this->axis_;
  }
  void SetAxis(const Direction<T>& axis) {
    this->axis_ = axis;
    this->cached = false;
  }

  const T& GetAngle() const {
    return this->angle_;
  }
  void SetAngle(T angle) {
    this->angle_ = angle;
    this->cached = false;
  }

  void SetAxisAngle(const Direction& axis, T angle) {
    this->axis_ = axis;
    this->angle_ = angle;
    this->cached = false;
  }

  Eigen::Matrix4d AsMatrix() {
    if (!cached) {
      local_mat_cache.block<3, 3>(0, 0) = Eigen::AngleAxis<T>(angle_, axis_.direction_).toRotationMatrix();
    }
    return local_mat_cache;
  }

 protected:
  Direction<T> axis_;
  T angle_;
  bool cached = false;
  Eigen::Matrix<T, 4, 4> local_mat_cache = Eigen::Matrix<T, 4, 4>::Identity();
};

template <typename T, typename ... Args>
Transform<T>::SPtr MakeRotation(Args&& ... args) {
  return std::make_shared<Rotation<T>>(std::forward(args));
};

}

#endif //RAYTRACER_ROTATE_H
