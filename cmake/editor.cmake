target_sources(
  rflect3d-editor
  PRIVATE ${PROJECT_SOURCE_DIR}/src/editor/utils/components.cpp
          ${PROJECT_SOURCE_DIR}/src/editor/viewport/dock_space.cpp
          ${PROJECT_SOURCE_DIR}/src/editor/viewport/file_explorer.cpp
          ${PROJECT_SOURCE_DIR}/src/editor/viewport/scene_graph.cpp)

target_sources(
  rflect3d-editor
  PUBLIC
    FILE_SET
    HEADERS
    BASE_DIRS
    ${PROJECT_SOURCE_DIR}/src
    FILES
    ${PROJECT_SOURCE_DIR}/src/editor/utils/table_components.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/utils/components.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/utils/imgui.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/utils/styling.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/draw_component.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/draw_geometry_component.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/draw_light_component.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/draw_metadata_component.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/draw_transform_component.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/entity_properties/entity_properties.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/camera_properties.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/console.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/dock_space.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/file_explorer.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/menu_bar.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/profiler.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/scene_graph.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/viewport/world_properties.hpp
    ${PROJECT_SOURCE_DIR}/src/editor/editor.hpp)

target_link_libraries(rflect3d-editor PUBLIC rflect3d-engine)
