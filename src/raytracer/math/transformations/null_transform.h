#ifndef RAYTRACER_NULL_TRANSFORM_H
#define RAYTRACER_NULL_TRANSFORM_H

#include "transform.h"

namespace raytracer {

template <typename T>
class NullTransform final : public Transform<T> {
 public:
  NullTransform() : Transform<T>() {}
  explicit NullTransform(typename Transform<T>::SPtr prev) : Transform<T>(prev) {}

  void AsMatrix(Eigen::Matrix<T, 4, 4>& mat) const override {}
};

template <typename T, typename ... Args>
typename Transform<T>::SPtr MakeNullTransform(Args&& ... args) {
  return std::make_shared<NullTransform<T>>(std::forward<Args>(args) ...);
};

}

#endif //RAYTRACER_NULL_TRANSFORM_H
