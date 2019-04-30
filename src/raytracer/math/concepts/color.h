#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <Eigen/Core>

namespace raytracer {

class Color {
 public:
  Color() : val_(1, 1, 1) {}
  Color(const Eigen::Vector3f& val) : val_(val) {}
  Color(float b, float g, float r) : val_(b, g, r) {}

  Eigen::Vector3f val_;
};

}

#endif //RAYTRACER_COLOR_H
