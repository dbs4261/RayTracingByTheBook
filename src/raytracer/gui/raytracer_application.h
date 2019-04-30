#ifndef RAYTRACER_APPLICATION_H
#define RAYTRACER_APPLICATION_H

#include <memory>

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>

#include "raytracer/scene_objects/scene_graph.h"
//#include "raytracer/scene_objects/cameras/abstract_camera.h"

namespace raytracer {

class RaytracerApplication : public QMainWindow {
 Q_OBJECT

 public:
  RaytracerApplication(const SceneGraph<double>& scene_);
  bool loadFile(const QString& fname);

 private slots:
  void open();
  void saveAs();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void about();
  void renderCamera(QAction* action);

 private:
  void createActions();
  void updateActions();
  bool saveFile(const QString& fileName);
  void setImage(const QImage& newImage);
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);

  const SceneGraph<double>& scene;
//  QImage image;
  QPixmap pixmap;
  QPainter painter;
  QLabel* imageLabel;
  QScrollArea* scrollArea;
  double scaleFactor = 1;

//  QAction* renderAct;
  QAction* openAct;
  QAction* saveAsAct;
  QAction* zoomInAct;
  QAction* zoomOutAct;
  QAction* normalSizeAct;
  QAction* fitToWindowAct;
};

}

#endif //RAYTRACER_MAINAPPLICATION_H
