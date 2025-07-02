cmake_minimum_required(VERSION 3.28)

add_library(rflect3d STATIC)

target_include_directories(rflect3d PUBLIC ${PROJECT_SOURCE_DIR}/src/engine)

include(${PROJECT_SOURCE_DIR}/cmake/engine.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/imgui.cmake)

target_include_directories(rflect3d PUBLIC math/${PLAT})
target_compile_definitions(rflect3d PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
