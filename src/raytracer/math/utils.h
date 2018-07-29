#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <Eigen/Core>

#include "raytracer/math/concepts/point.h"

namespace raytracer {

template <typename T>
T Distance(const Point<T>& pt1, const Point<T>& pt2) {
  return (pt1.point_ - pt2.point_).norm();
}

}

#endif //RAYTRACER_UTILS_H
