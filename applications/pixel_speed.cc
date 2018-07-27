#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QDebug>

const int loop = 25;
const int windowWidth = 400;
const int windowHeight = 300;

class PainterWindow : public QWidget {
  void paintEvent(QPaintEvent*) {
    QTime time;
    time.start();
    for (int i = 0; i < ::loop; ++i) {
      QPainter painter(this);
      for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
          const QColor color(static_cast<QRgb>(i+x+y));
          painter.setPen(color);
          painter.drawPoint(x, y);
        }
      }
    }
    qDebug() << "drawPoint time:" << time.elapsed();
    close();
  }
};

class ImageWindow : public QWidget {
  void paintEvent(QPaintEvent*) {
    QRgb* pixels = new QRgb[width()*height()];
    QTime time;
    time.start();
    for (int i = 0; i < ::loop; ++i) {
      QPainter painter(this);
      QImage image((uchar*)pixels, width(), height(), QImage::Format_ARGB32);
      for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
          pixels[x + y * height()] = static_cast<QRgb>(rand());
        }
      }
      painter.drawImage(0, 0, image);
    }
    qDebug() << "drawImage time:" << time.elapsed();
    close();
    delete[] pixels;
  }
};

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  PainterWindow w;
  w.resize(::windowWidth, ::windowHeight);
  w.show();

  a.exec();

  ImageWindow imageWindow;
  imageWindow.resize(::windowWidth, ::windowHeight);
  imageWindow.show();

  a.exec();
}