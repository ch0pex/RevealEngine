cmake_minimum_required(VERSION 3.31)
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
#        This specific value changes as experimental support evolves. See
#        `Help/dev/experimental.rst` in the CMake source corresponding to
#        your CMake build for the exact value to use.
#        "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")


project(RevealEngine LANGUAGES CXX)

#set(CMAKE_CXX_MODULE_STD 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)


include_directories(PUBLIC .)
add_subdirectory(Reveal3d)
aux_source_directory(Editor EDITOR_SOURCES)
aux_source_directory(Editor/viewport EDITOR_SOURCES)
aux_source_directory(Editor/components EDITOR_SOURCES)
aux_source_directory(Project PROJECT_SOURCES)

add_executable(RevealEngine)

target_sources(RevealEngine
        #        PRIVATE
        #        FILE_SET CXX_MODULES FILES
        #        std.ixx
        PRIVATE
        ${EDITOR_SOURCES} ${PROJECT_SOURCES} main.cpp Engine/engine.hpp Engine/engine_cfg.hpp
        Engine/state_machine/fsm.hpp
        Engine/state_machine/states.hpp
        Editor/viewport/profiler.hpp
        Editor/imgui/imgui.hpp
)
target_link_libraries(RevealEngine Reveal3d)
target_include_directories(RevealEngine PUBLIC Reveal3d)
target_include_directories(RevealEngine PUBLIC)
