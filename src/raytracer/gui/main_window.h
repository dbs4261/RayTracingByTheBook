#ifndef RAYTRACER_MAIN_WINDOW_H
#define RAYTRACER_MAIN_WINDOW_H

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace raytracer {

class MainWindow {
 public:
  MainWindow();

  void Loop() const;
  void Update() const;
  void Draw() const;

  ~MainWindow();
};

}

#endif //RAYTRACER_MAIN_WINDOW_H
