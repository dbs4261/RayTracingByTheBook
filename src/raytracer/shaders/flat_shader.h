#ifndef RAYTRACER_FLATSHADER_H
#define RAYTRACER_FLATSHADER_H

#include <Eigen/Core>
#include <random>

#include "raytracer/math/concepts/color.h"

#include "abstract_shader.h"

namespace raytracer {

class FlatShader : public AbstractShader {
 public:
  FlatShader() : color_(0.5, 0.5, 0.5) {}
  FlatShader(const Eigen::Vector3f& bgr) : color_(bgr) {}
  FlatShader(const float b, const float g, const float r) : color_(b, g, r) {}

  Color color_;
};

}

#endif //RAYTRACER_FLATSHADER_H
