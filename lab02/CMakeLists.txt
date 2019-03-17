cmake_minimum_required(VERSION 3.12)
project(lab02)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
            -pedantic -Wall -Wextra
            -Wnon-virtual-dtor
            -Wold-style-cast -Wcast-align
            -Wunused -Woverloaded-virtual
            -Wpedantic -Wconversion -Wnull-dereference
            -Wdouble-promotion -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op -fsanitize=leak
            -fno-omit-frame-pointer)

include_directories(src)
include_directories(src/circles)
include_directories(src/graphics)
include_directories(src/utility)
include_directories(src/widgets)

add_executable(lab02
        main.cpp
        src/application.cpp
        src/graphics/window.cpp
        src/graphics/canvas.cpp
        src/circles/circle.cpp
        src/circles/rgb_circle.cpp
        src/circles/cmy_circle.cpp
        src/circles/hsl_circle.cpp
        src/circles/hsv_circle.cpp
        src/utility/input_manager.cpp
        src/widgets/slider.cpp
        src/widgets/fps_counter.cpp)

target_link_libraries(lab02 sfml-graphics sfml-window sfml-system)

configure_file(fonts/Lato-Regular.ttf fonts/Lato-Regular.ttf COPYONLY)