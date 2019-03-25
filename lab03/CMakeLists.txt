cmake_minimum_required(VERSION 3.12)
project(lab03)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets 3.1.2 REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(src)
include_directories(src/graphics)

add_executable(lab03
        main.cpp
        src/application.cpp
        src/graphics/frame.cpp)

target_link_libraries(lab03 ${wxWidgets_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/assets/banan.png assets/banan.png COPYONLY)