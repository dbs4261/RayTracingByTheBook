//
// Created by daniel on 9/9/17.
//

#ifndef RAYTRACER_ROTATE_H
#define RAYTRACER_ROTATE_H

#include <Eigen/Core>
#include "src/raytracer/math/utils.h"
#include "transform.h"

namespace raytracer {

class Rotation : public Transform {
 public:
  Rotation() : axis(Vector3d()), angle(0.0) {}
  Rotation(const Vector3d axis, const double angle) : axis(axis), angle(angle) {}
  Rotation(const double x, const double y, const double z, const double theta) {
    axis = Eigen::Vector3d(x, y, z);
    angle = theta;
  }

  const double GetAngle() {
    return angle;
  }
  void SetAngle(double theta) {
    angle = theta;
    cached = false;
  }

  const Eigen::Vector3d GetAxis() {
    return axis;
  }
  void SetAxis(Eigen::Vector3d axis) {
    this->axis = axis;
    cached = false;
  }

  void LocalTransformVect(Eigen::Vector3d& vect) {
    vect *= cos(angle);
    vect += axis.cross(vect) * sin(angle);
    vect += axis * (axis.dot(vect)) * (1 - cos(angle));
  }
  void LocalTransformMat(Eigen::Matrix4d& mat) {
    mat = AsMatrix() * mat;
  }

  void GlobalTransformVect(Eigen::Vector3d& vect) {
    if (prev) {
      prev->GlobalTransformVect(vect);
    }
    LocalTransformMat(vect);
  }
  void GlobalTransformMat(Eigen::Matrix4d& mat) {
    if (prev) {
      prev->GlobalTransformMat(mat);
    }
    LocalTransformMat(mat);
  }

  void GlobalRotationVect(Eigen::Vector3d& vect) {
    if (prev) {
      prev->GlobalRotationVect(vect);
    }
    LocalTransformMat(vect);
  }

 protected:
  // ASSUMES THE AXIS IS NORMALIZED!!!
  Eigen::Vector3d axis;
  double angle;
  bool cached = false;
  Eigen::Matrix4d local_mat_cache;

  Eigen::Matrix4d AsMatrix() {
    if (!cached) {
      local_mat_cache = Eigen::Matrix4d::Identity();
      local_mat_cache += sin(angle) * SkewSymmetric(axis);
      local_mat_cache += (1.0 - cos(angle)) * SkewSymmetric(axis) * SkewSymmetric(axis);
      cached = true;
    }
    return local_mat_cache;
  }
};

}

#endif //RAYTRACER_ROTATE_H
