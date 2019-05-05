#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "raytracer/gui/drawable_image.h"
#include "raytracer/image/tone_generator.h"

DEFINE_string(temp, "", "Help");

int main(int argc, char** argv) {
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);

  ImGui::CreateContext();
  sf::RenderWindow window(sf::VideoMode(640, 480), "Dan's Renderer");
  ImGui::SFML::Init(window);

  raytracer::DrawableImage img(480, 270);
  std::fill(img.Get().data.begin(), img.Get().data.end(), 127);

  raytracer::ColorBars(img.Get());
  raytracer::AddBorder(img.Get(), raytracer::RGBA{127, 127, 127, 127}, 1);

  img.setScale(window.getSize().x / (float)img.Get().GetX(), window.getSize().y / (float)img.Get().GetY());

  auto start = std::chrono::high_resolution_clock::now();
  img.Update();
  std::cout << "Set up time: " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;

  window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    window.draw(img);

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  ImGui::DestroyContext();

  return EXIT_SUCCESS;
}
