#ifndef RAYTRACER_INFINITEPLANE_H
#define RAYTRACER_INFINITEPLANE_H

#include <Eigen/Core>

#include "abstract_geometry.h"

namespace raytracer {

/**
 * @brief An infinite plane who's normal faces along the positive X axis.
 * @tparam T The data type used for spatial calculations.
 */
template <typename T>
class InfinitePlane : public AbstractGeometry<T> {
 public:
  InfinitePlane()
      : AbstractGeometry<T>(), two_sided_(true) {}
  InfinitePlane(bool two_sided)
      : AbstractGeometry<T>(), two_sided_(two_sided) {}
  InfinitePlane(AbstractShader::SPtr shader, bool two_sided)
      : AbstractGeometry<T>(shader), two_sided_(two_sided) {}
  InfinitePlane(typename Transform<T>::SPtr tform, bool two_sided)
      : AbstractGeometry<T>(std::move(tform)), two_sided_(two_sided) {}
  InfinitePlane(typename Transform<T>::SPtr tform, AbstractShader::SPtr shader, bool two_sided)
      : AbstractGeometry<T>(std::move(tform), std::move(shader)), two_sided_(two_sided) {}

  bool hit(const Ray<T>& ray, ShadingData<T>& dat) const {
    Point<T> g_center = this->tform_->TransformPoint();
    Direction<T> g_normal = this->tform_->TransformDirection(Direction<T>());
    T denom = g_normal.Project(ray.direction_);
    if (!this->two_sided_ && denom <= 0.0) {
      dat.hit_ = false;
      return false;
    } else {
      T t = Direction<T>(g_center, ray.origin_).Project(g_normal) / denom;
      Point<T> pt = ray.Project(t);
      dat.hit_ = t > 0.0;
      dat.ray_ = ray;
      dat.depth_ = t;
      dat.hit_point_ = pt;
      dat.normal_ = g_normal;
      dat.shader_ = this->shader_;
      return t > 0.0;
    }
  }

  bool two_sided_;
};

}

#endif //RAYTRACER_INFINITEPLANE_H
