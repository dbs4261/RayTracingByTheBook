cmake_minimum_required(VERSION 3.10)
project(RayTracer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(libraries)

find_package(GFLAGS REQUIRED)
if(GFLAGS_LIBRARIES)
  message("-- Found GFlags")
else()
  message("-- Did not find GFlags")
endif()

find_package(Glog REQUIRED)
if(GLOG_LIBRARIES)
else()
  message("-- Did not find GLog")
endif()

option(BUILD_SHARED_LIBS OFF)

add_executable(LaunchGui applications/launch_gui.cc)
target_link_libraries(LaunchGui
  PRIVATE
    imgui
    ${GFLAGS_LIBRARIES}
    ${GLOG_LIBRARIES}
)