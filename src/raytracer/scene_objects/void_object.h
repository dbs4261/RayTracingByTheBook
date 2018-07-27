//
// Created by daniel on 9/9/17.
//

#ifndef RAYTRACER_VOIDOBJECT_H
#define RAYTRACER_VOIDOBJECT_H

#include <Eigen/Core>

#include "abstract_object.h"

namespace raytracer {

class VoidObject : public AbstractObject {
 public:
  VoidObject() : AbstractObject(Eigen::Vector3d(0.0, 0.0, 0.0)) {}
  VoidObject(const Eigen::Vector3d& center) : AbstractObject(center) {}
};

}

#endif //RAYTRACER_VOIDOBJECT_H
