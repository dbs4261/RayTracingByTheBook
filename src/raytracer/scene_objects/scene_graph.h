#ifndef RAYTRACER_SCENE_GRAPH_H
#define RAYTRACER_SCENE_GRAPH_H

#include <memory>
#include <vector>

#include "raytracer/tracers/abstract_tracer.h"

#include "cameras/abstract_camera.h"
#include "geometry/abstract_geometry.h"

namespace raytracer {

template <typename T>
class SceneGraph {
 public:
  std::vector<std::shared_ptr<AbstractGeometry<T>>> objects;
  std::vector<std::pair<std::string, std::shared_ptr<AbstractCamera<T>>>> cameras;
  AbstractTracer::UPtr tracer;

  template <typename G, typename ... Args>
  void AddGeometry(Args&& ... args) {
    static_assert(std::is_base_of_v<AbstractGeometry<T>, G>, "Cannot add this type of object. It is not Geometry.");
    this->objects.push_back(std::make_unique<G>(std::forward<Args>(args)...));
  }

  template <typename C, typename ... Args>
  void AddCamera(std::string description, Args&& ... args) {
    static_assert(std::is_base_of_v<AbstractCamera<T>, C>, "Cannot add this type of object. It is not a Camera.");
    this->cameras.emplace_back(std::move(description), std::make_shared<C>(std::forward<Args>(args)...));
  }

  const auto& PeekCamera(size_t idx) const {
    return this->cameras.at(idx);
  }

  const auto CameraCBegin() const {
    return this->cameras.begin();
  }

  const auto CameraCEnd() const {
    return this->cameras.end();
  }

  size_t NumCameras() const {
    return this->cameras.size();
  }

//  void RenderCamera(size_t idx, QImage& img) const;
};

}

#endif //RAYTRACER_SCENE_GRAPH_H
