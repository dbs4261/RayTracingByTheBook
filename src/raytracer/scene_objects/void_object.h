#ifndef RAYTRACER_VOID_OBJECT_H
#define RAYTRACER_VOID_OBJECT_H

#include <Eigen/Core>
#include <memory>
#include <unordered_set>

#include "raytracer/math/transformations/transform.h"
#include "raytracer/math/transformations/null_transform.h"

#include "raytracer/scene_objects/void_object.h"

namespace raytracer {

template <typename T>
class VoidObject {
 public:
  VoidObject() : tform_(MakeNullTransform<T>()) {}
  explicit VoidObject(typename Transform<T>::SPtr tform) : tform_(std::move(tform)) {}

  void PushTransform(typename Transform<T>::SPtr next) {
    next->prev_ = this->tform_;
    this->tform_ = next;
  }

  typename Transform<T>::SPtr PopTransform() {
    typename Transform<T>::SPtr out = this->tform_;
    this->tform_ = out->prev_;
    return out;
  }

  typename Transform<T>::SPtr PeekTransform() {
    return this->tform_;
  }

  Point<T> GetGlobalCenter() const {
    return this->tform_->TransformPoint();
  }

  typename Transform<T>::SPtr tform_;
};

}

#endif //RAYTRACER_VOID_OBJECT_H
