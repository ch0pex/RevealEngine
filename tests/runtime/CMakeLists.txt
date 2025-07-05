find_package(doctest REQUIRED)

include(${PROJECT_SOURCE_DIR}/cmake/extern.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/test_utils.cmake)

add_rflect3d_utest(test_math utest/test_math.cpp)
add_rflect3d_utest(test_scene utest/test_scene.cpp)
add_rflect3d_utest(test_content utest/test_content.cpp)
add_rflect3d_utest(test_components utest/test_components.cpp)
add_rflect3d_utest(test_strings utest/test_string_literals.cpp)
add_rflect3d_utest(test_pools utest/test_pools.cpp)
add_rflect3d_utest(test_ids utest/test_id.cpp)
add_rflect3d_utest(test_rflect3d utest/test_rflec3d_scene.cpp)

add_rflect3d_ftest(high_poly ftest/high_poly_meshes.cpp)
add_rflect3d_ftest(multiple_children ftest/multiple_children.cpp)
