enable_testing()

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(test test_scene.cpp)
add_test(NAME run_tests COMMAND test_scene)
target_link_libraries(test PRIVATE doctest::doctest Reveal3d)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(test PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
