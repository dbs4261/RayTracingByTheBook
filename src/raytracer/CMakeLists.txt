add_library(raytracer)
target_compile_features(raytracer PUBLIC cxx_std_17)
target_sources(raytracer
  PRIVATE
    gui/main_window.cc
)

target_compile_options(raytracer
  PUBLIC
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
)