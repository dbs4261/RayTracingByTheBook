#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Eigen/Core>

#include "point.h"
#include "direction.h"

namespace raytracer {

template <typename T>
class Ray {
 public:
  template <typename O>
  friend class Ray;

  Ray() : origin_(), direction_() {}
  explicit Ray(const Eigen::Matrix<T, 3, 1>& direction)
      : origin_(), direction_(direction) {}
  explicit Ray(const Direction<T>& direction)
      : origin_(), direction_(direction) {}
  Ray(const Eigen::Matrix<T, 3, 1>& origin, const Eigen::Matrix<T, 3, 1>& direction)
      : origin_(origin), direction_(direction) {}
  Ray(const Point<T>& origin, const Direction<T>& direction)
      : origin_(origin), direction_(direction) {}

  template <typename O>
  Ray(const Ray<O>& other) {
    this->origin_ = other.origin_;
    this->direction_ = other.direction_;
  }

  template <typename D>
  explicit operator Ray<D>() const {
    return Ray<D>(this->origin_, this->direction_);
  }

  Point<T> origin_;
  Direction<T> direction_;
};

}

#endif //RAYTRACER_RAY_H
