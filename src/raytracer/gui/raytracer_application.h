#ifndef RAYTRACER_APPLICATION_H
#define RAYTRACER_APPLICATION_H

#include <memory>

#include <QtWidgets/QMainWindow>

#include "render_display.h"

namespace raytracer {

class RaytracerApplication : public QMainWindow {
  Q_OBJECT

 public:
//  RaytracerApplication();
//  virtual ~RaytracerApplication() {};

 protected:
//  void closeEvent(QCloseEvent *event) override;

 private slots:
//  void open();
//  void save();
//  void about();

 private:
//  void createActions();
//  void createMenus();
//  bool maybeSave();
//  bool saveFile(const QByteArray &fileFormat);

  QTabWidget* tabWidget;
  QLabel* statusLabel;

  QMenu* saveAsMenu;
  QMenu* fileMenu;
  QMenu* optionMenu;
  QMenu* helpMenu;

  QAction* openAct;
  QList<QAction*> saveAsActs;
  QAction* exitAct;
  QAction* penColorAct;
  QAction* penWidthAct;
  QAction* printAct;
  QAction* clearScreenAct;
  QAction* aboutAct;
  QAction* aboutQtAct;
};

}

#endif //RAYTRACER_MAINAPPLICATION_H
