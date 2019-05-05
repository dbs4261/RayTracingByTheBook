#include <gflags/gflags.h>
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
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dan's Renderer");
  ImGui::SFML::Init(window);

  raytracer::DrawableImage img(480, 270);
  std::fill(img.Get().data.begin(), img.Get().data.end(), 0);

//  auto start = std::chrono::high_resolution_clock::now();
  img.setScale(window.getSize().x / (float)img.Get().GetSize().x,
               window.getSize().y / (float)img.Get().GetSize().y);

  raytracer::ColorBars<raytracer::ChannelType::RGBA>(img.Get().data.data(), 480, 270);
  img.Update();
//  std::cout << "Set up time: " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;

  window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());
//    ImGui::Image(texture, sf::Vector2f(window.getSize()));
//    ImGui::Image(texture, sf::Vector2f(480, 270));
    window.draw(img);

//    window.clear(sf::Color(0, 0, 0)); // fill background with color
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  ImGui::DestroyContext();

  return EXIT_SUCCESS;
}
