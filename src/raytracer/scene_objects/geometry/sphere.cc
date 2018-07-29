////
//// Created by daniel on 9/6/17.
////
//
//#include <Eigen/Core>
//#include <limits>
//
//#include "sphere.h"
//
//namespace raytracer {
//
//Sphere::Sphere(const Vector3d& center_, const double& radius) :
//    AbstractGeometry(center_), radius(radius) {}
//Sphere::Sphere(const Vector3d& center_, const double& radius, const AbstractShader& shader) :
//    AbstractObject(center_), AbstractGeometry(shader), radius(radius) {}
//
//bool sphere::hit(const Ray &ray, ShadingData &dat) const {
//  Eigen::Vector3d g_center = center_;
//  translation_->GlobalTransformVect(g_center);
//  double a = ray.getDirection().dot(ray.getDirection());
//  double b = 2 * (ray.getOrigin() - g_center).dot(ray.getDirection());
//  double c = (ray.getOrigin() - g_center).dot(ray.getOrigin() - g_center) - radius * radius;
//  double disc = b * b - 4 * a * c;
//  if (disc < 0.0) {
//    return false;
//  } else {
//    double e = sqrt(disc);
//    double denom = 2.0 * a;
//
//    double t = (-b - e) / denom;
//    if (t <= std::numeric_limits<double>::epsilon()) {
//      return false;
//    } else {
//      t = (-b + e) / denom;
//      if (t <= std::numeric_limits<double>::epsilon()) {
//        return false;
//      }
//    }
//    Eigen::Vector3d pt = ray.getOrigin() + t * ray.getDirection();
//    Eigen::Vector3d normal = (pt - g_center);
//    normal.normalize();
//    dat.hit = t > 0.0;
//    dat.iter = 1;
//    dat.ray = &ray;
//    dat.depth = t;
//    dat.hit_point = pt;
//    dat.normal = normal;
//    dat.shader = &shader;
//    return true;
//  }
//}
//
//}
