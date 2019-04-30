#include <QApplication>

#include "raytracer/gui/raytracer_application.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  raytracer::RaytracerApplication window;
  window.show();
  return app.exec();
}