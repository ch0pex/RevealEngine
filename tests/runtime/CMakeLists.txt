find_package(doctest CONFIG REQUIRED)

include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/test_utils.cmake)

# --- Math ---
add_engine_utest(math_matrix utest/math/test_matrix.cpp)
add_engine_utest(math_vector utest/math/test_vector.cpp)

# --- Core ---
add_engine_utest(core_strings utest/core/test_string_literals.cpp)
add_engine_utest(core_data_types_ids utest/core/test_id.cpp)
add_engine_utest(core_containers_views utest/core/test_views.cpp)
add_engine_utest(core_containers_bimap utest/core/test_bi_map.cpp)

# --- Scene ---
add_engine_utest(scene_systems utest/scene/test_systems.cpp)
add_engine_utest(scene_graph utest/scene/test_scene_graph.cpp)
add_engine_utest(scene_ecs utest/scene/test_ecs.cpp)
add_engine_utest(scene_transform_component utest/scene/test_transform.cpp)
add_engine_utest(scene_metadata_component utest/scene/test_metadata.cpp)

# --- Content ---
#add_engine_utest(test_content utest/content/test_content.cpp)

# --- Functional tests ---
add_rflect3d_ftest(high_poly ftest/high_poly_meshes.cpp)
add_rflect3d_ftest(multiple_children ftest/multiple_children.cpp)
