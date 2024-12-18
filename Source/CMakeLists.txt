cmake_minimum_required(VERSION 3.28)

project(RevealEngine LANGUAGES CXX)

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
        ${EDITOR_SOURCES} ${PROJECT_SOURCES} main.cpp
        Engine/engine.hpp
        Engine/run_engine.hpp
        Engine/engine_cfg.hpp
        Engine/state_machine/fsm.hpp
        Engine/state_machine/states.hpp
        Editor/viewport/profiler.hpp
        Editor/utils/imgui.hpp
        Editor/utils/components.hpp
        Editor/utils/styling.hpp
)
target_link_libraries(RevealEngine Reveal3d)
target_include_directories(RevealEngine PUBLIC Reveal3d)
target_include_directories(RevealEngine PUBLIC)
