cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(PUBLIC .)

add_library(Reveal3d STATIC)

include(${PROJECT_SOURCE_DIR}/cmake/source.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)

include(${PROJECT_SOURCE_DIR}/cmake/imgui.cmake)
target_compile_definitions(Reveal3d PRIVATE IMGUI=1)

target_include_directories(Reveal3d PUBLIC .)
target_include_directories(Reveal3d PUBLIC math/${PLAT})
target_include_directories(Reveal3d PUBLIC extern/include)
target_compile_definitions(Reveal3d PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
