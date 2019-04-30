#ifndef RAYTRACER_ABSTRACT_TRACER_H
#define RAYTRACER_ABSTRACT_TRACER_H

#include <memory>

namespace raytracer {

class AbstractTracer {
 public:
  using UPtr = std::unique_ptr<AbstractTracer>;
};

}

#endif //RAYTRACER_ABSTRACT_TRACER_H