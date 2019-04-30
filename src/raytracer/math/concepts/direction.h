#ifndef RAYTRACER_DIRECTION_H
#define RAYTRACER_DIRECTION_H

#include <Eigen/Core>

#include "point.h"

namespace raytracer {

template <typename T>
class Direction {
 public:
  template <typename O>
  friend class Direction;

  Direction() : direction_(Eigen::Matrix<T, 3, 1>::UnitX()) {}
  explicit Direction(Eigen::Matrix<T, 3, 1> direction) : direction_(std::move(direction)) {}
  Direction(T x, T y, T z) : direction_(Eigen::Matrix<T, 3, 1>(x, y, z)) {}
  Direction(const Point<T>& from, const Point<T>& to) : direction_(to.point_ - from.point_) {}

  template <typename O>
  explicit Direction(const Direction<O>& other) {
    direction_ = other.direction_.template cast<T>();
  }

  template <typename D>
  explicit operator Direction<D>() const {
    return Direction<D>(this->direction_.template cast<D>());
  }

  Direction<T>& Normalized() {
    direction_.normalized();
    return *this;
  }

  T Project(const Direction<T>& other) const {
    return this->direction_.dot(other.direction_);
  }

  Direction<T> operator*(T magnitude) const {
    return Direction<T>(this->direction_ * magnitude);
  }

  Eigen::Matrix<T, 3, 1> direction_;
};

}

#endif //RAYTRACER_DIRECTION_H
