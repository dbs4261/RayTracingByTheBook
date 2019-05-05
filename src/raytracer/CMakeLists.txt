add_library(raytracer)
target_compile_features(raytracer PUBLIC cxx_std_17)
target_sources(raytracer
  PRIVATE
    gui/main_window.cc
    image/image.cc
)

target_compile_options(raytracer
  PRIVATE
    $<$<CONFIG:Debug>:-O3>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z>
)
target_link_libraries(raytracer
  PUBLIC
    imgui
)
target_include_directories(raytracer
  PUBLIC
    ../../libraries/imgui/
    ${CMAKE_HOME_DIRECTORY}/src/
)