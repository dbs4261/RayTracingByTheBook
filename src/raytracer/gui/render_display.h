#ifndef RAYTRACER_RENDER_DISPLAY_H
#define RAYTRACER_RENDER_DISPLAY_H

#include <QWidget>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>

namespace raytracer {

class RenderDisplay : public QWidget {
 Q_OBJECT

 public:
  RenderDisplay(QWidget* parent = 0);

  bool openImage(const QString& filename);
  bool saveImage(const QString& fileName, const char* fileFormat);
  bool isModified() const { return modified; }

 public slots:
  void clearRender();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  void resizeImage(QImage* image, const QSize& newSize);

  bool modified; // If a render has been run since the last save.
  bool rendering; // If a render is running.

  QScrollArea* scrollArea; // Scroll for images lager than the window.
  QLabel* imageLabel; // Container for the image to allow zooming.
  QPoint mousePoint; // Mouse location to get the value from.
  QColor mouseColor; // Mouse over to look at value.
};

}

#endif //RAYTRACER_RENDER_DISPLAY_H
