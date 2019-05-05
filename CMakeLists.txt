cmake_minimum_required(VERSION 3.10)
project(RayTracer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(libraries)

find_package(GFLAGS REQUIRED)
if(GFLAGS_FOUND)
  message("-- Found GFlags")
else()
  message("-- Did not find GFlags")
endif()

find_package(Glog REQUIRED)
if(GLOG_FOUND)
else()
  message("-- Did not find GLog")
endif()

find_package(Boost REQUIRED)
if(Boost_FOUND)
  message("-- Found Boost in ${Boost_INCLUDE_DIRS}")
else()
  message("-- Did not find Boost")
endif()

option(BUILD_SHARED_LIBS OFF)

add_subdirectory(src/raytracer)
add_subdirectory(applications)