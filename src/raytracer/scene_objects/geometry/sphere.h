#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <Eigen/Core>

#include "abstract_geometry.h"

namespace raytracer {

using Eigen::Vector3d;

template <typename T>
class Sphere : public AbstractGeometry<T> {
 public:
  Sphere() : AbstractGeometry<T>(), radius_(1.0) {}
  Sphere(double radius)
      : AbstractGeometry<T>(), radius_(radius) {}
  Sphere(AbstractShader::SPtr shader, double radius)
      : AbstractGeometry<T>(shader), radius_(radius) {}
  Sphere(typename Transform<T>::SPtr tform, double radius)
      : AbstractGeometry<T>(std::move(tform)), radius_(radius) {}
  Sphere(AbstractShader::SPtr shader, typename Transform<T>::SPtr tform, double radius)
      : AbstractGeometry<T>(std::move(tform), std::move(shader)), radius_(radius) {}

  bool hit(const Ray<T>& ray, ShadingData<T>& dat) const {
    Point<T> g_center = this->tform_->TransformPoint();
    Direction<T> center_to_ray (g_center, ray.origin_);
    T a = ray.direction_.Project(ray.direction_);
    T b = 2 * center_to_ray.Project(ray.direction_);
    T c = center_to_ray.Project(center_to_ray) - (radius_ * radius_);
    T disc = (b * b) - (4 * a * c);
    if (disc < std::numeric_limits<T>::epsilon()) {
      // Negative discriminant
      dat.hit_ = false;
      return false;
    } else {
      T e = sqrt(disc);
      T denom = 2.0 * a;
      T t = (-b - e) / denom;
      if (t <= std::numeric_limits<T>::epsilon()) {
        dat.hit_ = false;
        return false;
      } else {
        t = (-b + e) / denom;
        if (t <= std::numeric_limits<T>::epsilon()) {
          dat.hit_ = false;
          return false;
        }
      }
      dat.hit_ = true;
      dat.hit_point_ = Point<T>(ray.origin_ + t * ray.direction_);
      dat.ray_ = &ray;
      dat.depth_ = t;
      dat.normal_ = Direction<T>(g_center, dat.hit_point_);
      dat.shader_ = this->shader_;
    }
  }

 protected:
  double radius_;
};

}

#endif //RAYTRACER_SPHERE_H
