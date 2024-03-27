cmake_minimum_required(VERSION 3.1)

project(mjpeg_streamer CXX)

find_package(OpenCV 4.2 REQUIRED)
# find_package(nadjieb_mjpeg_streamer REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(stream_test
  "mjpeg_server.cpp")
target_compile_features(stream_test PRIVATE cxx_std_11)
target_link_libraries(stream_test PRIVATE
                     ${OpenCV_LIBS})