#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(temp, "", "Help");

int main(int argc, char *argv[]) {
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);

  LOG(INFO) << FLAGS_temp;
  return EXIT_SUCCESS;
}