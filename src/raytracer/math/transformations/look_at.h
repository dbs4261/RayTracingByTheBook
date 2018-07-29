#ifndef RAYTRACER_LOOKAT_H
#define RAYTRACER_LOOKAT_H

#include <Eigen/Core>

#include "raytracer/scene_objects/void_object.h"
#include "raytracer/scene_objects/void_object.h"

#include "raytracer/math/concepts/point.h"
#include "raytracer/math/utils.h"
#include "transform.h"

namespace raytracer {

class LookAt : public Transform {
 public:
  LookAt(const Eigen::Vector3d& from, const Eigen::Vector3d& to) {}
  LookAt(const AbstractObject* from, const Eigen::Vector3d& to) {}
  LookAt(const Eigen::Vector3d& from, const AbstractObject* to) {}
  LookAt(const AbstractObject* from, const AbstractObject* to) {}

  double Distance() {
//    return Distance(to->getGlobalCenter(), from->getGlobalCenter());
    return 0.0;
  }

  void LocalTransformVect(Eigen::Vector3d& vect);
  void LocalTransformMat(Eigen::Matrix4d& mat);

  void GlobalTransformVect(Eigen::Vector3d& vect);
  void GlobalTransformMat(Eigen::Matrix4d& mat);

  void GlobalRotationVect(Eigen::Vector3d& vect);

 protected:
  AbstractObject* from;
  AbstractObject* to;

  Eigen::Matrix4d AsMatrix();
};

}

#endif //RAYTRACER_LOOKAT_H
