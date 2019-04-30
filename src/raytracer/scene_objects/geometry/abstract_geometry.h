#ifndef RAYTRACER_ABSTRACT_GEOMETRY_H
#define RAYTRACER_ABSTRACT_GEOMETRY_H

#include "raytracer/math/concepts/ray.h"
#include "raytracer/scene_objects/void_object.h"

#include "raytracer/shaders/abstract_shader.h"
#include "raytracer/shaders/default_shader.h"
#include "raytracer/shaders/shading_data.h"

namespace raytracer {

template <typename T>
class AbstractGeometry : public VoidObject<T> {
 public:
  AbstractGeometry()
      : VoidObject<T>(), shader_(DefaultShader::Get()) {}
  explicit AbstractGeometry(typename Transform<T>::SPtr tform)
      : VoidObject<T>(std::move(tform)), shader_(DefaultShader::Get()) {}
  explicit AbstractGeometry(AbstractShader::SPtr shader)
      : VoidObject<T>(), shader_(std::move(shader)) {}
  AbstractGeometry(typename Transform<T>::SPtr tform, AbstractShader::SPtr shader)
      : VoidObject<T>(std::move(tform)), shader_(std::move(shader)) {}

  AbstractShader::SPtr shader_;

  virtual bool hit(const Ray<T>& ray, ShadingData<T>& dat) const = 0;
};

}

#endif //RAYTRACER_ABSTRACT_GEOMETRY_H
