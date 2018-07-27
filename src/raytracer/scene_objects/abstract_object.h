//
// Created by daniel on 9/10/17.
//

#ifndef RAYTRACER_ABSTRACTOBJECT_H
#define RAYTRACER_ABSTRACTOBJECT_H

#include <Eigen/Core>
#include <memory>
#include <unordered_set>

#include "raytracer/math/transformations/transform.h"

namespace raytracer {

class AbstractObject {
 public:
  AbstractObject() : center(Eigen::Vector3d::Zero()) {}
  AbstractObject(const Eigen::Vector3d& center_) : center(center_) {}

  void pushTransform(std::shared_ptr<Transform> next) {
    next->SetPrevious(this->tform);
    this->tform = next;
  }
  std::shared_ptr<Transform> popTransform() {
    std::shared_ptr<Transform> out = this->tform;
    this->tform = this->tform->GetPrevious();
  }
  std::shared_ptr<Transform> peekTransform() const {
    return this->tform;
  }

  Eigen::Vector3d getLocalCenter() const {
    return center;
  }
  Eigen::Vector3d getGlobalCenter() const {
    Eigen::Vector3d out = center;
    tform->GlobalTransformVect(out);
    return out;
  }

 protected:
  Eigen::Vector3d center;
  std::shared_ptr<Transform> tform;
};

}

#endif //RAYTRACER_ABSTRACTOBJECT_H
