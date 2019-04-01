cmake_minimum_required(VERSION 3.12)
project(lab03)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets 3.1.2 REQUIRED)
include(${wxWidgets_USE_FILE})

#include_directories(src)

add_executable(lab03
        main.cpp
        ChartClass.cpp
        ConfigClass.cpp
        GUI.cpp
        GUIMyFrame1.cpp)

target_link_libraries(lab03 ${wxWidgets_LIBRARIES})