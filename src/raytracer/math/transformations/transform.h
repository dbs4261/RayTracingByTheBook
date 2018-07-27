//
// Created by daniel on 9/9/17.
//

#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H


#include <Eigen/Core>
#include <memory>

namespace raytracer {

class Transform {
 public:
  std::shared_ptr<Transform> GetPrevious() {return prev;}
  void SetPrevious(std::shared_ptr<Transform> tform) {prev = tform;}

  virtual void LocalTransformVect(Eigen::Vector3d& vect) = 0;
  virtual void LocalTransformMat(Eigen::Matrix4d& mat) = 0;

  virtual void GlobalTransformVect(Eigen::Vector3d& vect) = 0;
  virtual void GlobalTransformMat(Eigen::Matrix4d& mat) = 0;

  Eigen::Matrix4d LocalTransformMat() {
    return AsMatrix();
  }
  Eigen::Matrix4d GlobalTransformMat() {
    Eigen::Matrix4d out = Eigen::Matrix4d::Identity();
    GlobalTransformMat(out);
    return out;
  }

  virtual void GlobalRotationVect(Eigen::Vector3d& vect) = 0;

 protected:
  std::shared_ptr<Transform> prev = nullptr;
  // Creates the transformation matrix from scratch
  virtual Eigen::Matrix4d AsMatrix() = 0;
};

}

#endif //RAYTRACER_TRANSFORM_H
