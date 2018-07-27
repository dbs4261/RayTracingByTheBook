//
// Created by daniel on 9/6/17.
//

#ifndef RAYTRACER_ABSTRACT_GEOMETRY_H
#define RAYTRACER_ABSTRACT_GEOMETRY_H

#include "raytracer/math/ray.h"
#include "raytracer/shaders/flat_shader.h"

#include "raytracer/scene_objects/void_object.h"
#include "raytracer/shaders/abstract_shader.h"
#include "raytracer/shaders/shading_data.h"

namespace raytracer {

class AbstractGeometry : public AbstractObject {
// public:
//  AbstractGeometry() : shader(FlatShader()) {}
//  AbstractGeometry(const AbstractShader& shader) : shader(shader) {}
//  AbstractShader shader;
//  virtual bool hit(const Ray &ray, ShadingData& dat) const = 0;
};

}

#endif //RAYTRACER_ABSTRACT_GEOMETRY_H
