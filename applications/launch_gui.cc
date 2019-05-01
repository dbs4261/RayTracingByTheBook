#include <gflags/gflags.h>
#include <glog/logging.h>

#include "raytracer/gui/main_window.h"

DEFINE_string(temp, "", "Help");

int main(int argc, char *argv[]) {
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);

  raytracer::MainWindow window;
  window.Loop();

  LOG(INFO) << FLAGS_temp;


  return EXIT_SUCCESS;
}