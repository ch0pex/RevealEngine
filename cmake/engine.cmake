target_sources(
  rflect3d-engine
  PUBLIC
    FILE_SET
    HEADERS
    BASE_DIRS
    ${PROJECT_SOURCE_DIR}/src
    FILES
    # Ecs
    ${PROJECT_SOURCE_DIR}/src/engine/scene/entity.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/scene.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/behaviour.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/collider.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/component.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/geometry.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/light.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/metadata.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/rigidbody.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/components/transform.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/behaviour/behaviour_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/behaviour/behaviour_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/collider/collider_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/collider/collider_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/geometry/geometry_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/geometry/geometry_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/light/light_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/light/light_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/metadata/metadata_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/metadata/metadata_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/rigidbody/rigidbody_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/rigidbody/rigidbody_system.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/transform/transform_data.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/scene/systems/transform/transform_system.hpp
    # Content
    ${PROJECT_SOURCE_DIR}/src/engine/content/formats/obj/obj_parser.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/content/content.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/content/primitives.hpp
    # Core
    ${PROJECT_SOURCE_DIR}/src/engine/core/misc/timer.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/data_types/id.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/containers/vector.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/misc/string_literals.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/data_types/primitive_types.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/misc/tuple.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/logging/logger.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/core/misc/platform.hpp
    # Render
    ${PROJECT_SOURCE_DIR}/src/engine/render/renderer.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/render/camera.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/render/light.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/render/material.hpp
    # Input
    ${PROJECT_SOURCE_DIR}/src/engine/input/input.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/input/input_types.hpp
    # Config
    ${PROJECT_SOURCE_DIR}/src/engine/config/config.hpp
    # Math
    ${PROJECT_SOURCE_DIR}/src/engine/math/math.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/math/vector.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/math/utils.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/math/concepts.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/math/operators.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/math/matrix.hpp
    # Window
    ${PROJECT_SOURCE_DIR}/src/engine/window/window.hpp
    ${PROJECT_SOURCE_DIR}/src/engine/window/window_info.hpp #
)
