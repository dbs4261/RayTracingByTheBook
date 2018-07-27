//
// Created by daniel on 9/6/17.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Eigen/Core>

namespace raytracer {

class Ray {
 public:
  const Eigen::Vector3d& getOrigin() const {
    return origin;
  }

  void setOrigin(const Eigen::Vector3d& origin) {
    this->origin = origin;
  }

  const Eigen::Vector3d& getDirection() const {
    return direction;
  }

  void setDirection(const Eigen::Vector3d& direction) {
    this->direction = direction;
  }

 protected:
  Eigen::Vector3d origin;
  Eigen::Vector3d direction;
};

}

#endif //RAYTRACER_RAY_H
