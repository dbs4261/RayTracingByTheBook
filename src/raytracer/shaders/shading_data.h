//
// Created by daniel on 9/10/17.
//

#ifndef RAYTRACER_SHADINGDATA_H
#define RAYTRACER_SHADINGDATA_H

#include <Eigen/Core>

#include "abstract_shader.h"
#include "raytracer/math/ray.h"

namespace raytracer {

class ShadingData {
 public:
  bool hit;
  int iter;
  const Ray* ray;
  double depth;
  Eigen::Vector3d hit_point;
  Eigen::Vector3d normal;
  Eigen::Vector2d texture;
  AbstractShader* shader;
};

}

#endif //RAYTRACER_SHADINGDATA_H
