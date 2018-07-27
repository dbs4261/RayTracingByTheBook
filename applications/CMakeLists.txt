add_executable(ScribbleExample scribble_example.cc)
target_link_libraries(ScribbleExample raytracer ${GFLAGS_LIBRARIES} ${GLOG_LIBRARIES})
qt5_use_modules(ScribbleExample Core Widgets Gui)

add_executable(PixelSpeed pixel_speed.cc)
target_link_libraries(PixelSpeed ${GFLAGS_LIBRARIES} ${GLOG_LIBRARIES})
qt5_use_modules(PixelSpeed Core Widgets Gui)