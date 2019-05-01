#include "main_window.h"

namespace raytracer {

MainWindow::MainWindow() {
  ImGui::CreateContext();
}

void MainWindow::Loop() const {

}

void MainWindow::Update() const {

}

void MainWindow::Draw() const {

}

MainWindow::~MainWindow() {
  ImGui::SFML::Shutdown();
  ImGui::DestroyContext();
}

}
