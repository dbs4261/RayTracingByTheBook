#ifndef RAYTRACER_TRANSLATION_H
#define RAYTRACER_TRANSLATION_H

#include <Eigen/Core>
#include "transform.h"

namespace raytracer {

template <typename T>
class Translation : public Transform<T> {
 public:
  Translation() : Transform<T>(), translation_(Eigen::Matrix<T, 3, 1>::Zero()) {}
  explicit Translation(Transform::SPtr prev) : Transform<T>(prev), translation_(Eigen::Matrix<T, 3, 1>::Zero()) {}
  explicit Translation(const Eigen::Matrix<T, 3, 1>& translation) : Transform<T>(), translation_(translation) {}
  Translation(Transform::SPtr prev, const Eigen::Matrix<T, 3, 1>& translation) : Transform<T>(prev), translation_(translation) {}
  Translation(T x, T y, T z) : Transform<T>(), translation_(Eigen::Matrix<T, 3, 1>(x, y, z)) {}
  Translation(Transform::SPtr prev, T x, T y, T z) : Transform<T>(prev), translation_(Eigen::Matrix<T, 3, 1>(x, y, z)) {}

  void AsMatrix(Eigen::Matrix<T, 4, 4>& out) const override {
    out(0, 3) += translation_(0);
    out(1, 3) += translation_(1);
    out(2, 3) += translation_(2);
  }

  Eigen::Matrix<T, 3, 1> translation_;
};

}

#endif //RAYTRACER_TRANSLATION_H
