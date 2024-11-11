cmake_minimum_required(VERSION 3.29.6)

#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
#         This specific value changes as experimental support evolves. See
#         `Help/dev/experimental.rst` in the CMake source corresponding to
#         your CMake build for the exact value to use.
#        "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(RevealEngine LANGUAGES CXX)

#set(CMAKE_CXX_MODULE_STD 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(Source)
add_subdirectory(Test)


