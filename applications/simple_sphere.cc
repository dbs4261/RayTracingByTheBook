#include <string>

#include <QApplication>

#include "raytracer/gui/raytracer_application.h"
#include "raytracer/scene_objects/scene_graph.h"
#include "raytracer/scene_objects/cameras/orthographic_camera.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  raytracer::SceneGraph<double> scene;
  scene.AddCamera<raytracer::OrthographicCamera<double>>(std::string("Default Camera"), 480, 640);
  raytracer::RaytracerApplication window(scene);
  window.show();
  return app.exec();
}