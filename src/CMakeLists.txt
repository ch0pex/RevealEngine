# Rflect3d static libraries
add_library(rflect3d-engine STATIC)
add_library(rflect3d-editor STATIC)

include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/editor.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/engine.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/imgui.cmake)

target_include_directories(
  rflect3d-engine
  PUBLIC ${PROJECT_SOURCE_DIR}/src/engine/extern
         ${PROJECT_SOURCE_DIR}/src/engine/extern/rflect/src/include)

# Rflect3d executable
add_executable(Rflect3d main.cpp)
target_link_libraries(Rflect3d PUBLIC rflect3d-editor)
