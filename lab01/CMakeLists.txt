cmake_minimum_required(VERSION 2.8)
project(lab01)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

add_executable(lab01
        main.cpp
        src/menu.cpp
        src/canvas.cpp
        src/application.cpp
        src/file_manager.cpp)

target_link_libraries(lab01 sfml-graphics sfml-window sfml-system)
