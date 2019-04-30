#ifndef RAYTRACER_ABSTRACTSHADER_H
#define RAYTRACER_ABSTRACTSHADER_H

#include <memory>

namespace raytracer {

class AbstractShader {
 public:
  using SPtr = std::shared_ptr<AbstractShader>;
};

}

#endif //RAYTRACER_ABSTRACTSHADER_H
