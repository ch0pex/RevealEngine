cmake_minimum_required(VERSION 3.28)
project(reveal-tests)

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)


macro(add_reveal3d_test test_name test_src)
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
    target_link_libraries(${test_exe_name} PUBLIC Reveal3d)
    target_include_directories(${test_exe_name} PUBLIC ../Source/Reveal3d)
    target_compile_definitions(${test_exe_name} PRIVATE DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES)
    add_test(${test_name} ${test_exe_name} ${TEST_FLAGS})
endmacro(add_reveal3d_test)

add_reveal3d_test(test_scene test_scene.cpp)
add_reveal3d_test(test_content test_content.cpp)
add_reveal3d_test(test_components test_components.cpp)
add_reveal3d_test(test_strings test_string_literals.cpp)
add_reveal3d_test(test_pools test_pools.cpp)

# TODO make a compile flags cmake
add_compile_options(/Wall /Wextra /external:anglebrakets /external:W0 /experimental:module /concepts)

