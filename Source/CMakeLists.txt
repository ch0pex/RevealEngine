cmake_minimum_required(VERSION 3.28)

project(RevealEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)


include_directories(PUBLIC .)
add_subdirectory(Reveal3d)

include(cmake/editor.cmake)
include(cmake/engine.cmake)

add_executable(RevealEngine ${EDITOR_SOURCES} ${PROJECT_SOURCES} main.cpp)
target_link_libraries(RevealEngine Reveal3d)
target_include_directories(RevealEngine PUBLIC Reveal3d)
target_include_directories(RevealEngine PUBLIC)

include(cmake/post_build.cmake)
