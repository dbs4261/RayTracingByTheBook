//
// Created by daniel on 9/9/17.
//

#ifndef RAYTRACER_TRANSLATION_H
#define RAYTRACER_TRANSLATION_H

#include <Eigen/Core>
#include "transform.h"

namespace raytracer {

class Translation : public Transform {
 public:
  Translation() : tform(Eigen::Vector3d()) {}
  Translation(const Eigen::Vector3d vect) : tform(vect) {}
  Translation(const double x, const double y, const double z) {tform = Eigen::Vector3d(x, y, z);}

  Eigen::Vector3d tform;

  void LocalTransformVect(Eigen::Vector3d& vect) {
    vect(0) += tform(0);
    vect(1) += tform(1);
    vect(2) += tform(2);
  }
  void LocalTransformMat(Eigen::Matrix4d& mat) {
    mat(0, 3) += tform(0);
    mat(1, 3) += tform(1);
    mat(2, 3) += tform(2);
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

  void GloalRotationVect(Eigen::Vector3d& vect) {
    if (prev) {
      prev->GlobalRotationVect(vect);
    }
  }

 protected:
  Eigen::Matrix4d AsMatrix() {
    Eigen::Matrix4d out = Eigen::Matrix4d::Identity();
    out(0, 3) = tform(0);
    out(1, 3) = tform(1);
    out(2, 3) = tform(2);
  }
};

}

#endif //RAYTRACER_TRANSLATION_H
