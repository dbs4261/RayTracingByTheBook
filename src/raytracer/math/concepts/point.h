#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

#include <Eigen/Core>
namespace raytracer {

template <typename T>
class Ray;

template <typename T>
class Point {
 public:
  template <typename O>
  friend class Point;

  Point() : point_(Eigen::Matrix<T, 3, 1>::Zero()) {}
  explicit Point(Eigen::Matrix<T, 3, 1> point) : point_(std::move(point)) {}
  Point(T x, T y, T z) : point_(Eigen::Matrix<T, 3, 1>(x, y, z)) {}
  Point(const Ray<T>& ray, const T& distance) : point_(ray.origin_ + distance * ray.direction_) {}

  template <typename O>
  explicit Point(const Point<O>& other) {
    this->point_ = other.point_.template cast<O>();
  }

  template <typename D>
  explicit operator Point<D>() const {
    return Point<D>(this->point_.template cast<D>());
  }

  Eigen::Matrix<T, 3, 1> point_;
};

}

#endif //RAYTRACER_POINT_H
