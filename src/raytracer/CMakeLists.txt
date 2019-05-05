add_library(raytracer)
target_compile_features(raytracer PUBLIC cxx_std_17)
target_sources(raytracer
  PRIVATE
    gui/drawable_image.cc
    image/image.cc
    io/pgm_io.cc
)

target_compile_options(raytracer
  PRIVATE
    $<$<CONFIG:Debug>:-O3>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z>
)
target_link_libraries(raytracer
  PUBLIC
    ${BOOST_LIBRARIES}
    imgui
)
target_include_directories(raytracer
  PUBLIC
    ${BOOST_INCLUDE_DIRS}
    ${CMAKE_HOME_DIRECTORY}/libraries/imgui/
    ${CMAKE_HOME_DIRECTORY}/src/
)