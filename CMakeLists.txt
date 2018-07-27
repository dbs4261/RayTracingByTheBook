cmake_minimum_required(VERSION 3.7)
project(RayTracer)
include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data")

# GFlags
find_package(Gflags REQUIRED)
if (GFLAGS_FOUND)
  message("-- Found Google Flags: ${GFLAGS_INCLUDE_DIRS} in namespace: ${GFLAGS_NAMESPACE}")
  add_definitions(-DSELENE_GFLAGS_NAMESPACE=${GFLAGS_NAMESPACE})
else (GFLAGS_FOUND)
  message(FATAL_ERROR "Can't find Google FLAGS.")
endif (GFLAGS_FOUND)

# Google Logging
message("-- Check for Google Log")
find_package(Glog REQUIRED)
if (GLOG_FOUND)
  message("-- Found Google Logging: ${GLOG_INCLUDE_DIRS}")
else (GLOG_FOUND)
  message(FATAL_ERROR "Can't find Google Logging. Please set GLOG_INCLUDE_DIR & "
          "GLOG_LIBRARY")
endif (GLOG_FOUND)

# Google Testing
message("-- Check for Google Test")
find_package(GTest REQUIRED)
if (GTEST_FOUND)
  message("-- Found Google Logging: ${GTEST_INCLUDE_DIRS}")
else (GTEST_FOUND)
  message(FATAL_ERROR "Can't find Google Testing. Please set GTEST_INCLUDE_DIR & GTEST_FOUND")
endif()

# Eigen
set(MIN_EIGEN_VERSION 3.2.0)
find_package(Eigen ${MIN_EIGEN_VERSION} REQUIRED)
if (EIGEN_FOUND)
  message("-- Found Eigen version ${EIGEN_VERSION}: ${EIGEN_INCLUDE_DIRS}")
endif (EIGEN_FOUND)

# OpenImageIO
message("-- Check for OpenImageIO")
find_package(OpenImageIO REQUIRED)
if (OPENIMAGEIO_FOUND)
  message("-- Found OpenImageIO: ${OPENIMAGEIO_INCLUDE_DIRS}")
else (OPENIMAGEIO_FOUND)
  message(FATAL_ERROR "Can't find OpenImageIO. Please set OPENIMAGEIO_INCLUDE_DIR & OPENIMAGEIO_LIBRARY")
endif (OPENIMAGEIO_FOUND)

# QT
message("-- Check for Qt5")
find_package(Qt5 5.4 REQUIRED)
if (Qt5_FOUND)
  message("-- Found OpenImageIO: ${Qt5_INCLUDE_DIRS}")
else (Qt5_FOUND)
  message(FATAL_ERROR "Can't find Qt5. Please set Qt5_INCLUDE_DIR & QT5_LIBRARY")
endif (Qt5_FOUND)

include_directories(
  include
  src
  ${EIGEN_INCLUDE_DIRS}
  ${GFLAGS_INCLUDE_DIRS}
  ${GLOG_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ${OPENIMAGEIO_INCLUDE_DIRS}
  ${Qt5_INCLUDE_DIR}
)
include_directories(SYSTEM ${EIGEN_INCLUDE_DIRS})

add_subdirectory(applications)
add_subdirectory(src/raytracer)