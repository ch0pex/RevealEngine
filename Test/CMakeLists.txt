enable_testing()

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(run_tests test_scene.cpp test_content.cpp)
target_link_libraries(run_tests PRIVATE doctest::doctest Reveal3d)
target_include_directories(run_tests PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(run_tests PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(run_tests PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(run_tests PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")

function(add_reveal3d_test target_name source_file)
    add_executable(${target_name} ${source_file})
    add_test(NAME ${target_name} COMMAND ${target_name})
    target_link_libraries(${target_name} PRIVATE doctest::doctest Reveal3d)
    target_include_directories(${target_name} PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
    target_include_directories(${target_name} PUBLIC
            ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32
            ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include
    )
    target_compile_definitions(${target_name} PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
endfunction()

add_reveal3d_test(test_scene test_scene.cpp)
add_reveal3d_test(test_content test_content.cpp)
add_reveal3d_test(test_transforms test_components.cpp)

