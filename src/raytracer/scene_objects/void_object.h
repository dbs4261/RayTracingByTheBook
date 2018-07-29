#ifndef RAYTRACER_ABSTRACTOBJECT_H
#define RAYTRACER_ABSTRACTOBJECT_H

#include <Eigen/Core>
#include <memory>
#include <unordered_set>

#include "raytracer/math/transformations/transform.h"

namespace raytracer {

template <typename T>
class AbstractObject {
 public:
  AbstractObject() : center_(), tform_() {}
  explicit AbstractObject(const Point<T>& center) : center_(center), tform_() {}
  explicit AbstractObject(Transform<T>::SPtr tform) : center_(), tform_(std::move(tform)) {}
  AbstractObject(const Point<T>& center, Transform<T>::SPtr tform) : center_(center), tform_(tform) {}

  void PushTransform(std::shared_ptr<Transform<T>> next) {
    next->prev_ = this->tform_;
    this->tform_ = next;
  }

  std::shared_ptr<Transform> PopTransform() {
    std::shared_ptr<Transform> out = this->tform_;
    this->tform_ = out->prev_;
    return out;
  }

  Point<T> GetGlobalCenter() const {
    return this->tform_->TransformPoint(this->center_);
  }

  Point<T> center_;
  Transform<T>::SPtr tform_;
};

}

#endif //RAYTRACER_ABSTRACTOBJECT_H
