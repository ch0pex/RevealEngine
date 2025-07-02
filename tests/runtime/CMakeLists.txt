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

# Provisional add_executable(test_rflect3d utest/test_rflec3d_scene.cpp)
# target_include_directories( test_rflect3d PUBLIC
# ${PROJECT_SOURCE_DIR}/src/engine ${PROJECT_SOURCE_DIR}/src/engine/extern)
# target_include_directories(test_rflect3d PUBLIC ${PROJECT_SOURCE_DIR}/src)
# target_link_libraries(test_rflect3d PUBLIC doctest::doctest rflect::rflect
# fmt::fmt)
