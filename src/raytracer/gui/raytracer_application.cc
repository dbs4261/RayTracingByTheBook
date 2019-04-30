#include <glog/logging.h>
#include <iostream>

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QMenuBar>
#include <QMessageBox>
#include <QRgb>
#include <QScreen>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>

#include "raytracer_application.h"

namespace raytracer {

RaytracerApplication::RaytracerApplication(const SceneGraph<double>& scene_) : scene(scene_), imageLabel(new QLabel), scrollArea(new QScrollArea) {
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);
  imageLabel->setPixmap(this->pixmap);

  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  scrollArea->setVisible(false);
  setCentralWidget(scrollArea);

  createActions();

  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

bool RaytracerApplication::loadFile(const QString& fileName) {
  QImageReader reader(fileName);
  reader.setAutoTransform(true);
  const QImage newImage = reader.read();

  if (newImage.isNull()) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
    return false;
  }

  setImage(newImage);

  setWindowFilePath(fileName);

  const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
      .arg(QDir::toNativeSeparators(fileName)).arg(pixmap.width()).arg(pixmap.height()).arg(pixmap.depth());
  statusBar()->showMessage(message);
  return true;
}

void RaytracerApplication::setImage(const QImage& newImage) {
  this->pixmap = QPixmap::fromImage(newImage);
//  imageLabel->setPixmap(QPixmap::fromImage(newImage));
  scaleFactor = 1.0;

  scrollArea->setVisible(true);
  fitToWindowAct->setEnabled(true);
  updateActions();

  if (!fitToWindowAct->isChecked()) {
    imageLabel->adjustSize();
  }
}

bool RaytracerApplication::saveFile(const QString& fileName) {
  QFile file(fileName);
  file.open(QIODevice::WriteOnly);

  if (!pixmap.save(&file)) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot write %1").arg(QDir::toNativeSeparators(fileName)));
    return false;
  }
  const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
  statusBar()->showMessage(message);
  return true;
}

static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode) {
  static bool firstDialog = true;

  if (firstDialog) {
    firstDialog = false;
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
  }

  QStringList mimeTypeFilters;
  const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
                                            ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
      foreach (const QByteArray& mimeTypeName, supportedMimeTypes) { mimeTypeFilters.append(mimeTypeName); }
  mimeTypeFilters.sort();
  dialog.setMimeTypeFilters(mimeTypeFilters);
  dialog.selectMimeTypeFilter("image/jpeg");
  if (acceptMode == QFileDialog::AcceptSave) {
    dialog.setDefaultSuffix("jpg");
  }
}

void RaytracerApplication::open() {
  QFileDialog dialog(this, tr("Open File"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

  while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void RaytracerApplication::saveAs() {
  QFileDialog dialog(this, tr("Save File As"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

  while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void RaytracerApplication::zoomIn() {
  scaleImage(1.25);
}

void RaytracerApplication::zoomOut() {
  scaleImage(0.8);
}

void RaytracerApplication::normalSize() {
  QImage img;
  this->setImage(img);
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void RaytracerApplication::fitToWindow() {
  bool fitToWindow = fitToWindowAct->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);
  if (!fitToWindow) {
    normalSize();
  }
  updateActions();
}

void RaytracerApplication::about() {
  QMessageBox::about(this, tr("About Image Viewer"),
                     tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
                        "and QScrollArea to display an image. QLabel is typically used "
                        "for displaying a text, but it can also display an image. "
                        "QScrollArea provides a scrolling view around another widget. "
                        "If the child widget exceeds the size of the frame, QScrollArea "
                        "automatically provides scroll bars. </p><p>The example "
                        "demonstrates how QLabel's ability to scale its contents "
                        "(QLabel::scaledContents), and QScrollArea's ability to "
                        "automatically resize its contents "
                        "(QScrollArea::widgetResizable), can be used to implement "
                        "zooming and scaling features. </p><p>In addition the example "
                        "shows how to use QPainter to print an image.</p>"));
}

void RaytracerApplication::renderCamera(QAction* action) {
  int index = action->data().toInt();
  if (index < 0) {
    std::cerr << "Camera index invalid. There probably arent any cameras to render";
  } else if (index >= scene.NumCameras()) {
    std::cerr << "Camera index out of bounds";
  } else {
    std::cout << "Rendering camera " << index << std::endl;
    auto cam = scene.PeekCamera(index).second;
//    QImage::Format format = QImage::Format_RGBA8888;
    pixmap = QPixmap(cam->width_, cam->height_);
    pixmap.fill(Qt::black);
    scaleFactor = 1.0;
    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();
    if (!fitToWindowAct->isChecked()) {
      imageLabel->adjustSize();
    }

    painter.begin(&pixmap);
    for (size_t y = 0; y < cam->height_; y++) {
      for (size_t x = 0; x < cam->width_; x++) {
//        this->image.setPixel(x, y, qRgba(x % 255, y % 255, 0, 255));
//        img.setPixel(x, y, qRgba(x % 255, y % 255, 0, 255));
        painter.drawPoint(x, y) = qRgba(x % 255, y % 255, 0, 255);
      }
    }
    painter.end();
  }
}

void RaytracerApplication::createActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

  openAct = fileMenu->addAction(tr("&Open..."), this, &RaytracerApplication::open);
  openAct->setShortcut(tr("Ctrl+O"));

  saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &RaytracerApplication::saveAs);
  saveAsAct->setShortcut(tr("Ctrl+S"));
  saveAsAct->setEnabled(false);

  fileMenu->addSeparator();

  QAction* exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcut(tr("Ctrl+Q"));

  QMenu* viewMenu = menuBar()->addMenu(tr("&View"));

  zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &RaytracerApplication::zoomIn);
  zoomInAct->setShortcut(tr("Ctrl+="));
  zoomInAct->setEnabled(false);

  zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &RaytracerApplication::zoomOut);
  zoomOutAct->setShortcut(tr("Ctrl+-"));
  zoomOutAct->setEnabled(false);

  normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &RaytracerApplication::normalSize);
  normalSizeAct->setShortcut(tr("Ctrl+0"));
  normalSizeAct->setEnabled(false);

  viewMenu->addSeparator();

  fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &RaytracerApplication::fitToWindow);
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);
  fitToWindowAct->setShortcut(tr("Ctrl+F"));

  QMenu* renderMenu = menuBar()->addMenu(tr("&Render"));
  auto cameraGroup = new QActionGroup(renderMenu);
  if (scene.NumCameras() > 0) {
    int index = 0;
    std::for_each(scene.CameraCBegin(), scene.CameraCEnd(),
        [&cameraGroup, &renderMenu, &index](auto pair)->void{
      cameraGroup->addAction(renderMenu->addAction(tr(pair.first.c_str())))->setData(index++);
    });
  } else {
    cameraGroup->addAction(renderMenu->addAction(tr("No cameras found!")))->setData(-1);
  }
  cameraGroup->setExclusive(true);
  connect(cameraGroup, SIGNAL(triggered(QAction*)), SLOT(renderCamera(QAction*)));

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

  helpMenu->addAction(tr("&About"), this, &RaytracerApplication::about);
  helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void RaytracerApplication::updateActions() {
//  saveAsAct->setEnabled(!image.isNull());
  saveAsAct->setEnabled(true);
  zoomInAct->setEnabled(!fitToWindowAct->isChecked());
  zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
  normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void RaytracerApplication::scaleImage(double factor) {
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void RaytracerApplication::adjustScrollBar(QScrollBar* scrollBar, double factor) {
  scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep() / 2)));
}

}