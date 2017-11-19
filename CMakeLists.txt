cmake_minimum_required(VERSION 3.8)
project(road_controller)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cc
        src/subsystem/perception/detection/lane_detector_strategy.h
        src/subsystem/perception/detection/basic_lane_detector.cc
        src/subsystem/perception/detection/basic_lane_detector.h)

add_executable(road_controller ${SOURCE_FILES})

target_link_libraries(road_controller ${OpenCV_LIBS})