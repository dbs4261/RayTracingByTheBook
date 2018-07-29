//
// Created by daniel on 9/6/17.
//

#include <Eigen/Core>

#include "infinite_plane.h"

namespace raytracer {

//InfinitePlane::InfinitePlane(const AbstractShader& shader, const Vector3d &point, const Vector3d &normal) :
//    AbstractGeometry(shader), center_(point), normal(normal) {}
//
//bool InfinitePlane::hit(const Ray &ray, ShadingData &dat) const {
//  Vector3d g_center = center_;
//  Vector3d g_normal = normal;
//  translation_->GlobalTransformVect(g_center);
//  translation_->GlobalRotationVect(g_normal);
//  double denom = g_normal.dot(ray.getDirection());
//  if (!two_sided && denom <= 0.0) {
//    dat.hit = false;
//    return false;
//  } else {
//    double t = (g_center - ray.getOrigin()).dot(g_normal) / denom;
//    Vector3d pt = ray.getOrigin() + t * ray.getDirection();
//    dat.hit = t > 0.0;
//    dat.iter = 1;
//    dat.ray = &ray;
//    dat.depth = t;
//    dat.hit_point = pt;
//    dat.normal = g_normal;
//    dat.shader = &shader;
//    return t > 0.0;
//  }
//}



}