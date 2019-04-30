set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
if(OPENGL_LIBRARIES)
  message("-- Found OpenGL")
else()
  message("-- Did not find OpenGL")
endif()

find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  message("-- Found SFML 2")
else()
  message("-- Did not find SFML 2")
endif()

add_library(imgui imgui.cpp imgui_draw.cpp imgui-SFML.cpp)
target_link_libraries(imgui
  PUBLIC
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# Ignoring msvc warning. imgui is really hard to work with warning wise
if (MSVC)
  target_compile_options(imgui PRIVATE /wd4312)
endif()