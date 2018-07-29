#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H


#include <Eigen/Core>
#include <memory>

namespace raytracer {

template <typename T>
class Transform {
 public:
  using SPtr = std::shared_ptr<Transform<T>>;

  Transform() : prev_(nullptr) {}
  explicit Transform(Transform::SPtr prev) : prev_(std::move(prev)) {}

  // Makes a transformation matrix.
  virtual void AsMatrix(Eigen::Matrix<T, 4, 4>& mat) const = 0;

  virtual void LocalTransformMat(Eigen::Matrix<T, 4, 4>& mat) const {
    AsMatrix(mat);
  }

  virtual void GlobalTransformMat(Eigen::Matrix<T, 4, 4>& mat) const {
    if (prev_.get() != nullptr) {
      prev_->GlobalTransformMat(mat);
    }
    LocalTransformMat(mat);
  }

  Eigen::Matrix<T, 4, 4> LocalTransformMat() const {
    Eigen::Matrix<T, 4, 4> out = Eigen::Matrix<T, 4, 4>::Identity();
    LocalTransformMat(out);
    return out;
  }

  Eigen::Matrix<T, 4, 4> GlobalTransformMat() const {
    Eigen::Matrix<T, 4, 4> out = Eigen::Matrix<T, 4, 4>::Identity();
    GlobalTransformMat(out);
    return out;
  }

  Point<T> TransformPoint(const Point<T>& pt) const {
    return Point<T>(GlobalTransformMat().template block<3, 4>(0, 0) * pt.point_);
  }

  Direction<T> TransformDirection(const Direction<T>& dir) const {
    return Direction<T>(GlobalTransformMat().template block<3, 4>(0, 0) * dir.direction_);
  }

  Transform::SPtr prev_;
};

}

#endif //RAYTRACER_TRANSFORM_H
