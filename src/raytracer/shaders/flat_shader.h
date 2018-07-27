//
// Created by daniel on 9/10/17.
//

#ifndef RAYTRACER_FLATSHADER_H
#define RAYTRACER_FLATSHADER_H

#include <Eigen/Core>
#include <random>

#include "abstract_shader.h"

namespace raytracer {

class FlatShader : public AbstractShader {
 public:
  FlatShader() {
    color << ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX));
  }
  FlatShader(const Eigen::Vector3d& rgb) : color(rgb) {}
  FlatShader(const float r, const float g, const float b) : color(Eigen::Vector3d(r, g, b)) {}

  const Eigen::Vector3d& getColor() const {
    return color;
  }
  void setColor(const Eigen::Vector3d& color) {
    this->color = color;
  }

 protected:
  Eigen::Vector3d color;

};

}

#endif //RAYTRACER_FLATSHADER_H
