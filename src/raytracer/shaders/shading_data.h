//
// Created by daniel on 9/10/17.
//

#ifndef RAYTRACER_SHADINGDATA_H
#define RAYTRACER_SHADINGDATA_H

#include <Eigen/Core>

#include "abstract_shader.h"
#include "raytracer/math/concepts/ray.h"

namespace raytracer {

template <typename T>
struct ShadingData {
 public:
  bool hit_;
  Ray<T>& ray_;
  T depth_;
  Point<T> hit_point_;
  Direction<T> normal_;
  AbstractShader::SPtr shader_;
};

}

#endif //RAYTRACER_SHADINGDATA_H
