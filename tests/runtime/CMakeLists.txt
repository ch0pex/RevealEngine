find_package(doctest CONFIG REQUIRED)

include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/test_utils.cmake)

# --- Math ---
add_rflect3d_utest(test_math utest/math/test_math.cpp)
#add_rflect3d_utest(test_content utest/content/test_content.cpp)

# --- Core ---
add_rflect3d_utest(test_strings utest/core/test_string_literals.cpp)
add_rflect3d_utest(test_ids utest/core/test_id.cpp)
add_rflect3d_utest(test_views utest/core/test_views.cpp)
add_rflect3d_utest(test_bi_map utest/core/test_bi_map.cpp)

# --- Scene ---
add_rflect3d_utest(test_systems utest/scene/test_systems.cpp)
add_rflect3d_utest(test_scene_graph utest/scene/test_scene_graph.cpp)
add_rflect3d_utest(test_ecs utest/scene/test_ecs.cpp)
add_rflect3d_utest(test_transform_component utest/scene/test_transform.cpp)
add_rflect3d_utest(test_metadata_component utest/scene/test_metadata.cpp)


# --- Functional tests ---
add_rflect3d_ftest(high_poly ftest/high_poly_meshes.cpp)
add_rflect3d_ftest(multiple_children ftest/multiple_children.cpp)
