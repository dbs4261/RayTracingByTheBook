file(GLOB_RECURSE RAYTRACER_HDRS *.h)

file(GLOB_RECURSE RAYTRACER_SRC *.cc)

set(RAYTRACER_LIBRARY_SRC ${RAYTRACER_HDRS} ${RAYTRACER_SRC})
set(RAYTRACER_LIBRARY_DEPENDENCEIES
    Eigen3
    ${GFLAGS_LIBRARIES}
    ${GLOG_LIBRARIES}
#    ${OPENIMAGEIO_LIBRARIES}
    )

add_library(raytracer ${RAYTRACER_LIBRARY_SRC})
target_link_libraries(raytracer ${RAYTRACER_LIBRARY_DEPENDENCIES})
qt5_use_modules(raytracer Core Widgets Gui)

if (BUILD_TESTING)
  macro (GTEST FILENAME)
    string(REPLACE "/" ";" TEST_NAME_LIST ${FILENAME})
    list(REVERSE TEST_NAME_LIST)
    list(GET TEST_NAME_LIST 0 TEST_NAME)
    add_executable(${TEST_NAME}_test test/test_main.cc ${FILENAME}_Test.cpp)
    target_link_libraries(${TEST_NAME}_test
                          gtest
                          raytracer
                          ${RAYTRACER_LIBRARY_DEPENDENCIES})
    add_test(NAME ${TEST_NAME}_test
             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}_test)
  endmacro (GTEST)

  #gtest(path/to/file)
endif (BUILD_TESTING)