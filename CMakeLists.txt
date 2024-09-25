cmake_minimum_required(VERSION 3.10)
project(VideoProcessingApp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_executable(VideoProcessingApp src/main.cpp src/video_processing.cpp)

target_link_libraries(VideoProcessingApp ${OpenCV_LIBS})