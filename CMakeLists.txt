cmake_minimum_required(VERSION 3.31)

project(RevealEngine LANGUAGES CXX)

# Provisional
add_subdirectory(${PROJECT_SOURCE_DIR}/src/engine/extern/rflect/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/engine/extern/rflect/tests)

add_subdirectory(src)
add_subdirectory(tests)
