#include "render_display.h"

namespace raytracer {

RenderDisplay::RenderDisplay(QWidget* parent) : QWidget(parent) {

}

bool RenderDisplay::openImage(const QString& filename) {
  return false;
}

bool RenderDisplay::saveImage(const QString& fileName, const char* fileFormat) {
  return false;
}

void RenderDisplay::clearRender() {

}

void RenderDisplay::paintEvent(QPaintEvent* event) {
  QWidget::paintEvent(event);
}

void RenderDisplay::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
}

void RenderDisplay::resizeImage(QImage* image, const QSize& newSize) {

}

}