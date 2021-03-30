cmake_minimum_required(VERSION 3.17)
project(lab_03)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} src/Qt/MainMenu.cpp inc/Qt/MainMenu.h src/Qt/EntryLineCoords.cpp
        inc/Qt/EntryLineCoords.h src/DrawLine.cpp inc/DrawLine.h src/Qt/GraphicWidget.cpp
        inc/Qt/GraphicWidget.h src/Qt/DrawTypeComboBox.cpp inc/Qt/DrawTypeComboBox.h inc/Qt/IDrawTypeGetter.h
        inc/Qt/ICoordsGetter.h src/Qt/EditLineUpdated.cpp inc/Qt/EditLineUpdated.h
        src/CheckString.cpp inc/CheckString.h inc/Qt/IConverter.h inc/Qt/IDrawColorGetter.h src/Qt/DrawColorComboBox.cpp inc/Qt/DrawColorComboBox.h inc/Qt/ISpectreInformationGetter.h src/Qt/SpectreUI.cpp inc/Qt/SpectreUI.h inc/TimeManager.cpp inc/TimeManager.h inc/Qt/StairsGraphic.cpp inc/Qt/StairsGraphic.h)

target_include_directories(${PROJECT_NAME} PRIVATE inc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++1y")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)

add_executable(${PROJECT_NAME}_debug main.cpp)

target_link_libraries(${PROJECT_NAME}_debug PUBLIC ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_debug PRIVATE inc)