#ifndef RAYTRACER_DEFAULT_SHADER_H
#define RAYTRACER_DEFAULT_SHADER_H

#include "flat_shader.h"

namespace raytracer {

class DefaultShader {
 public:
  static AbstractShader::SPtr Get() {
    static AbstractShader::SPtr instance = std::make_shared<FlatShader>();
    return instance;
  }

  DefaultShader(const DefaultShader&) = delete;
  void operator=(const DefaultShader&) = delete;

 private:
  DefaultShader() {}
};

}

#endif //RAYTRACER_DEFAULT_SHADER_H
