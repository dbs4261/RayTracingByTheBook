#ifndef RAYTRACER_MAINWINDOW_H
#define RAYTRACER_MAINWINDOW_H

#include <QList>
#include <QMainWindow>

#include "scribble_area.h"

class MainWindow : public QMainWindow
{
 Q_OBJECT

 public:
  MainWindow() : QMainWindow() {
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Scribble"));
    resize(500, 500);
  }
  virtual ~MainWindow() {};

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void open();
  void save();
  void penColor();
  void penWidth();
  void about();

 private:
  void createActions();
  void createMenus();
  bool maybeSave();
  bool saveFile(const QByteArray &fileFormat);

  ScribbleArea *scribbleArea;

  QMenu *saveAsMenu;
  QMenu *fileMenu;
  QMenu *optionMenu;
  QMenu *helpMenu;

  QAction *openAct;
  QList<QAction *> saveAsActs;
  QAction *exitAct;
  QAction *penColorAct;
  QAction *penWidthAct;
  QAction *printAct;
  QAction *clearScreenAct;
  QAction *aboutAct;
  QAction *aboutQtAct;
};


#endif //RAYTRACER_MAINWINDOW_H
