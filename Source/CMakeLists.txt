

include_directories(PUBLIC .)
add_subdirectory(Reveal3d)
aux_source_directory(Editor EDITOR_SOURCES)
aux_source_directory(Editor/viewport EDITOR_SOURCES)
aux_source_directory(Editor/components EDITOR_SOURCES)
aux_source_directory(Project PROJECT_SOURCES)
add_executable(RevealEngine main.cpp ${EDITOR_SOURCES} ${PROJECT_SOURCES})
target_link_libraries(RevealEngine Reveal3d)
target_include_directories(RevealEngine PUBLIC Reveal3d)
