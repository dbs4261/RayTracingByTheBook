add_executable(LaunchGui launch_gui.cc)
target_link_libraries(LaunchGui
  PRIVATE
    raytracer
    ${GFLAGS_LIBRARIES}
    ${GLOG_LIBRARIES}
)
target_include_directories(LaunchGui
  PRIVATE
    ../src/
)

add_executable(ImguiSfmlExample imgui_sfml_example.cc)
target_link_libraries(ImguiSfmlExample
  PRIVATE
    imgui
    ${GFLAGS_LIBRARIES}
    ${GLOG_LIBRARIES}
)
target_include_directories(ImguiSfmlExample
  PRIVATE
    ../libraries/imgui
)