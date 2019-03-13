cmake_minimum_required(VERSION 2.8)
project(lab01)

set(CMAKE_CXX_STANDARD 17)


#include_directories(${SFML_INCLUDE_DIR})
include_directories(include)
include_directories(src)

add_executable(lab01
        main.cpp
        src/menu.cpp
        src/canvas.cpp
        src/application.cpp
        src/file_manager.cpp)

#target_link_libraries(lab01 sfml-graphics sfml-window sfml-system)
#target_link_libraries(lab01 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(lab01 sfml-graphics sfml-window sfml-system)
endif()