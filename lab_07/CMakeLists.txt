cmake_minimum_required(VERSION 3.17)
project(lab_07)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} inc/MainWindowUI.h src/MyMainWindow.cpp inc/MyMainWindow.h src/CanvasPolygon.cpp inc/CanvasPolygon.h)

#target_include_directories(${PROJECT_NAME} PRIVATE inc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++1y")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)

add_executable(${PROJECT_NAME}_debug main.cpp)

target_link_libraries(${PROJECT_NAME}_debug PUBLIC ${PROJECT_NAME})

#target_include_directories(${PROJECT_NAME}_debug PRIVATE inc)