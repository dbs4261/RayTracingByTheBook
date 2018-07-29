//
// Created by daniel on 9/10/17.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <Eigen/Core>

namespace raytracer {

// Overwrites a matrix with a skew symmetric matrix
template <int D, typename T>
void SkewSymmetric(const Eigen::Matrix<T, D, 1>& vect, Eigen::Matrix<T, D + 1, D + 1>& mat) {
  mat(0,0) = 0.0;
  mat(0,1) = -vect(2);
  mat(0,2) = vect(1);
  mat(0,3) = 0.0;
  mat(1,0) = vect(2);
  mat(1,1) = 0.0;
  mat(1,2) = -vect(0);
  mat(1,3) = 0.0;
  mat(2,0) = -vect(1);
  mat(2,1) = vect(0);
  mat(2,2) = 0.0;
  mat(2,3) = 0.0;
  mat(3,0) = 0.0;
  mat(3,1) = 0.0;
  mat(3,2) = 0.0;
  mat(3,3) = 1.0;
}

Eigen::Matrix4d SkewSymmetric(const Eigen::Vector3d& vect) {
  Eigen::Matrix4d out;
  SkewSymmetric(vect, out);
  return out;
}

double Distance(const Eigen::Vector3d& pt1, const Eigen::Vector3d& pt2) {
  double distance = (pt2(0) - pt1(0)) * (pt2(0) - pt1(0));
  distance += (pt2(1) - pt1(1)) * (pt2(1) - pt1(1));
  distance += (pt2(2) - pt1(2)) * (pt2(2) - pt1(2));
  return sqrt(distance);
}

}

#endif //RAYTRACER_UTILS_H
