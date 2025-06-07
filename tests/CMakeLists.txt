enable_testing()
find_package(doctest REQUIRED)

macro(add_rflect3d_utest test_name test_src)
    list(APPEND TEST_FLAGS "--duration=true")

    set(JUNIT_DIR "${PROJECT_BINARY_DIR}/junit")
    file(MAKE_DIRECTORY ${JUNIT_DIR})
    set(JUNIT_FILE "${JUNIT_DIR}/${test_name}.xml")
    message("Setting junit file: ${JUNIT_FILE}")
    list(APPEND TEST_FLAGS "--reporters=junit")
    list(APPEND TEST_FLAGS "--out=${JUNIT_FILE}")

    set(test_exe_name "reveal_${test_name}")
    add_executable(${test_exe_name} ${test_src})
    target_link_libraries(${test_exe_name} PRIVATE doctest::doctest)
    target_link_libraries(${test_exe_name} PUBLIC rflect3d)
    target_include_directories(
            ${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src/engine
            ${PROJECT_SOURCE_DIR}/src/engine/extern)
    target_compile_definitions(${test_exe_name}
            PRIVATE DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES)
    add_test(${test_name} ${test_exe_name} ${TEST_FLAGS})
    include(${PROJECT_SOURCE_DIR}/cmake/post_build.cmake)
endmacro(add_rflect3d_utest)

macro(add_rflect3d_ftest test_name test_src)
    set(test_exe_name "reveal_${test_name}")
    include(${PROJECT_SOURCE_DIR}/cmake/editor.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/engine.cmake)
    list(TRANSFORM EDITOR_SOURCES PREPEND "${BASE}")
    list(TRANSFORM ENGINE_SOURCES PREPEND "${BASE}")
    add_executable(${test_exe_name} ${test_src} ${ENGINE_SOURCES}
            ${EDITOR_SOURCES})
    target_link_libraries(${test_exe_name} PUBLIC rflect3d)
    target_include_directories(
            ${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src/engine
            ${PROJECT_SOURCE_DIR}/src/engine/extern)
    target_include_directories(${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src)
    include(${PROJECT_SOURCE_DIR}/cmake/post_build.cmake)
endmacro(add_rflect3d_ftest)

add_rflect3d_utest(test_math utest/test_math.cpp)
add_rflect3d_utest(test_scene utest/test_scene.cpp)
add_rflect3d_utest(test_content utest/test_content.cpp)
add_rflect3d_utest(test_components utest/test_components.cpp)
add_rflect3d_utest(test_strings utest/test_string_literals.cpp)
add_rflect3d_utest(test_pools utest/test_pools.cpp)
add_rflect3d_utest(test_ids utest/test_id.cpp)

add_rflect3d_ftest(high_poly ftest/high_poly_meshes.cpp)
add_rflect3d_ftest(multiple_children ftest/multiple_children.cpp)

add_compile_options(/Wall /Wextra /external:anglebrakets /external:W0 /concepts)
