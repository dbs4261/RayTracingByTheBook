//
// Created by daniel on 9/6/17.
//

#ifndef RAYTRACER_INFINITEPLANE_H
#define RAYTRACER_INFINITEPLANE_H

#include <Eigen/Core>

#include "abstract_geometry.h"

namespace raytracer {

class InfinitePlane : public AbstractGeometry {
// public:
//  InfinitePlane() {};
//  InfinitePlane(const AbstractShader& shader, const Eigen::Vector3d& center, const Eigen::Vector3d& normal);
//
//  bool hit(const Ray& ray, ShadingData& dat) const;
//
// protected:
//  Eigen::Vector3d normal;
//  bool two_sided;
};

}

#endif //RAYTRACER_INFINITEPLANE_H
