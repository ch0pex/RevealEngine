include_directories(PUBLIC .)
add_subdirectory(engine)

include(${PROJECT_SOURCE_DIR}/cmake/editor.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/engine.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/post_build.cmake)

add_executable(RevealEngine ${EDITOR_SOURCES} ${PROJECT_SOURCES} main.cpp)
target_link_libraries(RevealEngine PRIVATE rflect3d)
target_include_directories(RevealEngine PUBLIC engine)
target_include_directories(RevealEngine PUBLIC)
target_include_directories(RevealEngine PUBLIC engine/extern)

#copy_glew_dll(RevealEngine "${CMAKE_BINARY_DIR}/src")
