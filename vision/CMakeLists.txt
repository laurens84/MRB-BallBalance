cmake_minimum_required(VERSION 2.6)

project(vision)
set(exe_name "vision")

enable_testing()
include(../../../flags.cmake)

set(OpenCV_DIR "~/Documents/opencv/release")

find_package(OpenCV REQUIRED PATHS "~/Documents/opencv/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/circle_detector.cpp
    src/coordinator.cpp
    src/main.cpp)

add_executable(${exe_name} ${sources})
target_link_libraries(vision ${OpenCV_LIBS})
